//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_LEVEL 3

#include "ModAssertTest.h"
#include "richbool/richbool.hpp"


// we use these macro defintions to make sure that the
// template functions in TestIfTypeReports.hpp have different
// names wherever they are used,
// because they are different as a consequence of the different
// definitions of MOD_ASSERT_LEVEL and MOD_CHECK_LEVEL

#define TestIfAssertDisabled TestIfAssertDisabledA1
#define TestIfCheckDisabled TestIfCheckDisabledA1
#define TestIfAssertEnabled TestIfAssertEnabledA1
#define TestIfCheckEnabled TestIfCheckEnabledA1

#include "TestIfTypeReports.hpp"


// MOD_ASSERT_LEVEL is defined to be 3.
// This means that assertions with type ModAssert::Info,
// ModAssert::Warning and ModAssert::Error are disabled.


MA_TEST(Assert_Level2_NoTypeSpecified)
{
	// Since ModAssert::Error is added implicitly if no level is specified,
	// assertions without a type are also disabled.

	int a=1;

	EXPECT_NO_FAILURE;

	MOD_ASSERT(++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_P(a, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_O(++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_PO(a, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	a=1;

	// the condition in MOD_VERIFY* should still be evaluated,
	// so a should increase

	MOD_VERIFY(++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));

	MOD_VERIFY_P(a, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	MOD_VERIFY_O(++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 4));

	MOD_VERIFY_PO(a, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	a=1;

	// the condition in MOD_CHECK* should still be evaluated,
	// so a should increase
	// the condition always fails, so it's increased twice

	EXPECT_CHECK(false, "++a==0", NULL, NULL, NULL);
	MOD_CHECK(++a==0, ++a);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	EXPECT_CHECK(false, "++a==0", NULL, CreateParameterList()("a", a+1), NULL);
	MOD_CHECK_P(a, ++a==0, ++a);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	EXPECT_CHECK(false, "++a==0", NULL, NULL, "++a");
	MOD_CHECK_O(++a, "++a", ++a==0, ++a);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 7));

	EXPECT_CHECK(false, "++a==0", NULL, CreateParameterList()("a", a+1), "++a");
	MOD_CHECK_PO(a, ++a, "++a", ++a==0, ++a);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 9));

}

MA_TEST(AssertLevel3_Levels)
{
	if (!MOD_ASSERT_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfAssertDisabled(ModAssert::Info);
	TestIfAssertDisabled(ModAssert::Warning);
	TestIfAssertDisabled(ModAssert::Error);
	TestIfAssertEnabled (ModAssert::Fatal);
}

MA_TEST(AssertLevel3_Groups)
{
	if (!MOD_ASSERT_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfAssertDisabled(modAssertGroupOn1);
	TestIfAssertDisabled(modAssertGroupOn1 && modAssertGroupOn2);
	TestIfAssertDisabled(modAssertGroupOn1 || modAssertGroupOn2);
	TestIfAssertDisabled(modAssertGroupOff);
}

MA_TEST(AssertLevel3_GroupsAndLevels)
{
	if (!MOD_ASSERT_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfAssertDisabled(modAssertGroupOn1 % ModAssert::Error);
	TestIfAssertDisabled((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Error);
	TestIfAssertDisabled(modAssertGroupOff % ModAssert::Error);

	TestIfAssertEnabled (modAssertGroupOn1 % ModAssert::Fatal);
	TestIfAssertEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Fatal);
	TestIfAssertDisabled(modAssertGroupOff % ModAssert::Fatal);
}
