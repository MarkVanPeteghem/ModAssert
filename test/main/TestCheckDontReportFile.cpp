//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif



// Test whether MOD_CHECK_DONT_REPORT_FILE overrides MOD_CHECK_REPORT:
// (normally MOD_CHECK_REPORT is defined application wide, not in a
// source file, but here we do it in a source file to make testing easier)
#define MOD_CHECK_REPORT
#define MOD_CHECK_DONT_REPORT_FILE
#include "modassert/assert.hpp"
#include "richbool/richbool.hpp"

#include "ModAssertTest.h"

struct Inc
{
	Inc(int &n_): n(n_) {}
	int &n;
	void operator()()
	{
		++n;
	}
private:
	Inc& operator=(const Inc &)
	{
		return *this;
	}
};

MA_TEST(CheckDontReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS==0);

	EXPECT_NO_FAILURE;
	MOD_CHECK(false, 0);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(CheckV_DontReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS==0);

	int a=0, n=0;
	Inc inc_a(a);

	EXPECT_NO_FAILURE;
	int rv=MOD_CHECK_V(n, inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(rv,0));
	META_ASSERT(rbEQUAL(a,1));
}

MA_TEST(CheckB_DontReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS==0);

	int n=0;

	EXPECT_NO_FAILURE;
	bool rv=MOD_CHECK_B(n);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(!rv);
}

MA_TEST(CheckV_WithRichBoolean_DontReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS==0);

	int a=0, n=0;
	Inc inc_a(a);

	EXPECT_NO_FAILURE;
	int rv=MOD_CHECK_V(rbvMORE(n,0), inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(rv,0));
	META_ASSERT(rbEQUAL(a,1));
}

MA_TEST(CheckB_WithRichBoolean_DontReportFile)
{
	META_ASSERT(MOD_CHECK_REPORTS==0);

	int n=0;

	EXPECT_NO_FAILURE;
	bool rv=MOD_CHECK_B(rbvMORE(n,0));
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(!rv);
}

MA_TEST(CheckV_Nested_PassBoth_DontReportFile)
{
	EXPECT_NO_FAILURE;

	int a=2;

	int n=0;
	Inc inc_n(n);

	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_n)+1, inc_n);
	META_ASSERT(rbEQUAL(b,3));
	META_ASSERT(rbEQUAL(n,0));
}

MA_TEST(CheckV_Nested_FailFirst_DontReportFile)
{
	int a=0;

	int m=0, n=0;
	Inc inc_m(m), inc_n(n);

	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_m)+1, inc_n);
	META_ASSERT(rbEQUAL(b,1));
    META_ASSERT(rbEQUAL(m,1));
    META_ASSERT(rbEQUAL(n,0));
}


MA_TEST(CheckV_Nested_FailSecond_DontReportFile)
{
	int a=-1;

	int m=0, n=0;
	Inc inc_m(m), inc_n(n);

	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_m)+1, inc_n);
	META_ASSERT(rbEQUAL(b,0));
    META_ASSERT(rbEQUAL(m,0));
    META_ASSERT(rbEQUAL(n,1));
}

MA_TEST(CheckB_Nested_PassBoth_DontReportFile)
{
	EXPECT_NO_FAILURE;

	int a=2;

	bool b = MOD_CHECK_B((bool)MOD_CHECK_B(a));
	META_ASSERT(b);
}

MA_TEST(CheckB_Nested_FailFirst_DontReportFile)
{
	int a=0;

	bool b = MOD_CHECK_B(!MOD_CHECK_B(a));
	META_ASSERT(b);
}


MA_TEST(CheckB_Nested_FailSecond_DontReportFile)
{
	int a=1;

	bool b = MOD_CHECK_B(!MOD_CHECK_B(a));
	META_ASSERT(!b);
}
