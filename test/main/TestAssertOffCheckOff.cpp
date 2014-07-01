//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_DONT_REPORT_FILE
#define MOD_CHECK_DONT_REPORT_FILE

#include "ModAssertTest.h"
#include "richbool/richbool.hpp"

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


MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_OffOff)
{
	int a=0;
	IF_MOD_ASSERT_REPORTS(int old_a=a;)

	++a;

	// this will give compile error if MOD_ASSERT doesn't work well
	MOD_ASSERT(old_a+1==a);

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	int old_a=0;
	++old_a;
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_MultipleDeclarations_OffOff)
{
	int a=0;

#define DECLARATIONS int old_a=a, new_a=a+1;

	IF_MOD_ASSERT_REPORTS(DECLARATIONS)

	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	MOD_ASSERT(old_a+1==a);

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	int old_a=0;
	++old_a;
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_With_Parameters_And_OptionalAction_OffOff)
{
	int a=0;
	++a; // to avoid warning
	IF_MOD_ASSERT_REPORTS(int old_a=a;)

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	int old_a=0;
	++old_a; // to avoid warning
}

MA_TEST(ParametersNotUsedInVerify_OffOff)
{
	int a=1;

	// this will give compile error if
	// parameters or optional actions are still evaluated
	// in MOD_VERIFY* when assertions are off
	// because old_a is not defined
	MOD_VERIFY_P(old_a, 1==a);
	MOD_VERIFY_O(++old_a, "inc", 1==a);

	int b = MOD_VERIFY_VP(old_a, a);
	META_ASSERT(rbEQUAL(b,1));
	int c = MOD_VERIFY_VO(Inc(old_a), "inc", a);
	META_ASSERT(rbEQUAL(c,1));

	int d = MOD_VERIFY_VP(old_a, rbvEQUAL(a,1));
	META_ASSERT(rbEQUAL(d,1));
	int e = MOD_VERIFY_VO(Inc(old_a), "inc", rbvEQUAL(a,1));
	META_ASSERT(rbEQUAL(e,1));
}

MA_TEST(ParametersNotUsedInCheck_OffOff)
{
	int a=1;

	// this will give compile error if
	// parameters or optional actions are still evaluated
	// in MOD_CHECK* when checks are off
	// because old_a is not defined
	MOD_CHECK_P(old_a, 1==a, ++a);
	MOD_CHECK_O(++old_a, "inc", 1==a, ++a);

	int b = MOD_CHECK_VP(old_a, a, Inc(a));
	META_ASSERT(rbEQUAL(b,1));
	int c = MOD_CHECK_VO(Inc(old_a), "inc", a, Inc(a));
	META_ASSERT(rbEQUAL(c,1));

	int d = MOD_CHECK_VP(old_a, rbvEQUAL(a,1), Inc(a));
	META_ASSERT(rbEQUAL(d,1));
	int e = MOD_CHECK_VO(Inc(old_a), "inc", rbvEQUAL(a,1), Inc(a));
	META_ASSERT(rbEQUAL(e,1));
}

// same tests for IF_MOD_CHECK_REPORTS:

MA_TEST(Macro_IF_MOD_CHECK_REPORTS_OffOff)
{
	int a=0;
	IF_MOD_CHECK_REPORTS(int old_a=a;)

	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	MOD_CHECK_P(old_a, 1==a, 0);

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	int old_a=0;
	++old_a;
}

MA_TEST(Macro_IF_MOD_CHECK_REPORTS_MultipleDeclarations_OffOff)
{
	int a=0;

#define DECLARATIONS int old_a=a, new_a=a+1;

	IF_MOD_CHECK_REPORTS(DECLARATIONS)

	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	MOD_CHECK_P(old_a << new_a, 1==a, 0);

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	int old_a=0;
	++old_a;
}

MA_TEST(Macro_IF_NOT_MOD_ASSERT_REPORTS_OffOff)
{
	IF_NOT_MOD_ASSERT_REPORTS(int b=1;)

	// this will give compile error if IF_NOT_MOD_ASSERT_REPORTS doesn't work well
	++b;
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_ELSE_OffOff)
{
	int a=1;
	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS_ELSE doesn't work well
	IF_MOD_ASSERT_REPORTS_ELSE(int a=1;, int b=1;)

	// this will give compile error if IF_MOD_ASSERT_REPORTS_ELSE doesn't work well
	++b;
}

MA_TEST(Macro_IF_NOT_MOD_CHECK_REPORTS_OffOff)
{
	IF_NOT_MOD_CHECK_REPORTS(int b=1;)

	// this will give compile error if IF_NOT_MOD_CHECK_REPORTS doesn't work well
	++b;
}

MA_TEST(Macro_IF_MOD_CHECK_REPORTS_ELSE_OffOff)
{
	int a=1;
	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS_ELSE doesn't work well
	IF_MOD_CHECK_REPORTS_ELSE(int a=1;, int b=1;)

	// this will give compile error if IF_MOD_CHECK_REPORTS_ELSE doesn't work well
	++b;
}
