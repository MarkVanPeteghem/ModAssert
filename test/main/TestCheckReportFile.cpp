//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif



// Test whether MOD_CHECK_REPORT_FILE overrides MOD_CHECK_DONT_REPORT:
// (normally MOD_CHECK_DONT_REPORT is defined application wide, not in a
// source file, but here we do it in a source file to make testing easier)
#define MOD_CHECK_DONT_REPORT
#define MOD_CHECK_REPORT_FILE
#include "modassert/assert.hpp"

#include "ModAssertTest.h"
#include "richbool/richbool.hpp"

MA_TEST(CheckReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS!=0);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	META_ASSERT(CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}
