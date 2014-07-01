//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "StubLogger.h"
#include "StubHook.h"
#include "modassert/filters.hpp"
#include "modassert/category.hpp"
#include "modassert/categories.hpp"
#include "modassert/logtype.hpp"
#include "richbool/richbool.hpp"

static ModAssert::Group<ModAssert::ReportFailure> Enabled("enabled");
static ModAssert::Group<ModAssert::ReportNone> Disabled("disabled");

// test for Filter for Responder

MA_TEST(FilterForResponder_Fail)
{
	ModAssert::SetDisplayFilter(&ModAssert::filterIfFailed);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::SetDisplayFilter(NULL);
}

MA_TEST(FilterForResponder_Pass)
{
	ModAssert::SetDisplayFilter(&ModAssert::filterIfFailed);

	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(ModAssert::IfSuccess, true);

	ModAssert::SetDisplayFilter(NULL);
}

// test for Filter for Logger

MA_TEST(FilterForLogger_Fail)
{
	StubLogger stubLogger;

	ModAssert::AddLogger(&stubLogger, &ModAssert::filterIfFailed);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}

MA_TEST(FilterForLogger_Pass)
{
	StubLogger stubLogger;

	ModAssert::AddLogger(&stubLogger, &ModAssert::filterIfFailed);

	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess, true);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}

// test for Filter for Logger with FilterInFile

MA_TEST(FilterForLogger_InFile)
{
	StubLogger stubLogger;

	ModAssert::FilterInFile filterInFile(__FILE__);
	ModAssert::AddLogger(&stubLogger, &filterInFile);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}

MA_TEST(FilterForLogger_NotInFile)
{
	StubLogger stubLogger;

	ModAssert::FilterInFile filterInFile("otherfile.cpp");
	ModAssert::AddLogger(&stubLogger, &filterInFile);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}

// test for Filter for Hook

MA_TEST(FilterForHook_Fail)
{
	StubHook stubHook;

	ModAssert::FilterIfFailed ifFailed;

	ModAssert::AddHook(&stubHook, &ifFailed);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(stubHook.CheckCalled());

	ModAssert::RemoveHook(&stubHook);
}

MA_TEST(FilterForHook_Pass)
{
	StubHook stubHook;

	ModAssert::FilterIfFailed ifFailed;

	ModAssert::AddHook(&stubHook, &ifFailed);

	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess, true);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!stubHook.CheckCalled());

	ModAssert::RemoveHook(&stubHook);
}

ModAssert::Category<ModAssert::Assertions> ah;
ModAssert::Category<ModAssert::Checks> ch;

ModAssert::Properties assertion(&ah, ModAssert::Context(__FILE__, __LINE__, 0), 0, 0, 0),
	check(&ch, ModAssert::Context(__FILE__, __LINE__, 0), 0, 0, 0);

ModAssert::Result failed(false, 0, 0), success(true, 0, 0);

// test for filterIfFailed

MA_TEST(FilterIfFailed)
{
	META_ASSERT(
		ModAssert::filterIfFailed.Accept(assertion, failed)
	);

	META_ASSERT(
		!ModAssert::filterIfFailed.Accept(assertion, success)
	);
}

// test for filterIfFailed

MA_TEST(FilterIfSuccess)
{
	META_ASSERT(
		!ModAssert::filterIfSuccess.Accept(assertion, failed)
	);

	META_ASSERT(
		ModAssert::filterIfSuccess.Accept(assertion, success)
	);
}

// test for filterIfAssertion

MA_TEST(FilterIfAssertion)
{
	META_ASSERT(
		ModAssert::filterIfAssertion.Accept(assertion, failed)
	);

	META_ASSERT(
		!ModAssert::filterIfAssertion.Accept(check, failed)
	);
}

// test for filterIfNotAssertion

MA_TEST(FilterIfNotAssertion)
{
	META_ASSERT(
		!ModAssert::filterIfNotAssertion.Accept(assertion, failed)
	);

	META_ASSERT(
		ModAssert::filterIfNotAssertion.Accept(check, failed)
	);
}

// test for filterIfCheck

MA_TEST(FilterIfCheck)
{
	META_ASSERT(
		!ModAssert::filterIfCheck.Accept(assertion, failed)
	);

	META_ASSERT(
		ModAssert::filterIfCheck.Accept(check, failed)
	);
}

// test for filterIfNotCheck

MA_TEST(FilterIfNotCheck)
{
	META_ASSERT(
		ModAssert::filterIfNotCheck.Accept(assertion, failed)
	);

	META_ASSERT(
		!ModAssert::filterIfNotCheck.Accept(check, failed)
	);
}

// test for FilterIfHasGroup

MA_TEST(FilterIfHasGroup)
{
	ModAssert::Group<ModAssert::ReportFailure> group1("group1"), group2("group2");

	ModAssert::FilterIfHasGroup ifHasGroup("group1");

	const ModAssert::GroupList &groupList1 = ModAssert::MakeGroupList(group1);
	ModAssert::Properties prop1(0, MOD_ASSERT_CONTEXT, 0, &groupList1, 0);
	META_ASSERT(ifHasGroup.Accept(prop1, failed));

	const ModAssert::GroupList &groupList2 = ModAssert::MakeGroupList(group2);
	ModAssert::Properties prop2(0, MOD_ASSERT_CONTEXT, 0, &groupList2, 0);
	META_ASSERT(!ifHasGroup.Accept(prop2, failed));
}

// test FilterMinimumLevel

MA_TEST(FilterMinimumLevel)
{
	ModAssert::FilterMinimumLevel filterMinimumLevel(ModAssert::Error);

	const ModAssert::GroupList &groupW = ModAssert::MakeGroupList(ModAssert::Warning);
	ModAssert::Properties propW(0, MOD_ASSERT_CONTEXT, 0, &groupW, 0);
	META_ASSERT(!filterMinimumLevel.Accept(propW, failed));

	const ModAssert::GroupList &groupE = ModAssert::MakeGroupList(ModAssert::Error);
	ModAssert::Properties propE(0, MOD_ASSERT_CONTEXT, 0, &groupE, 0);
	META_ASSERT(filterMinimumLevel.Accept(propE, failed));

	const ModAssert::GroupList &groupF = ModAssert::MakeGroupList(ModAssert::Fatal);
	ModAssert::Properties propF(0, MOD_ASSERT_CONTEXT, 0, &groupF, 0);
	META_ASSERT(filterMinimumLevel.Accept(propF, failed));
}

MA_TEST(FilterMinimumLevel_Description)
{
	ModAssert::FilterMinimumLevel filterMinimumLevel(ModAssert::Error);
	META_ASSERT(rbEQUAL(filterMinimumLevel.GetDescription(), "level >= 2"));

	filterMinimumLevel.SetLevel(1);
	META_ASSERT(rbEQUAL(filterMinimumLevel.GetDescription(), "level >= 1"));
}

// test FilterMaximumLevel

MA_TEST(FilterMaximumLevel)
{
	ModAssert::FilterMaximumLevel filterMaximumLevel(ModAssert::Error);

	const ModAssert::GroupList &groupW = ModAssert::MakeGroupList(ModAssert::Warning);
	ModAssert::Properties propW(0, MOD_ASSERT_CONTEXT, 0, &groupW, 0);
	META_ASSERT(filterMaximumLevel.Accept(propW, failed));

	const ModAssert::GroupList &groupE = ModAssert::MakeGroupList(ModAssert::Error);
	ModAssert::Properties propE(0, MOD_ASSERT_CONTEXT, 0, &groupE, 0);
	META_ASSERT(filterMaximumLevel.Accept(propE, failed));

	const ModAssert::GroupList &groupF = ModAssert::MakeGroupList(ModAssert::Fatal);
	ModAssert::Properties propF(0, MOD_ASSERT_CONTEXT, 0, &groupF, 0);
	META_ASSERT(!filterMaximumLevel.Accept(propF, failed));
}

MA_TEST(FilterMaximumLevel_Description)
{
	ModAssert::FilterMaximumLevel filterMaximumLevel(ModAssert::Error);
	META_ASSERT(rbEQUAL(filterMaximumLevel.GetDescription(), "level <= 2"));

	filterMaximumLevel.SetLevel(1);
	META_ASSERT(rbEQUAL(filterMaximumLevel.GetDescription(), "level <= 1"));
}

// test FilterInFile

MA_TEST(FilterInFile)
{
	ModAssert::FilterInFile filterInFile(__FILE__);

	ModAssert::Context context1 = MOD_ASSERT_CONTEXT;
	ModAssert::Properties prop1(0, context1, 0, 0, 0);
	META_ASSERT(filterInFile.Accept(prop1, failed));

	ModAssert::Context context2("otherfile", 1, 0);
	ModAssert::Properties prop2(0, context2, 0, 0, 0);
	META_ASSERT(!filterInFile.Accept(prop2, failed));
}

// test FilterLogType

static const ModAssert::LogType logAtBegin(ModAssert::LogType::AtBegin),
	logAtEnd(ModAssert::LogType::AtEnd),
	logInBetween(ModAssert::LogType::InBetween);

MA_TEST(FilterLogTypeNoAssertions)
{
	ModAssert::FilterLogType filter(false, true, true, true);

	META_ASSERT(!filter.Accept(assertion, failed));
	META_ASSERT(filter.Accept(logAtBegin));
	META_ASSERT(filter.Accept(logAtEnd));
	META_ASSERT(filter.Accept(logInBetween));
}

MA_TEST(FilterLogTypeNotAtBegin)
{
	ModAssert::FilterLogType filter(true, false, true, true);

	META_ASSERT(filter.Accept(assertion, failed));
	META_ASSERT(!filter.Accept(logAtBegin));
	META_ASSERT(filter.Accept(logAtEnd));
	META_ASSERT(filter.Accept(logInBetween));
}

MA_TEST(FilterLogTypeNotAtEnd)
{
	ModAssert::FilterLogType filter(true, true, false, true);

	META_ASSERT(filter.Accept(assertion, failed));
	META_ASSERT(filter.Accept(logAtBegin));
	META_ASSERT(!filter.Accept(logAtEnd));
	META_ASSERT(filter.Accept(logInBetween));
}

MA_TEST(FilterLogTypeNotInBetween)
{
	ModAssert::FilterLogType filter(true, true, true, false);

	META_ASSERT(filter.Accept(assertion, failed));
	META_ASSERT(filter.Accept(logAtBegin));
	META_ASSERT(filter.Accept(logAtEnd));
	META_ASSERT(!filter.Accept(logInBetween));
}


// tests for FilterNot

MA_TEST(FilterNot_Fail)
{
	StubLogger stubLogger;

	ModAssert::FilterIfFailed ifFailed;
	ModAssert::FilterNot ifSuccess(ifFailed);

	ModAssert::AddLogger(&stubLogger, &ifSuccess);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}

MA_TEST(FilterNot_Pass)
{
	StubLogger stubLogger;

	ModAssert::FilterIfFailed ifFailed;
	ModAssert::FilterNot ifSuccess(ifFailed);

	ModAssert::AddLogger(&stubLogger, &ifSuccess);

	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess, true);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(stubLogger.CheckCalled());

	ModAssert::RemoveLogger(&stubLogger);
}


// test for FilterAnd

MA_TEST(FilterAnd)
{
	ModAssert::FilterIfFailed filterIfFailed;
	ModAssert::FilterMinimumLevel filterMinimumLevel(ModAssert::Error);

	ModAssert::FilterAnd filterAnd(filterIfFailed, filterMinimumLevel);

	const ModAssert::GroupList &groupW = ModAssert::MakeGroupList(ModAssert::Warning);
	const ModAssert::GroupList &groupE = ModAssert::MakeGroupList(ModAssert::Error);

	ModAssert::Properties
		propW(0, MOD_ASSERT_CONTEXT, 0, &groupW, 0),
		propE(0, MOD_ASSERT_CONTEXT, 0, &groupE, 0);

	ModAssert::Result
		resultF(false, 0, 0), resultS(true, 0, 0);

	META_ASSERT( filterAnd.Accept(propE, resultF));
	META_ASSERT(!filterAnd.Accept(propE, resultS));
	META_ASSERT(!filterAnd.Accept(propW, resultF));
	META_ASSERT(!filterAnd.Accept(propW, resultS));
}


// test for FilterOr

MA_TEST(FilterOr)
{
	ModAssert::FilterIfFailed filterIfFailed;
	ModAssert::FilterMinimumLevel filterMinimumLevel(ModAssert::Error);

	ModAssert::FilterOr filterOr(filterIfFailed, filterMinimumLevel);

	const ModAssert::GroupList &groupW = ModAssert::MakeGroupList(ModAssert::Warning);
	const ModAssert::GroupList &groupE = ModAssert::MakeGroupList(ModAssert::Error);

	ModAssert::Properties
		propW(0, MOD_ASSERT_CONTEXT, 0, &groupW, 0),
		propE(0, MOD_ASSERT_CONTEXT, 0, &groupE, 0);

	ModAssert::Result
		resultF(false, 0, 0), resultS(true, 0, 0);

	META_ASSERT( filterOr.Accept(propE, resultF));
	META_ASSERT( filterOr.Accept(propE, resultS));
	META_ASSERT( filterOr.Accept(propW, resultF));
	META_ASSERT(!filterOr.Accept(propW, resultS));
}

MA_TEST(Filter_BadValue)
{
	RichBool::SharedAnalysis eq = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		.expr("a", ":")("1", true)(" == ").expr("1", ":")("1", true),
		eqbv = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("*p", ":")(RichBool::PtrToString(0), false)(" == ").expr("1", ":")("1", true);
	ModAssert::Result badValue(false, eqbv, 0), with_an(false, eq, 0);

	META_ASSERT( ModAssert::filterBadValue.Accept(assertion, badValue));
	META_ASSERT(!ModAssert::filterNoBadValue.Accept(assertion, badValue));

	META_ASSERT(!ModAssert::filterBadValue.Accept(assertion, with_an));
	META_ASSERT( ModAssert::filterNoBadValue.Accept(assertion, with_an));

	META_ASSERT(!ModAssert::filterBadValue.Accept(assertion, failed));
	META_ASSERT( ModAssert::filterNoBadValue.Accept(assertion, failed));
}
