//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef HANDLER_H__QM
#define HANDLER_H__QM

#include "richbool/portability.hpp"
#include "richbool/bool.hpp"
#include "modassert/report_type.hpp"
#include "modassert/levels.hpp"
#include "modassert/linkcore.hpp"
#include "modassert/warning_message.hpp"
#include "modassert/terminate_message.hpp"

namespace ModAssert
{
	class Filter;
	class Responder;
	class Context;
	class Logger;
	class Hook;
	class State;

	bool GetDisplayAll(const CategoryBase &cat);
	void SetDisplayAll(bool display, const CategoryBase &cat);

	bool GetLogAll(const CategoryBase &cat);
	void SetLogAll(bool log, const CategoryBase &cat);

	void SetDisplayInFile(const char *file, bool display, const CategoryBase &cat);
	bool GetDisplayInFile(const char *file, const CategoryBase &cat);

	void SetLogInFile(const char *file, bool b, const CategoryBase &cat);
	bool GetLogInFile(const char *file, const CategoryBase &cat);

	// only one Responder derived object can be active at the same time
	void SetResponder(const Responder *responder);

	State* GetState();
	void SetState(State *state);

	void SetDisplayFilter(const Filter *filter);

	namespace detail
	{
		void SetMinimumTerminateLevel(int level);
		void SetMinimumWarningLevel(int level);
	}

	template <class Level_>
	void SetMinimumWarningLevel(Level_ )
	{
		detail::SetMinimumWarningLevel(Level_::level);
	}

	template <class Level_>
	void SetMinimumTerminateLevel(Level_ )
	{
		detail::SetMinimumTerminateLevel(Level_::level);
	}

	void SetWarningMessage(WarningMessage *warningMessage);
	WarningMessage* GetWarningMessage();

	void SetTerminateMessage(TerminateMessage *terminateMessage);
	TerminateMessage* GetTerminateMessage();

	// multiple Logger derived objects can be active at the same time
	size_t AddLogger(const Logger *logger, const Filter *filter=NULL);
	void RemoveLogger(const Logger *logger);
	void RemoveLogger(size_t id);

	bool IsLoggerUsed(const Logger *logger);
	bool IsLoggerUsed(size_t id);

	void SetOptionalLogger(const Logger *logger, const char *szText=0, bool extraInfo=false);
	const Logger* GetOptionalLogger();
	const char* GetOptionalLoggerText();

	// multiple Hook derived objects can be active at the same time
	void AddHook(const Hook *hook, const Filter *filter=NULL);
	void RemoveHook(const Hook *hook);

	// Add an object of this struct in main(...), preferably before
	// you add a logger or set a responder. This will make sure that
	// ModAssert is exited gracefully.
	struct AutoShutdown
	{
		~AutoShutdown();
	};

	void SetGlobalOptionalAction(void (*action)(void), const char *description);
	void (*GetGlobalOptionalAction())(void);
	const char* GetGlobalOptionalActionDescription();

	void SetAllowBreakIntoDebugger(bool b);
	void SetAllowExit(bool b);
	void SetAllowOptional(bool b);
	void SetAllowGlobalOptional(bool b);

	bool GetAllowBreakIntoDebugger();
	bool GetAllowExit();
	bool GetAllowOptional();
	bool GetAllowGlobalOptional();

	bool IsDebugPossible();

	// used by wrapper functions to let caller decide
	// how ModAssert should handle failed assertions:
	enum Mode { testMode, continueSilentlyOnFailure,
		continueWithWarningOnFailure, terminateOnFailure };

	// Uses testMode if NDEBUG is not defined, otherwise continueSilentlyOnFailure.
	// It doesn't take a WarningMessage or TerminateMessage,
	// because these are not used with these modes.
	void Setup(const Responder *responder);

	// allows user to specify a mode instead of letting it depend on NDEBUG:
	void Setup(Mode mode,
		const Responder *responder,
		WarningMessage *warningMessage,
		TerminateMessage *terminateMessage);

	Mode GetMode();

} // namespace ModAssert

#endif // #ifndef HANDLER_H__QM
