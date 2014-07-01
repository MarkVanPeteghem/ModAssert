//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif



// Test whether MOD_ASSERT_REPORT_FILE overrides MOD_ASSERT_DONT_REPORT:
// (normally MOD_ASSERT_DONT_REPORT is defined application wide, not in a
// source file, but here we do it in a source file to make testing easier)
#define MOD_ASSERT_DONT_REPORT
#define MOD_ASSERT_REPORT_FILE
#include "modassert/assert.hpp"

#include "ModAssertTest.h"
#include "richbool/richbool.hpp"

MA_TEST(AssertReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS!=0);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;
	META_ASSERT(CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyV_ReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS!=0);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_VERIFY_V(false);
	META_ASSERT(CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyB_ReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS!=0);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	bool rv=MOD_VERIFY_B(false);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(!rv);

	EXPECT_NO_FAILURE;
}
