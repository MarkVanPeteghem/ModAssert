//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_REPORT_FILE
#define MOD_CHECK_DONT_REPORT_FILE

#include "ModAssertTest.h"


MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_OnOff)
{
	int a=0;
	IF_MOD_ASSERT_REPORTS(int old_a=a;)

	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	MOD_ASSERT(old_a+1==a);
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_MultipleDeclarations_OnOff)
{
	int a=0;

#define DECLARATIONS int old_a=a, new_a=a+1;

	IF_MOD_ASSERT_REPORTS(DECLARATIONS)

	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	MOD_ASSERT(old_a+new_a==a);
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_With_Parameters_And_OptionalAction_OnOff)
{
	int a=0;
	IF_MOD_ASSERT_REPORTS(int old_a=a;)

	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS doesn't work well
	// or parameters or optional actions are still evaluated
	// in MOD_VERIFY* and MOD_CHECK* when assertions are off
	MOD_VERIFY_P(old_a, 1==a);
	MOD_VERIFY_O(++old_a, "inc", 1==a);
	MOD_CHECK_P(old_a, 1==a, ++a);
	MOD_CHECK_O(++old_a, "inc", 1==a, ++a);
}



// same tests for IF_MOD_CHECK_REPORTS:
MA_TEST(Macro_IF_MOD_CHECK_REPORTS_OnOff)
{
	int a=0;
	IF_MOD_CHECK_REPORTS(int old_a=a;)

	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	MOD_CHECK_P(old_a, 1==a, 0);

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	int old_a=0;
	++old_a; // avoid warning
}

MA_TEST(Macro_IF_MOD_CHECK_REPORTS_MultipleDeclarations_OnOff)
{
	int a=0;

#define DECLARATIONS int old_a=a, new_a=a+1;

	IF_MOD_CHECK_REPORTS(DECLARATIONS)

	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	MOD_CHECK_P(old_a << new_a, 1==a, 0);

	// this will give compile error if IF_MOD_CHECK_REPORTS doesn't work well
	int old_a=0;
	++old_a; // avoid warning
}

MA_TEST(Macro_IF_NOT_MOD_ASSERT_REPORTS_OnOff)
{
	int b=1;

	// this will give compile error if IF_NOT_MOD_ASSERT_REPORTS doesn't work well
	IF_NOT_MOD_ASSERT_REPORTS(int b=1;)

	++b;
}

MA_TEST(Macro_IF_MOD_ASSERT_REPORTS_ELSE_OnOff)
{
	int a=1;
	++a;

	// this will give compile error if IF_MOD_ASSERT_REPORTS_ELSE doesn't work well
	IF_MOD_ASSERT_REPORTS_ELSE(int b=1;, int a=1;)

	// this will give compile error if IF_MOD_ASSERT_REPORTS_ELSE doesn't work well
	++b;
}

MA_TEST(Macro_IF_NOT_MOD_CHECK_REPORTS_OnOff)
{
	IF_NOT_MOD_CHECK_REPORTS(int b=1;)

	// this will give compile error if IF_NOT_MOD_CHECK_REPORTS doesn't work well
	++b;
}

MA_TEST(Macro_IF_MOD_CHECK_REPORTS_ELSE_OnOff)
{
	int a=1;
	++a;

	// this will give compile error if IF_MOD_CHECK_REPORTS_ELSE doesn't work well
	IF_MOD_CHECK_REPORTS_ELSE(int a=1;, int b=1;)

	// this will give compile error if IF_MOD_CHECK_REPORTS_ELSE doesn't work well
	++b;
}
