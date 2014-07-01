//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif



// Test whether MOD_ASSERT_DONT_REPORT_FILE overrides MOD_ASSERT_REPORT:
// (normally MOD_ASSERT_REPORT is defined application wide, not in a
// source file, but here we do it in a source file to make testing easier)
#ifndef MOD_ASSERT_REPORT
#define MOD_ASSERT_REPORT
#endif
#define MOD_ASSERT_DONT_REPORT_FILE
#include "modassert/assert.hpp"
#include "richbool/richbool.hpp"

#include "ModAssertTest.h"

MA_TEST(AssertDontReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS==0);

	EXPECT_NO_FAILURE;
	MOD_FAIL;
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(VerifyVDontReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS==0);

	EXPECT_NO_FAILURE;
	int a = MOD_VERIFY_V(0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a,0));
}

MA_TEST(VerifyVWithRichBoolean_DontReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS==0);

	EXPECT_NO_FAILURE;
	int a = MOD_VERIFY_V(rbvMORE(1,2));
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a,1));
}

MA_TEST(VerifyV_Nested_PassBoth_DontReportFile)
{
	EXPECT_NO_FAILURE;

	int a=2;

	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,3));
}

MA_TEST(VerifyV_Nested_FailFirst_DontReportFile)
{
	int a=0;

	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,1));
}


MA_TEST(VerifyV_Nested_FailSecond_DontReportFile)
{
	int a=-1;

	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,0));
}

MA_TEST(VerifyBDontReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS==0);

	EXPECT_NO_FAILURE;
	bool b = MOD_VERIFY_B(false);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(!b);
}

MA_TEST(VerifyBWithRichBoolean_DontReportFile)
{
	META_ASSERT(MOD_ASSERT_REPORTS==0);

	EXPECT_NO_FAILURE;
	bool b = MOD_VERIFY_B(rbvMORE(1,2));
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(!b);
}

MA_TEST(VerifyB_Nested_PassBoth_DontReportFile)
{
	EXPECT_NO_FAILURE;

	int a=2;

	bool b = MOD_VERIFY_B(MOD_VERIFY_B(a==2));
	META_ASSERT(b);
}

MA_TEST(VerifyB_Nested_FailFirst_DontReportFile)
{
	int a=0;

	bool b = MOD_VERIFY_B(!MOD_VERIFY_B(a==0));
	META_ASSERT(!b);
}


MA_TEST(VerifyB_Nested_FailSecond_DontReportFile)
{
	int a=1;

	bool b = MOD_VERIFY_B(!MOD_VERIFY_V(a==0));
	META_ASSERT(b);
}
