//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_CHECK_LEVEL 1

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


// MOD_CHECK_LEVEL is defined to be 1.
// This means that checks with type ModAssert::Info are disabled.

MA_TEST(Check_LevelDisabled)
{
	if (MOD_ASSERT_REPORTS)
	{
		TestIfAssertEnabled(ModAssert::Info);
		TestIfAssertEnabled(ModAssert::Warning);
		TestIfAssertEnabled(ModAssert::Error);
	}

	if (MOD_CHECK_REPORTS)
	{
		TestIfCheckDisabled(ModAssert::Info);
		TestIfCheckEnabled (ModAssert::Warning);
		TestIfCheckEnabled (ModAssert::Error);
	}
}
