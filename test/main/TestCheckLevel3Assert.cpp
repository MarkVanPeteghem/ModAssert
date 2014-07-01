//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_CHECK_LEVEL 3

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



// MOD_CHECK_LEVEL is defined to be 3.
// This means that checks with type ModAssert::Info,
// ModAssert::Warning and ModAssert::Error are disabled,
// but assertions are enabled

MA_TEST(Check_TypeSpecified_Assert)
{
	if (!MOD_ASSERT_REPORTS)
		return;

	ModAssert::Group<ModAssert::ReportFailure>  modAssertGroupOn1("on1"), modAssertGroupOn2("on2");
	ModAssert::Group<ModAssert::ReportNone> modAssertGroupOff("off");

	TestIfAssertEnabled (ModAssert::Info);
	TestIfAssertEnabled (ModAssert::Warning);
	TestIfAssertEnabled (ModAssert::Error);
	TestIfAssertEnabled (ModAssert::Fatal);

	TestIfAssertEnabled (modAssertGroupOn1);
	TestIfAssertEnabled (modAssertGroupOn1 && modAssertGroupOn2);
	TestIfAssertEnabled (modAssertGroupOn1 || modAssertGroupOn2);
	TestIfAssertDisabled(modAssertGroupOff);

	TestIfAssertEnabled (modAssertGroupOn1 % ModAssert::Error);
	TestIfAssertEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Error);
	TestIfAssertDisabled(modAssertGroupOff % ModAssert::Error);

	TestIfAssertEnabled (modAssertGroupOn1 % ModAssert::Fatal);
	TestIfAssertEnabled ((modAssertGroupOn1 && modAssertGroupOn2) % ModAssert::Fatal);
	TestIfAssertDisabled(modAssertGroupOff % ModAssert::Fatal);
}
