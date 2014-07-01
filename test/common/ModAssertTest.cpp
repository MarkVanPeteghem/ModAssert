//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "ModAssertTest.h"
#include "richbool/analysis.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "StubLogger.h"

// include this just for auto linking:
#include "modassert/consolehandler.hpp"

#ifdef RICHBOOL_USE_WX
	#include <wx/wfstream.h>
	#include <wx/txtstrm.h>
	static wxFFileOutputStream output( stderr );
	static wxTextOutputStream out(output);
#else
	#include <iostream>
	static std::ostream &out = std::cerr;
#endif

ModAssertTest::ModAssertTest(const char *name_): name(name_), next(0), loggerCalled(false)
{
	// add to the linked list
	next = tests;
	tests = this;
	++nrTests;
}

static StubLogger stubLogger;

ModAssertTest *ModAssertTest::tests=0;
int ModAssertTest::nrTests=0;

bool CheckLoggerCalled()
{
	return stubLogger.CheckCalled();
}

void ModAssertTest::RunTests()
{
	ModAssert::AddLogger(&stubLogger);
	for (ModAssertTest *test=tests; test; test=test->next)
	{
		stubLogger.Clear();
		//out << "running " << test->GetName() << "\r\n";
		test->run();
	}
	ModAssert::RemoveLogger(&stubLogger);
}

static ModAssertTestHandler s_modAssertTestHandler;
static int s_nrErrors=0, s_nrMetaAssertions=0;

struct StreamGroupList
{
	StreamGroupList(const ModAssert::GroupList *groupList): m_groupList(groupList) {}
	const ModAssert::GroupList *m_groupList;
};

#if defined(RICHBOOL_USE_WX) && !defined(_MSC_VER)
/*wxTextOutputStream& operator<<(wxTextOutputStream& os, size_t n)
{
	os << (wxUint32)n;
	return os;
}*/
#endif

RB_CONVERSION_HEADER(StreamGroupList)
{
	if (val.m_groupList)
	{
		for (size_t idx=0; idx<val.m_groupList->GetSize(); ++idx)
		{
			str << '(' << idx << ") ";
			const RichBool::detail::String &name = val.m_groupList->GetName(idx);
			for (size_t i=0; (i<20) && (i<name.size()); ++i)
				str << name[i];
			str << '\n';
		}
	}
	else
		str << "NULL";

	return str;
}

struct StreamStringArray
{
	StreamStringArray(const RichBool::detail::StringArray &strArray): m_strArray(&strArray) {}
	const RichBool::detail::StringArray *m_strArray;
};

RB_CONVERSION_HEADER(StreamStringArray)
{
	for (size_t idx=0; idx<RichBool::detail::array_size(*val.m_strArray); ++idx)
		str << '(' << idx << ") " << (*val.m_strArray)[idx] << '\n';

	return str;
}

ModAssertTestHandler::ModAssertTestHandler(): m_analysis(0), m_condition(0),
	m_context(0, -1, 0), m_isCheck(false), m_isUnconditional(false),
    m_expectFailure(false), m_parList(0),
	m_groupList(0), m_level(undefinedLevel), m_action(0)
{}

void ModAssertTestHandler::Activate()
{
	ModAssert::SetResponder(&s_modAssertTestHandler);
}

template<typename T>
bool same(const T *t1, const T *t2)
{
	if (!t1 && !t2)
		return true;
	if (!t1 || !t2)
		return false;

	return *t1 == *t2;
}

bool same_analysis(RichBool::SharedAnalysis analysis1, RichBool::SharedAnalysis analysis2)
{
	if (!analysis1 && !analysis2)
		return true;
	if (!analysis1 || !analysis2)
		return false;

	return *analysis1 == *analysis2;
}

bool sameType(const ModAssert::GroupList *groupList1,
			  const RichBool::detail::StringArray &groupList2)
{
	const bool firstEmpty = !groupList1 || (groupList1->GetSize()==0);
	if (firstEmpty && !RichBool::detail::array_size(groupList2))
		return true;
	if (firstEmpty || !RichBool::detail::array_size(groupList2))
		return false;
	if (groupList1->GetSize()!=RichBool::detail::array_size(groupList2))
		return false;

	for (size_t idx=0; idx<groupList1->GetSize(); ++idx)
		if (groupList1->GetName(idx)!=groupList2[idx])
			return false;

	return true;
}

bool same_sz(const char *sz1, const char *sz2)
{
	if (!sz1 && !sz2)
		return true;
	if (!sz1 || !sz2)
		return false;

	return strcmp(sz1, sz2)==0;
}

void LogSz(const char *sz, const char *msg)
{
	if (sz)
		out << sz;
	else
		out << msg;
}

template<typename T>
void Log(const T t, const char *msg)
{
	if (t)
		out << *t;
	else
		out << msg;
}

ModAssert::Response ModAssertTestHandler::OnAssert(
							const ModAssert::Properties & prop,
							const ModAssert::Result &result,
							bool display) const
{
	if (!display)
		return ModAssert::Response(0);

	if (active)
	{
		out << prop.GetContext() << " error: multiple threads" << '\n';
		++s_nrErrors;
		return response;
	}
	active = true;

	if (ignoreAssertions)
	{
		// we only come here if we're testing thread safety
		static RichBool::detail::String str;
		str += "waste some time";

		active = false;
		return response;
	}

	if (m_expectFailure)
		CheckAssertion(result.Succeeded(), prop.GetCategory()->IsCheck(), prop.IsUnconditional(),
			prop.GetContext(),
			prop.GetCondition(), result.GetAnalysis(), result.GetParameterList(),
			prop.GetGroupList(), prop.GetOptional());
	else
		ReportUnexpectedAssertion(result.Succeeded(), prop.GetCategory()->IsCheck(), prop.IsUnconditional(),
			prop.GetContext(),
			prop.GetCondition(), result.GetAnalysis(), result.GetParameterList(),
			prop.GetGroupList(), prop.GetOptional());

	m_expectFailure = false;

	active = false;

	return response;
}

void ModAssertTestHandler::CheckAssertion(bool success,
										  bool isCheck,
										  bool isUnconditional,
										  const ModAssert::Context &context,
										  const char* condition,
										  const RichBool::SharedAnalysis analysis,
										  const ModAssert::ParameterList *parList,
										  const ModAssert::GroupList *groupList,
										  const char *actionName) const
{
	bool err = false;

	if (m_success!=success)
	{
		if (success)
			out << "expected failure but was success\n";
		else
			out << "expected success but was failure\n";
		err = true;
	}

	if (!(m_isCheck==isCheck))
	{
		if (isCheck)
			out << "expected no check but was check\n";
		else
			out << "expected check but was not a check\n";
		err = true;
	}

	if (!(m_isUnconditional==isUnconditional))
	{
		if (isUnconditional)
			out << "expected no unconditional but was unconditional\n";
		else
			out << "expected unconditional but was not unconditional\n";
		err = true;
	}

	if (!same_sz(m_condition, condition))
	{
		out << "wrong condition:\n  "
			<< "expected " << (m_condition ? m_condition: "no condition") << "\n"
			<< "     was " << (condition ? condition: "no condition") << "\n";
		err = true;
	}

	if (!same_analysis(m_analysis, analysis))
	{
		out << "wrong analysis:" << '\n'
			<< "expected ";
		Log(m_analysis, "no analysis");
		out << '\n' << "     was ";
		Log(analysis, "no analysis");
		out << '\n';
		err = true;
	}

	if (!same(m_parList, parList))
	{
		out << "wrong parList:" << '\n'
			<< "  expected ";
		Log(m_parList, "no parList");
		out << '\n' << "       was ";
		Log(parList, "no parList");
		out << '\n';
		err = true;
	}

	if (!sameType(groupList, m_groupList))
	{
		out << "wrong type:\n"
			<< "  expected " << StreamStringArray(m_groupList) << "\n"
			<< "  but was  " << StreamGroupList(groupList) << "\n";
		err = true;
	}

	if ( (m_level!=undefinedLevel) && (m_level!=groupList->GetLevel()) )
	{
		out << "wrong level:\n"
			<< "expected " << m_level << "\n"
			<< "but was  " << groupList->GetLevel() << "\n";
		err = true;
	}

	if (!same_sz(m_action, actionName))
	{
		out << "wrong action:\n  "
			<< "  expected " << (m_action ? m_action : "no action") << "\n"
			<< "       was " << (actionName ? actionName : "no action") << "\n";
		err = true;
	}

	if (err)
	{
		out << m_context << " expected assert doesn't match\n";
		out << context << " see assert\n";
		++s_nrErrors;
	}
}

void ModAssertTestHandler::ReportUnexpectedAssertion(bool success,
													 bool isCheck,
													 bool isUnconditional,
													 const ModAssert::Context &context,
													 const char* condition,
													 const RichBool::SharedAnalysis analysis,
													 const ModAssert::ParameterList *parmList,
													 const ModAssert::GroupList *groupList,
													 const char *) const
{
	out << "got "
		<< (success ? "succeeding " : "failing ")
		<< (isUnconditional ? "unconditional " : "")
		<< (isCheck ? "check " : "assertion ")
		<< '\n';
	LogSz(condition, "no condition");
	out << '\n';
	Log(analysis, "no analysis");
	out << '\n';
	Log(parmList, "no expressions");
	out << '\n';
	for (size_t t=0; t<groupList->GetSize(); ++t)
		out << groupList->GetName(t) << '\n';
	out << context << " error: unexpected assertion\n";
	++s_nrErrors;
}

void ModAssertTestHandler::SetExpectedFailure(bool success,
											  bool isCheck,
											  bool isUnconditional,
											  const ModAssert::Context &context,
											  const char* condition,
											  const RichBool::SharedAnalysis analysis,
											  const ModAssert::ParameterList *parList,
											  const ModAssert::GroupList &groupList,
											  int level,
											  const char *action)
{
	if (s_modAssertTestHandler.m_expectFailure)
	{
		out << s_modAssertTestHandler.m_context
			<< " error: expected failure not raised\n";
		++s_nrErrors;
	}

	s_modAssertTestHandler.m_success = success;
	s_modAssertTestHandler.m_isCheck = isCheck;
	s_modAssertTestHandler.m_isUnconditional = isUnconditional;
	s_modAssertTestHandler.m_context = context;
	s_modAssertTestHandler.m_condition = condition;
	s_modAssertTestHandler.m_analysis = analysis;
	s_modAssertTestHandler.m_parList = parList;

	RichBool::detail::clear(s_modAssertTestHandler.m_groupList);
	for (size_t group=0; group<groupList.GetSize(); ++group)
	{
		RichBool::detail::AddString(s_modAssertTestHandler.m_groupList,
			groupList.GetName(group));
	}

	s_modAssertTestHandler.m_level = level;

	s_modAssertTestHandler.m_action = action;

	s_modAssertTestHandler.m_expectFailure = true;
}

void ModAssertTestHandler::ExpectNoFailure(const ModAssert::Context &context)
{
	if (s_modAssertTestHandler.m_expectFailure)
	{
		out << s_modAssertTestHandler.m_context
			<< " error: expected failure not raised\n";
		s_modAssertTestHandler.m_expectFailure = false;

		++s_nrErrors;
	}

	s_modAssertTestHandler.m_context = context;
}

int ModAssertTestHandler::GetNrErrors()
{
	return s_nrErrors;
}

void ModAssertTestHandler::IncNrMetaAsserts()
{
	++s_nrMetaAssertions;
}

int ModAssertTestHandler::GetNrMetaAsserts()
{
	return s_nrMetaAssertions;
}

void ModAssertTestHandler::SetIgnoreAssertions(bool ignore)
{
	ignoreAssertions = ignore;
}

ModAssert::Response ModAssertTestHandler::response = (ModAssert::Response)0;
bool ModAssertTestHandler::ignoreAssertions = false;
bool ModAssertTestHandler::active = false;

void MetaFailure(const char *condition,
				 RichBool::SharedAnalysis analysis,
				 const ModAssert::Context &context)
{
	out << context << " error: condition '" << condition << "' failed\n";
	if (analysis)
		out << "  analysis: " << *analysis << '\n';
	++s_nrErrors;
}

void MetaFailure(const char *condition,
				 RichBool::SharedAnalysis analysis,
				 const ModAssert::Context &context,
				 const ModAssert::ParameterList *parList)
{
	out << context << " error: condition '" << condition << "' failed\n";
	if (analysis)
		out << "  analysis: " << *analysis << '\n';
	if (parList)
	{
		out << *parList;
	}
	++s_nrErrors;
}

static bool allowBreakIntoDebugger=false;

void SetAllowBreakIntoDebugger(bool b)
{
	allowBreakIntoDebugger = b;
}

bool GetAllowBreakIntoDebugger()
{
	return allowBreakIntoDebugger;
}

int GetRichboolLevel()
{
	return 2;
}
