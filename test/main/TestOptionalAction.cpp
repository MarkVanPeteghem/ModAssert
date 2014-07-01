//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "CreateList.h"
#include "ScopedSetReturnValue.h"
#include "richbool/richbool.hpp"

static int n=2;

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

static Inc inc_n(n);

struct DoubleInt
{
	DoubleInt(int &n_): n(n_) {}
	int &n;
	void operator()()
	{
		n *= 2;
	}
private:
	DoubleInt& operator=(const DoubleInt &)
	{
		return *this;
	}
};


MA_TEST(PassOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	int b=1;

	MOD_ASSERT_O(++b, "++b", n==2);
	MOD_ASSERT_PO(n, ++b, "++b", n==2);

	MOD_VERIFY_O(++b, "++b", n==2);
	MOD_VERIFY_PO(n, ++b, "++b", n==2);

	MOD_CHECK_O(++b, "++b", n==2, ++b);
	MOD_CHECK_PO(n, ++b, "++b", n==2, ++b);

	Inc inc_b(b);

	MOD_VERIFY_VO(inc_b, "++b", n==2);
	MOD_VERIFY_VPO((n), inc_b, "++b", n==2);

	bool rv=false;
	rv=MOD_VERIFY_BO(inc_b, "++b", n==2);
	rv=MOD_VERIFY_BPO((n), inc_b, "++b", n==2);

	MOD_CHECK_VO(inc_b, "++b", n==2, inc_n);
	MOD_CHECK_VPO((n), inc_b, "++b", n==2, inc_n);

	rv=MOD_CHECK_BO(inc_b, "++b", n==2);
	rv=MOD_CHECK_BPO((n), inc_b, "++b", n==2);

	META_ASSERT(b==1);
}



MA_TEST(NoPassOptional_Assert)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	int b=1;

	EXPECT_ASSERT(false, "b==0", NULL, NULL, "++b");
	MOD_ASSERT_O(++b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	MOD_ASSERT_PO(n, ++b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n)("n+1", n+1), "++b");
	MOD_ASSERT_PO(n << n+1, ++b, "++b", b==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(b, 4));
	else
		META_ASSERT(rbEQUAL(b, 1));

	EXPECT_ASSERT(false, "b==0", NULL, NULL, "++b");
	MOD_VERIFY_O(++b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	MOD_VERIFY_PO(n, ++b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n)("n+1", n+1), "++b");
	MOD_VERIFY_PO(n << n+1, ++b, "++b", b==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(b, 7));
	else
		META_ASSERT(rbEQUAL(b, 1));

	Inc inc_b(b);
	DoubleInt db(b);

	b=1;
	EXPECT_ASSERT(false, "b==0", NULL, NULL, "++b");
	MOD_VERIFY_VO(inc_b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	MOD_VERIFY_VPO((n), inc_b, "++b", b==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		// this value of 3 is only obtained if
		// the optional action is done
		META_ASSERT(rbEQUAL(b, 3));
	else
		// this value of 1 is only obtained if
		// the optional action is not evaluated
		META_ASSERT(rbEQUAL(b, 1));

	b=1;
	EXPECT_ASSERT(false, "b==0", NULL, NULL, "++b");
	bool rv=MOD_VERIFY_BO(inc_b, "++b", b==0);
	EXPECT_ASSERT(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	rv=MOD_VERIFY_BPO((n), inc_b, "++b", b==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		// this value of 3 is only obtained if
		// the optional action is done
		META_ASSERT(rbEQUAL(b, 3));
	else
		// this value of 1 is only obtained if
		// the optional action is not evaluated
		META_ASSERT(rbEQUAL(b, 1));
}

MA_TEST(NoPassOptional_Check)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	int b=1;

	EXPECT_CHECK(false, "b==0", NULL, NULL, "++b");
	MOD_CHECK_O(++b, "++b", b==0, b*=2);
	EXPECT_CHECK(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	MOD_CHECK_PO(n, ++b, "++b", b==0, b*=2);
	EXPECT_CHECK(false, "b==0", NULL, CreateParameterList()("n", n)("n+1", n+1), "++b");
	MOD_CHECK_PO(n << n+1, ++b, "++b", b==0, b*=2);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		// this value of 70 is only obtained if
		// the optional action is done BEFORE the fail action
		META_ASSERT(rbEQUAL(b, 22));
	else
		// this value of 8 is only obtained if
		// ONLY the fail action is evaluated
		META_ASSERT(rbEQUAL(b, 8));

	Inc inc_b(b);
	DoubleInt db(b);

	b=1;
	EXPECT_CHECK(false, "b==0", NULL, NULL, "++b");
	MOD_CHECK_VO(inc_b, "++b", b==0, db);
	EXPECT_CHECK(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	MOD_CHECK_VPO((n), inc_b, "++b", b==0, db);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		// this value of 10 is only obtained if
		// the optional action is done BEFORE the fail action
		META_ASSERT(rbEQUAL(b, 10));
	else
		// this value of 4 is only obtained if
		// ONLY the fail action is evaluated
		META_ASSERT(rbEQUAL(b, 4));

	bool rv=false;

	b=1;
	EXPECT_CHECK(false, "b==0", NULL, NULL, "++b");
	rv=MOD_CHECK_BO(inc_b, "++b", b==0);
	EXPECT_CHECK(false, "b==0", NULL, CreateParameterList()("n", n), "++b");
	rv=MOD_CHECK_BPO((n), inc_b, "++b", b==0);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		// this value of 3 is only obtained if
		// the optional action is done
		META_ASSERT(rbEQUAL(b, 3));
	else
		// this value of 1 is only obtained if
		// the optional action is not evaluated
		META_ASSERT(rbEQUAL(b, 1));
}


MA_TEST(FailOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	int b=1;

	EXPECT_FAIL(false, NULL, NULL, NULL, "++b");
	MOD_FAIL_O(++b, "++b");

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("n", n), "++b");
	MOD_FAIL_PO(n, ++b, "++b");

	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "++b");
	MOD_FAIL_GO(ModAssert::Error, ++b, "++b");

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("n", n), ModAssert::Error, "++b");
	MOD_FAIL_PGO(n, ModAssert::Error, ++b, "++b");

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(b, 5));
	else
		META_ASSERT(rbEQUAL(b, 1));
}

MA_TEST(AssertOptionalBreak)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, NULL, "break");
		MOD_ASSERT_O(break, "break", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(AssertOptionalContinue)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, NULL, "continue");
		MOD_ASSERT_O(continue, "continue", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(AssertPOptionalBreak)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	IF_MOD_ASSERT_REPORTS(int p = 1;)
	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, CreateParameterList()("p", p), "break");
		MOD_ASSERT_PO(p, break, "break", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(AssertPOptionalContinue)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	IF_MOD_ASSERT_REPORTS(int p = 1;)
	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, CreateParameterList()("p", p), "continue");
		MOD_ASSERT_PO(p, continue, "continue", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyOptionalBreak)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, NULL, "break");
		MOD_VERIFY_O(break, "break", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyOptionalContinue)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_ASSERT(false, "false", NULL, NULL, "continue");
		MOD_VERIFY_O(continue, "continue", false);
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(FailOptionalBreak)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_FAIL(false, NULL, NULL, NULL, "break");
		MOD_FAIL_O(break, "break");
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(FailOptionalContinue)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	for (int i=0; i<2; ++i)
	{
		EXPECT_FAIL(false, NULL, NULL, NULL, "continue");
		MOD_FAIL_O(continue, "continue");
		MOD_FAIL; // shouldn't be reached if ModAssert is on
	}

	EXPECT_NO_FAILURE;
}

MA_TEST(Fail_MultipleStatements)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	int p=0;

	EXPECT_ASSERT(false, "false", NULL, NULL, "inc");
	MOD_ASSERT_O(++p; ++p;, "inc", false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(p, 2));
	else
		META_ASSERT(rbEQUAL(p, 0));
}

MA_TEST(Pass_MultipleStatements)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	int p=0;

	MOD_ASSERT_O(++p; ++p;, "inc", true);

	META_ASSERT(rbEQUAL(p, 0));

	EXPECT_NO_FAILURE;
}

MA_TEST(Fail_Block)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	int p=0;
	IF_MOD_ASSERT_REPORTS(bool b=true;)

	EXPECT_ASSERT(false, "false", NULL, NULL, "inc");
	MOD_ASSERT_O(
		if (b)
		{
			++p;
			++p;
		},
		"inc",
		false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(p, 2));
	else
		META_ASSERT(rbEQUAL(p, 0));
}

MA_TEST(Pass_Block)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	int p=0;
	IF_MOD_ASSERT_REPORTS(bool b=true;)

	MOD_ASSERT_O(
		if (b)
		{
			++p;
			++p;
		},
		"inc",
		true);

	EXPECT_NO_FAILURE;

	META_ASSERT(rbEQUAL(p, 0));
}

void foo(int , int )
{
}

MA_TEST(Compilable)
{
	MOD_ASSERT_O(
		// check if this compiles:
		int p=0;
		foo(p, 1);

		// this doesn't compile:
		// int p=1, q=2;
		,
		"inc",
		true);

	EXPECT_NO_FAILURE;
}
