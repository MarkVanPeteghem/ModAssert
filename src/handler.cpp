//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/handler.hpp"
#include "modassert/filters.hpp"
#include "modassert/terminate_message.hpp"
#include "modassert/use_bool.hpp"

#if defined(RICHBOOL_USE_WX)
	#include "wx/dynarray.h"
	#include "wx/arrimpl.cpp"
	#include <wx/hashmap.h>
#else
	#include <vector>
	#include <map>
	#include <algorithm>
	#include <ctime>
#endif

#include "modassert/logger.hpp"
#include "modassert/hook.hpp"
#include "modassert/responder.hpp"
#include "modassert/levels.hpp"
#include "modassert/report_type.hpp"
#include "modassert/threads.hpp"
#include "modassert/timeinfo.hpp"
#include "modassert/properties.hpp"
#include "modassert/category.hpp"
#include "modassert/logtype.hpp"
#include "modassert/responder_switcher.hpp"
#include "modassert/warning_message.hpp"

#include <assert.h>

#if defined(RICHBOOL_WIN)
	#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0400
	#endif

	#include <windows.h>
#endif

namespace ModAssert
{
	extern void SetMainThread();

	struct LoggerData
	{
		LoggerData(const Logger *logger_, const Filter *filter_, size_t id_):
			logger(logger_), filter(filter_), id(id_)
		{}

		const Logger *logger;
		const Filter *filter;
		size_t id;
	};

	struct IsLogger
	{
		IsLogger(const Logger *logger_): logger(logger_)
		{}

		const Logger *logger;

		bool operator()(const LoggerData &loggerData) const
		{
			return logger==loggerData.logger;
		}
	};

	struct HasLoggerId
	{
		HasLoggerId(size_t id_): id(id_)
		{}

		size_t id;

		bool operator()(const LoggerData &loggerData) const
		{
			return id==loggerData.id;
		}
	};

#if defined(RICHBOOL_USE_WX)
	WX_DECLARE_OBJARRAY(LoggerData, LoggerArray);
	WX_DEFINE_OBJARRAY(LoggerArray);

	WX_DEFINE_ARRAY_PTR(const Hook*, HookArray);
	WX_DEFINE_ARRAY_PTR(const Filter*, FilterArray);
	WX_DECLARE_STRING_HASH_MAP(ReportData, FileToReportDataMap);
#else
	typedef std::vector<LoggerData> LoggerArray;
	typedef std::vector<const Hook*> HookArray;
	typedef std::vector<const Filter*> FilterArray;
	typedef std::map<std::string, ReportData> FileToReportDataMap;
#endif

	// The class State contains all global variables in ModAssert.
	// This class allows to have the same state in an executable and DLLs
	// by using GetState and SetState, so you need to set it up in one of
	// them, to have all assertions and checks handled in one place.
	class State
	{
	public:
		const Responder *m_responder;
		LoggerArray m_loggers;
		HookArray m_hooks;
		FilterArray m_hookFilters;
		const Logger *m_optionalLogger;
		const char *m_optionalLoggerText;

		Response m_responseMask;

		// non-const, so the user can call SetText on it:
		WarningMessage *m_warningResponder;

		// wrapper around m_warningResponder so user can change it
		// because GetState()->m_autoResponderWithWarning has pointer to
		// m_warningResponderWrapper, not m_warningResponder
		ResponderSwitcher m_warningResponderWrapper;

		const Filter *m_displayerFilter;

		// m_active is set to true as soon as a logger is added or a responder is set.
		// As long as this is false, assertions should be ignored, because
		// ModAssert needs thread synchronization, and the thread synchronization
		// may not yet be initialized before main(...) is entered. Therefore
		// m_loggers and responders should be set as soon as main(...) is entered,
		// but not sooner than that, so ModAssert is sure that thread
		// synchronization is available.
		// An object of the class AutoShutdown should be created on
		// the stack before main(...) is left, preferably before m_loggers are added
		// or a responder is set, but after the m_loggers and the responder are
		// created. Its destructor will make sure that m_active is made
		// false again. This makes sure that assertions are also ignored after
		// main(...) has exited, which is necessary because the thread
		// synchronization may be disabled by then.
		bool m_active;

		ResponderSwitcher m_autoResponderWithWarning,
			m_autoResponderWithTerminateAndWarning;
		FilterMinimumLevel m_warningLevel, m_terminateLevel;

		// the id that is assigned to each logger that is added,
		// so we can remove them using an id,
		// to avoid removing the wrong one if a logger is added more than once
		// (e.g. with different filters)
		int m_loggerId;

		FileToReportDataMap m_fileToReportDataMap;

		size_t m_optionalLoggerId;

		// non-const, so the user can call SetText on it:
		TerminateMessage *m_terminateMessage;

		Mode m_mode;

		void (*m_globalOptionalAction)(void);
		const char *m_globalOptionalActionName;


		static State *s_State;

		void Activate()
		{
			if (!m_active)
			{
				m_active = true;
			}
		}

	private:
		// private constructor so it is a singleton
		State()
			: m_responder(0)
			, m_optionalLogger(0)
			, m_optionalLoggerText(0)
			, m_responseMask(0)
			, m_warningResponder(0)
			, m_warningResponderWrapper(m_warningResponder)
			, m_displayerFilter(0)
			, m_active(false)
			, m_warningLevel(Warning)
			, m_terminateLevel(Fatal)
			, m_loggerId(0)
			, m_optionalLoggerId(0)
			, m_terminateMessage(0)
			, m_mode(continueSilentlyOnFailure)
			, m_globalOptionalAction(NULL)
			, m_globalOptionalActionName(NULL)
		{
			s_State = &_State;
		}

		// keep the singleton object private,
		// so that all code uses the pointer s_State,
		// which can be modified when used in several DLLs and an executable
		// (each of the executable and the DLLs will have their own _State object).
		static State _State;
	};

	State State::_State;
	State* State::s_State = 0;

	State* GetState()
	{
		return State::s_State;
	}

	void SetState(State *state)
	{
		State::s_State = state;
	}

	static void OnLoggerAdded(const Logger *logger, const Filter *filter)
	{
		GetState()->Activate();

		static const LogType logAtBegin(LogType::AtBegin);

		if (!filter || filter->Accept(logAtBegin) )
			logger->AddBeginMessage(filter);

		SetMainThread();
	}

	static void OnLoggerRemoved(const Logger *logger, const Filter *filter)
	{
		static const LogType logAtEnd(LogType::AtEnd);

		if (!filter || filter->Accept(logAtEnd) )
			logger->AddEndMessage();
	}

#if defined(RICHBOOL_USE_WX)

	size_t AddLogger(const Logger *logger, const Filter *filter)
	{
		ScopedLock lock;

		GetState()->m_loggers.Add(LoggerData(logger, filter, ++GetState()->m_loggerId));

		OnLoggerAdded(logger, filter);

		return GetState()->m_loggerId;
	}

	template <class Func>
	int FindLogger(Func func)
	{
		size_t i=0;
		for ( ; i<GetState()->m_loggers.GetCount(); ++i)
		{
			if (func(GetState()->m_loggers[i]))
				return (int)i;
		}
		return wxNOT_FOUND;
	}

	template <class Func>
	void TmplRemoveLogger(Func func)
	{
		ScopedLock lock;

		int idx = FindLogger(func);
		if (idx!=wxNOT_FOUND)
		{
			OnLoggerRemoved(GetState()->m_loggers[idx].logger, GetState()->m_loggers[idx].filter);
			GetState()->m_loggers.RemoveAt(idx);
		}
	}

	template <class Func>
	bool TmplIsLoggerUsed(Func func)
	{
		ScopedLock lock;

		return FindLogger(func)!=wxNOT_FOUND;
	}

	#define NR_LOGGERS GetState()->m_loggers.GetCount()

	void AddHook(const Hook *hook, const Filter *filter)
	{
		ScopedLock lock;

		GetState()->m_hooks.Add(hook);
		GetState()->m_hookFilters.Add(filter);
	}
	void RemoveHook(const Hook *hook)
	{
		ScopedLock lock;

		int idx = GetState()->m_hooks.Index(hook);
		if (idx!=wxNOT_FOUND)
		{
			GetState()->m_hooks.RemoveAt(idx);
			GetState()->m_hookFilters.RemoveAt(idx);
		}
	}
	#define NR_HOOKS GetState()->m_hooks.GetCount()

#else

	size_t AddLogger(const Logger *logger, const Filter *filter)
	{
		ScopedLock lock;

		GetState()->m_loggers.push_back(LoggerData(logger, filter, ++GetState()->m_loggerId));

		OnLoggerAdded(logger, filter);

		return GetState()->m_loggerId;
	}

	template <class Func>
	void TmplRemoveLogger(Func func)
	{
		ScopedLock lock;

		std::vector<LoggerData>::iterator it =
			std::find_if(GetState()->m_loggers.begin(), GetState()->m_loggers.end(), func);
		if (it!=GetState()->m_loggers.end())
		{
			OnLoggerRemoved(it->logger, it->filter);
			GetState()->m_loggers.erase(it);
		}
	}

	template <class Func>
	bool TmplIsLoggerUsed(Func func)
	{
		ScopedLock lock;

		return std::find_if(GetState()->m_loggers.begin(), GetState()->m_loggers.end(), func)!=GetState()->m_loggers.end();
	}

	#define NR_LOGGERS GetState()->m_loggers.size()

	void AddHook(const Hook *hook, const Filter *filter)
	{
		ScopedLock lock;

		GetState()->m_hooks.push_back(hook);
		GetState()->m_hookFilters.push_back(filter);
	}
	void RemoveHook(const Hook *hook)
	{
		ScopedLock lock;

		std::vector<const Hook*>::iterator it =
			std::find(GetState()->m_hooks.begin(), GetState()->m_hooks.end(), hook);
		if (it!=GetState()->m_hooks.end())
		{
			size_t idx = it-GetState()->m_hooks.begin();
			GetState()->m_hooks.erase(it);
			GetState()->m_hookFilters.erase(GetState()->m_hookFilters.begin()+idx);
		}
	}
	#define NR_HOOKS GetState()->m_hooks.size()


#endif

	void RemoveLogger(const Logger *logger)
	{
		TmplRemoveLogger(IsLogger(logger));
	}
	void RemoveLogger(size_t id)
	{
		TmplRemoveLogger(HasLoggerId(id));
	}

	bool IsLoggerUsed(const Logger *logger)
	{
		return TmplIsLoggerUsed(IsLogger(logger));
	}

	bool IsLoggerUsed(size_t id)
	{
		return TmplIsLoggerUsed(HasLoggerId(id));
	}

	void SetOptionalLogger(const Logger *logger,
		const char *szText,
		bool extraInfo)
	{
		if (GetState()->m_optionalLoggerId)
		{
			RemoveLogger(GetState()->m_optionalLoggerId);
			GetState()->m_optionalLoggerId = 0;
		}

		if (extraInfo)
		{
			if (logger)
				GetState()->m_optionalLoggerId = AddLogger(logger, &filterNoAssertionsAndChecks);
		}

		GetState()->m_optionalLogger = logger;
		GetState()->m_optionalLoggerText = szText;
	}

	const Logger* GetOptionalLogger()
	{
		return GetState()->m_optionalLogger;
	}

	const char* GetOptionalLoggerText()
	{
		return GetState()->m_optionalLoggerText;
	}


	// because not every platform has recursive locks, we need non-locking versions
	// of SetDisplayInFile and GetDisplayInFile to call from HandleAssert

	void SetDisplayInFileNoLock(const char *file, bool b, const CategoryBase &cat)
	{
		cat.SetDisplay(b, GetState()->m_fileToReportDataMap[file]);
	}

	bool GetDisplayInFileNoLock(const char *file, const CategoryBase &cat)
	{
		FileToReportDataMap::iterator it=GetState()->m_fileToReportDataMap.find(file);

		return it==GetState()->m_fileToReportDataMap.end() ? true : cat.GetDisplay(it->second);
	}

	void SetDisplayInFile(const char *file, bool b, const CategoryBase &cat)
	{
		ScopedLock lock;

		SetDisplayInFileNoLock(file, b, cat);
	}

	bool GetDisplayInFile(const char *file, const CategoryBase &cat)
	{
		ScopedLock lock;

		return GetDisplayInFileNoLock(file, cat);
	}


	void SetLogInFileNoLock(const char *file, bool b, const CategoryBase &cat)
	{
		cat.SetLog(b, GetState()->m_fileToReportDataMap[file]);
	}

	bool GetLogInFileNoLock(const char *file, const CategoryBase &cat)
	{
		FileToReportDataMap::iterator it=GetState()->m_fileToReportDataMap.find(file);

		return it==GetState()->m_fileToReportDataMap.end() ? true : cat.GetLog(it->second);
	}

	void SetLogInFile(const char *file, bool b, const CategoryBase &cat)
	{
		ScopedLock lock;

		SetLogInFileNoLock(file, b, cat);
	}

	bool GetLogInFile(const char *file, const CategoryBase &cat)
	{
		ScopedLock lock;

		return GetLogInFileNoLock(file, cat);
	}


	void SetResponderNoLock(const Responder *responder)
	{
		// call before setting s_responder, so we override
		// the value that Activate() gives:
		GetState()->Activate();

		GetState()->m_responder = responder;

		SetMainThread();
	}

	void SetResponder(const Responder *responder)
	{
		ScopedLock lock;

		SetResponderNoLock(responder);
	}

	void SetDisplayFilter(const Filter *filter)
	{
		ScopedLock lock;

		GetState()->m_displayerFilter = filter;
	}

	const Responder* GetResponderSwitcherWithWarning()
	{
		if (GetState()->m_autoResponderWithWarning.size()==0)
		{
			GetState()->m_autoResponderWithWarning.AddFilter(&ModAssert::filterIfSuccess, ModAssert::Response(0));
			GetState()->m_autoResponderWithWarning.AddFilter(&ModAssert::filterIfCheck,   ModAssert::Response(0));
			GetState()->m_autoResponderWithWarning.AddFilter(&GetState()->m_warningLevel, &GetState()->m_warningResponderWrapper);
			GetState()->m_autoResponderWithWarning.SetDefaultResponse(ModAssert::Response(0));
		}
		return &GetState()->m_autoResponderWithWarning;
	}

	const Responder* GetTerminatingResponder()
	{
		if (GetState()->m_autoResponderWithTerminateAndWarning.size()==0)
		{
			GetState()->m_autoResponderWithTerminateAndWarning.AddFilter(&ModAssert::filterIfSuccess, ModAssert::Response(0));
			GetState()->m_autoResponderWithTerminateAndWarning.AddFilter(&ModAssert::filterIfCheck,   ModAssert::Response(0));
			GetState()->m_autoResponderWithTerminateAndWarning.AddFilter(&GetState()->m_terminateLevel,      ModAssert::Exit);
			GetState()->m_autoResponderWithTerminateAndWarning.AddFilter(&GetState()->m_warningLevel, &GetState()->m_warningResponderWrapper);
			GetState()->m_autoResponderWithTerminateAndWarning.SetDefaultResponse(ModAssert::Response(0));
		}
		return &GetState()->m_autoResponderWithTerminateAndWarning;
	}

	void SetWarningMessage(WarningMessage *warningMessage)
	{
		ScopedLock lock;

		GetState()->m_warningResponder = warningMessage;
		GetState()->m_warningResponderWrapper.SetDefaultResponder(warningMessage);
	}

	void SetWarningMessageNoLock(WarningMessage *warningMessage)
	{
		GetState()->m_warningResponder = warningMessage;
		GetState()->m_warningResponderWrapper.SetDefaultResponder(warningMessage);
	}

	WarningMessage* GetWarningMessage()
	{
		return GetState()->m_warningResponder;
	}

	void SetTerminateMessageNoLock(TerminateMessage *terminateMessage)
	{
		GetState()->m_terminateMessage = terminateMessage;
	}

	void SetTerminateMessage(TerminateMessage *terminateMessage)
	{
		ScopedLock lock;

		GetState()->m_terminateMessage = terminateMessage;
	}

	TerminateMessage* GetTerminateMessage()
	{
		return GetState()->m_terminateMessage;
	}

	void Setup(const Responder *responder)
	{
#ifdef NDEBUG
		Setup(continueSilentlyOnFailure, responder, NULL, NULL);
#else
		Setup(testMode, responder, NULL, NULL);
#endif
	}

	void Setup(Mode mode,
		const Responder *responder,
		WarningMessage *warningMessage,
		TerminateMessage *terminateMessage)
	{
		ScopedLock lock;

		SetWarningMessageNoLock(warningMessage);
		GetState()->m_mode = mode;

		switch (mode)
		{
		case testMode:
			SetResponderNoLock(responder);
			UseBool::SetCheck(true);
			break;
		case continueSilentlyOnFailure:
			SetResponderNoLock(NULL);
			UseBool::SetCheck(false);
			break;
		case continueWithWarningOnFailure:
			SetResponderNoLock(GetResponderSwitcherWithWarning());
			UseBool::SetCheck(false);
			break;
		case terminateOnFailure:
			// only call SetTerminateMessage if mode is terminateOnFailure,
			// if we'd do it for testMode we'd get message after debug info
			SetTerminateMessageNoLock(terminateMessage);
			SetResponderNoLock(GetTerminatingResponder());
			UseBool::SetCheck(false);
			break;
		}
	}

	Mode GetMode()
	{
		return GetState()->m_mode;
	}

	namespace detail
	{
		void SetMinimumTerminateLevel(int level)
		{
			GetState()->m_terminateLevel.SetLevel(level);
		}

		void SetMinimumWarningLevel(int level)
		{
			GetState()->m_warningLevel.SetLevel(level);
		}
	}

	static ReportData reportAll;

	bool GetDisplayAll(const CategoryBase &cat)
	{
		return cat.GetDisplay(reportAll);
	}
	void SetDisplayAll(bool display, const CategoryBase &cat)
	{
		cat.SetDisplay(display, reportAll);
	}

	bool GetLogAll(const CategoryBase &cat)
	{
		return cat.GetLog(reportAll);
	}
	void SetLogAll(bool log, const CategoryBase &cat)
	{
		cat.SetLog(log, reportAll);
	}

	void CallHooks(const Properties &properties,
		const Result &result)
	{
		for (size_t hook=0; hook<NR_HOOKS; ++hook)
			if (!GetState()->m_hookFilters[hook] || GetState()->m_hookFilters[hook]->Accept(properties, result))
				GetState()->m_hooks[hook]->OnAssert(properties, result);
	}

	void CallLoggers(const Properties &properties,
		const Result &result)
	{
		const CategoryBase &cb = *properties.GetCategory();
		bool ok = result.Succeeded();
		bool b = (!properties.GetGroupList()
				|| properties.GetGroupList()->GetLog(ok, cb));

		if ( GetLogAll(*properties.GetCategory())
			&& b
			&& GetLogInFileNoLock(properties.GetContext().file_, *properties.GetCategory()) )
		{
			for (size_t loggerIdx=0; loggerIdx<NR_LOGGERS; ++loggerIdx)
			{
				const LoggerData &loggerData = GetState()->m_loggers[loggerIdx];
				if (!loggerData.filter || loggerData.filter->Accept(properties, result))
					loggerData.logger->OnAssert(properties, result);
			}
		}
	}

	bool GetDisplay(const Properties &properties,
		const Result &result,
		bool *displayThis)
	{
		bool filteredOut = GetState()->m_displayerFilter &&
			!GetState()->m_displayerFilter->Accept(properties, result);

		return !filteredOut
			&& properties.GetGroupList()->GetDisplay(result.Succeeded(), *properties.GetCategory())
			&& (!displayThis || *displayThis)
			&& GetDisplayAll(*properties.GetCategory())
			&& GetDisplayInFileNoLock(properties.GetContext().file_,
				*properties.GetCategory());
	}

	Response AskResponse(const Properties &properties,
		const Result &result,
		bool *displayThis)
	{
		Response response = (Response)0;

		if (GetState()->m_responder)
		{
			bool display = GetDisplay(properties, result, displayThis);

			response = GetState()->m_responder->OnAssert(properties, result, display);

			if (response&StopDisplayingAll)
			{
				SetDisplayAll(false, *properties.GetCategory());
			}
			if (response&StopDisplayingFile)
			{
				SetDisplayInFileNoLock(properties.GetContext().file_, false, *properties.GetCategory());
			}
			if ( (response&StopDisplayingThis) && displayThis)
				*displayThis = false;

			GroupList *gl = const_cast<GroupList*>(properties.GetGroupList());
			size_t nrCustom = properties.GetGroupList()->GetSize();
			if (nrCustom>8) nrCustom = 8;
			for (size_t custom=0; custom<nrCustom; ++custom)
				if ( response & (StopDisplayingCustom1<<custom) )
					gl->SetDisplay(custom, false, *properties.GetCategory());
		}

		return response & (~GetState()->m_responseMask);
	}

	Category<Assertions> categoryAsserts;
	Category<Checks> categoryChecks;

	Response HandleAssert(
		const Properties &properties,
		const Result &result,
		bool *displayThis)
	{
		// if a check uses a Rich Boolean as the condition,
		// and this Rich Boolean detected a bad value,
		// it should be considered as an assertion
		bool is_bad_value = result.GetAnalysis()
			&&(result.GetAnalysis()->GetState()==RichBool::Analysis::BadValue);
		static TemplateGroupListWithLevel<Level<detail::L_<3> > > fatal(Fatal);
		const char *cond=properties.GetCondition();
		if (!properties.IsUnconditional() && !cond)
			cond = (char*)1;
		const Properties our_properties(
			is_bad_value ? &categoryAsserts : properties.GetCategory(),
			properties.GetContext(),
			cond,
			is_bad_value ? &fatal : properties.GetGroupList(),
			properties.GetOptional(),
			properties.CanStopDisplayingThis()
			);

		if (!GetState()->m_active)
			// if no m_loggers are added and no responder
			// is set, redirect assertions (not checks) to default assertion;
			// possibly thread synchronization is not yet available
			// so leave it to the default assertion mechanism
		{
#ifndef NDEBUG
			if (!result.Succeeded() && our_properties.GetCategory()->IsAssertion())
			{
				const bool Redirecting_ModAssert_To_DefaultAssert = false;
				assert(Redirecting_ModAssert_To_DefaultAssert);
			}
#endif
			return Response(0);
		}

		ScopedLock lock;

		CallHooks(our_properties, result);

		CallLoggers(our_properties, result);

		return AskResponse(our_properties, result, displayThis);
	}

	AutoShutdown::~AutoShutdown()
	{
		ScopedLock lock;

		GetState()->m_active = false;

		static const LogType logAtEnd(LogType::AtEnd);
		for (size_t logger=0; logger<NR_LOGGERS; ++logger)
		{
			const Filter *filter = GetState()->m_loggers[logger].filter;
			if ( !filter || filter->Accept(logAtEnd) )
				GetState()->m_loggers[logger].logger->AddEndMessage();
		}

		GetState()->m_responder = 0;
		GetState()->m_displayerFilter = 0;

		RichBool::detail::clear(GetState()->m_loggers);

		RichBool::detail::clear(GetState()->m_hooks);
		RichBool::detail::clear(GetState()->m_hookFilters);

		GetState()->m_fileToReportDataMap.clear();
	}

	void SetAllowBreakIntoDebugger(bool b)
	{
		if (b)
			GetState()->m_responseMask = GetState()->m_responseMask & (~BreakIntoDebugger);
		else
			GetState()->m_responseMask = GetState()->m_responseMask | BreakIntoDebugger;
	}

	void SetAllowExit(bool b)
	{
		if (b)
			GetState()->m_responseMask = GetState()->m_responseMask & (~Exit);
		else
			GetState()->m_responseMask = GetState()->m_responseMask | Exit;
	}

	void SetAllowOptional(bool b)
	{
		if (b)
			GetState()->m_responseMask = GetState()->m_responseMask & (~Optional);
		else
			GetState()->m_responseMask = GetState()->m_responseMask | Optional;
	}

	void SetAllowGlobalOptional(bool b)
	{
		if (b)
			GetState()->m_responseMask = GetState()->m_responseMask & (~GlobalOptional);
		else
			GetState()->m_responseMask = GetState()->m_responseMask | GlobalOptional;
	}

	bool GetAllowBreakIntoDebugger()
	{
		return (GetState()->m_responseMask&BreakIntoDebugger)==0;
	}

	bool GetAllowExit()
	{
		return (GetState()->m_responseMask&Exit)==0;
	}

	bool GetAllowOptional()
	{
		return (GetState()->m_responseMask&Optional)==0;
	}

	bool GetAllowGlobalOptional()
	{
		return (GetState()->m_responseMask&GlobalOptional)==0;
	}

	void SetGlobalOptionalAction(void (*func)(void), const char *funcName)
	{
		GetState()->m_globalOptionalAction = func;
		GetState()->m_globalOptionalActionName = funcName;
	}

	void (*GetGlobalOptionalAction())(void)
	{
		return GetState()->m_globalOptionalAction;
	}

	const char* GetGlobalOptionalActionDescription()
	{
		return GetState()->m_globalOptionalActionName;
	}

	bool IsDebugPossible()
	{
#if defined(RICHBOOL_WIN) && !defined(NDEBUG)
		return IsDebuggerPresent()!=FALSE;
#else
		return true; // return our best guess
#endif
	}

	void ExecuteGlobalOptionalAction()
	{
		if (GetState()->m_globalOptionalAction)
			GetState()->m_globalOptionalAction();
	}

	void HandleResponse(Response response,
		const Properties &properties,
		const Result &result)
	{
		if (response&ModAssert::GlobalOptional)
			ModAssert::ExecuteGlobalOptionalAction();

		if (response&ModAssert::Exit)
		{
			if (GetState()->m_terminateMessage)
				GetState()->m_terminateMessage->OnAssert(properties, result);
			exit(1);
		}
	}

	void ManualBreak()
	{
		// manually place a breakpoint here
		// if the MOD_ASSERT_BREAK_HERE macro can't be resolved for your platform
		int a=0;
		++a;
	}

	struct Nop_
	{
		void operator()() const {}
	};

	Nop_ Nop;
}
