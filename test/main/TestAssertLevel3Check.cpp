//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
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
// ModAssert::Warning and ModAssert::Error are disabled,
// but all checks are enabled.


MA_TEST(Assert_TypeSpecified_Check_Levels)
{
	if (!MOD_CHECK_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfCheckEnabled(ModAssert::Info);
	TestIfCheckEnabled(ModAssert::Warning);
	TestIfCheckEnabled(ModAssert::Error);
	TestIfCheckEnabled(ModAssert::Fatal);
}

MA_TEST(Assert_TypeSpecified_Check_Groups)
{
	if (!MOD_CHECK_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfCheckEnabled (modAssertGroupOn1);
	TestIfCheckEnabled (modAssertGroupOn1 && modAssertGroupOn2);
	TestIfCheckEnabled (modAssertGroupOn1 || modAssertGroupOn2);
	TestIfCheckDisabled(modAssertGroupOff);
}

MA_TEST(Assert_TypeSpecified_Check_GroupsWithLevels)
{
	if (!MOD_CHECK_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfCheckEnabled (modAssertGroupOn1 % ModAssert::Warning);
	TestIfCheckEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Warning);
	TestIfCheckDisabled(modAssertGroupOff % ModAssert::Warning);

	TestIfCheckEnabled (modAssertGroupOn1 % ModAssert::Error);
	TestIfCheckEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Error);
	TestIfCheckDisabled(modAssertGroupOff % ModAssert::Error);

	TestIfCheckEnabled (modAssertGroupOn1 % ModAssert::Fatal);
	TestIfCheckEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Fatal);
	TestIfCheckDisabled(modAssertGroupOff % ModAssert::Fatal);
}
