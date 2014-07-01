//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

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

static int gl=0;
static Inc inc_b(gl);
static DoubleInt db(gl);

#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION ++gl
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V inc_b
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT "++gl"

#include "ModAssertTest.h"
#include "CreateList.h"
#include "ScopedSetReturnValue.h"
#include "richbool/richbool.hpp"

static const int n=2;

MA_TEST(PassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);

	gl=1;

	MOD_ASSERT(n==2);
	MOD_ASSERT_P(n, n==2);
	MOD_ASSERT_G(ModAssert::Error, n==2);
	MOD_ASSERT_PG(n, ModAssert::Error, n==2);

	MOD_VERIFY(n==2);
	MOD_VERIFY_P(n, n==2);
	MOD_VERIFY_G(ModAssert::Error, n==2);
	MOD_VERIFY_PG(n, ModAssert::Error, n==2);

	MOD_CHECK(n==2, ++gl);
	MOD_CHECK_P(n, n==2, ++gl);
	MOD_CHECK_G(ModAssert::Error, n==2, ++gl);
	MOD_CHECK_PG(n, ModAssert::Error, n==2, ++gl);

	MOD_CHECK_V(n==2, inc_b);
	MOD_CHECK_VP((n), n==2, inc_b);
	MOD_CHECK_VG(ModAssert::Error, n==2, inc_b);
	MOD_CHECK_VPG((n), ModAssert::Error, n==2, inc_b);

	bool b=false;
	b=MOD_CHECK_B(n==2);
	b=MOD_CHECK_BP((n), n==2);
	b=MOD_CHECK_BG(ModAssert::Error, n==2);
	b=MOD_CHECK_BPG((n), ModAssert::Error, n==2);

	META_ASSERT(gl==1);
}

MA_TEST(ModAssert_NoPassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;

	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++gl");
	MOD_ASSERT(gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_ASSERT_P(n, gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++gl");
	MOD_ASSERT_G(ModAssert::Error, gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_ASSERT_PG(n, ModAssert::Error, gl==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(gl, 5));
	else
		META_ASSERT(rbEQUAL(gl, 1));
}

MA_TEST(Modverify_NoPassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;

	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++gl");
	MOD_VERIFY(gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_VERIFY_P(n, gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++gl");
	MOD_VERIFY_G(ModAssert::Error, gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_VERIFY_PG(n, ModAssert::Error, gl==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(gl, 5));
	else
		META_ASSERT(rbEQUAL(gl, 1));
}

MA_TEST(ModCheck_NoPassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;


	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	MOD_CHECK(gl==0, gl*=2);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_CHECK_P(n, gl==0, gl*=2);
	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	MOD_CHECK_G(ModAssert::Error, gl==0, gl*=2);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_CHECK_PG(n, ModAssert::Error, gl==0, gl*=2);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		// this value of 46 is only obtained if
		// the optional action is done BEFORE the fail action
		META_ASSERT(rbEQUAL(gl, 46));
	else
		// this value of 16 is only obtained if
		// ONLY the fail action is evaluated
		META_ASSERT(rbEQUAL(gl, 16));
}

MA_TEST(ModCheckV_NoPassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;


	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	MOD_CHECK_V(gl==0, db);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_CHECK_VP((n), gl==0, db);
	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	MOD_CHECK_VG(ModAssert::Error, gl==0, db);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	MOD_CHECK_VPG((n), ModAssert::Error, gl==0, db);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		// this value of 46 is only obtained if
		// the optional action is done BEFORE the fail action
		META_ASSERT(rbEQUAL(gl, 46));
	else
		// this value of 16 is only obtained if
		// ONLY the fail action is evaluated
		META_ASSERT(rbEQUAL(gl, 16));
}

MA_TEST(ModCheckB_NoPassDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;

	bool b=false;

	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	b=MOD_CHECK_B(gl==0);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	b=MOD_CHECK_BP((n), gl==0);
	EXPECT_CHECK(false, "gl==0", NULL, NULL, "++gl");
	b=MOD_CHECK_BG(ModAssert::Error, gl==0);
	EXPECT_CHECK(false, "gl==0", NULL, CreateParameterList()("n", n), "++gl");
	b=MOD_CHECK_BPG((n), ModAssert::Error, gl==0);

	EXPECT_NO_FAILURE;

	if (MOD_CHECK_REPORTS)
		META_ASSERT(rbEQUAL(gl, 5));
	else
		// this value of 16 is only obtained if
		// the optional action is not evaluated
		META_ASSERT(rbEQUAL(gl, 1));
}


MA_TEST(FailDefaultOptional)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;

	EXPECT_FAIL(false, NULL, NULL, NULL, "++gl");
	MOD_FAIL;
	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("n", n), "++gl");
	MOD_FAIL_P(n);
	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "++gl");
	MOD_FAIL_G(ModAssert::Error);
	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("n", n), ModAssert::Error, "++gl");
	MOD_FAIL_PG(n, ModAssert::Error);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(gl, 5));
	else
		META_ASSERT(rbEQUAL(gl, 1));
}

MA_TEST(PassDefaultOptionalOverride)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=1;

	MOD_ASSERT_O(--gl, "--gl", n==2);
	MOD_ASSERT_PO(n, --gl, "--gl", n==2);
	MOD_ASSERT_GO(ModAssert::Error, --gl, "--gl", n==2);
	MOD_ASSERT_PGO(n, ModAssert::Error, --gl, "--gl", n==2);

	MOD_VERIFY_O(--gl, "--gl", n==2);
	MOD_VERIFY_PO(n, --gl, "--gl", n==2);
	MOD_VERIFY_GO(ModAssert::Error, --gl, "--gl", n==2);
	MOD_VERIFY_PGO(n, ModAssert::Error, --gl, "--gl", n==2);

	MOD_CHECK_O(--gl, "--gl", n==2, ++gl);
	MOD_CHECK_PO(n, --gl, "--gl", n==2, ++gl);
	MOD_CHECK_GO(ModAssert::Error, --gl, "--gl", n==2, ++gl);
	MOD_CHECK_PGO(n, ModAssert::Error, --gl, "--gl", n==2, ++gl);

	META_ASSERT(gl==1);
}

MA_TEST(ModAssert_NoPassDefaultOptionalOverride)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=5;

	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "--gl");
	MOD_ASSERT_O(--gl, "--gl", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "--gl");
	MOD_ASSERT_PO(n, --gl, "--gl", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "--gl");
	MOD_ASSERT_GO(ModAssert::Error, --gl, "--gl", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "--gl");
	MOD_ASSERT_PGO(n, ModAssert::Error, --gl, "--gl", gl==0);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(gl, 1));
	else
		META_ASSERT(rbEQUAL(gl, 5));
}

MA_TEST(ModVerifyV_NoPassDefaultOptionalOverride)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=5;
	int c=0;
	Inc inc_c(c);

	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++c");
	MOD_VERIFY_VO(inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++c");
	MOD_VERIFY_VPO((n), inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++c");
	MOD_VERIFY_VGO(ModAssert::Error, inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++c");
	MOD_VERIFY_VPGO((n), ModAssert::Error, inc_c, "++c", gl==0);

	EXPECT_NO_FAILURE;

	META_ASSERT(rbEQUAL(gl, 5));

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(c, 4));
	else
		META_ASSERT(rbEQUAL(c, 0));
}

MA_TEST(ModVerifyB_NoPassDefaultOptionalOverride)
{
	ScopedSetReturnValue s(ModAssert::Optional);
	gl=5;
	int c=0;
	Inc inc_c(c);

	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++c");
	bool rv=MOD_VERIFY_BO(inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++c");
	rv=MOD_VERIFY_BPO((n), inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, NULL, "++c");
	rv=MOD_VERIFY_BGO(ModAssert::Error, inc_c, "++c", gl==0);
	EXPECT_ASSERT(false, "gl==0", NULL, CreateParameterList()("n", n), "++c");
	rv=MOD_VERIFY_BPGO((n), ModAssert::Error, inc_c, "++c", gl==0);

	EXPECT_NO_FAILURE;

	META_ASSERT(rbEQUAL(gl, 5));

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(c, 4));
	else
		META_ASSERT(rbEQUAL(c, 0));
}
