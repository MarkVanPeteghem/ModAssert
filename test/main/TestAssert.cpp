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
#include "richbool/richbool.hpp"


MA_TEST(Assert_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;

	MOD_ASSERT(a==2);
	MOD_ASSERT_P(a, a==2);
	MOD_ASSERT_P(a << a, a==2);
	MOD_ASSERT_G(ModAssert::Error, a==2);
	MOD_ASSERT_PG(a, ModAssert::Error, a==2);
	MOD_ASSERT_O(++a, "++a", a==2);
	MOD_ASSERT_PO(a, ++a, "++a", a==2);
	MOD_ASSERT_GO(ModAssert::Error, ++a, "++a", a==2);
	MOD_ASSERT_PGO(a, ModAssert::Error, ++a, "++a", a==2);

	MOD_ASSERT_NP(a==2);
	MOD_ASSERT_SP(a, a==2);
	MOD_ASSERT_SP(a << a, a==2);
	MOD_ASSERT_NPG(ModAssert::Error, a==2);
	MOD_ASSERT_SPG(a, ModAssert::Error, a==2);
	MOD_ASSERT_NPO(++a, "++a", a==2);
	MOD_ASSERT_SPO(a, ++a, "++a", a==2);
	MOD_ASSERT_NPGO(ModAssert::Error, ++a, "++a", a==2);
	MOD_ASSERT_SPGO(a, ModAssert::Error, ++a, "++a", a==2);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed
}

MA_TEST(Verify_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;

	MOD_VERIFY(a==2);
	MOD_VERIFY_P(a, a==2);
	MOD_VERIFY_P(a << a, a==2);
	MOD_VERIFY_G(ModAssert::Error, a==2);
	MOD_VERIFY_PG(a, ModAssert::Error, a==2);
	MOD_VERIFY_O(++a, "++a", a==2);
	MOD_VERIFY_PO(a, ++a, "++a", a==2);
	MOD_VERIFY_GO(ModAssert::Error, ++a, "++a", a==2);
	MOD_VERIFY_PGO(a, ModAssert::Error, ++a, "++a", a==2);

	MOD_VERIFY_NP(a==2);
	MOD_VERIFY_SP(a, a==2);
	MOD_VERIFY_SP(a << a, a==2);
	MOD_VERIFY_NPG(ModAssert::Error, a==2);
	MOD_VERIFY_SPG(a, ModAssert::Error, a==2);
	MOD_VERIFY_NPO(++a, "++a", a==2);
	MOD_VERIFY_SPO(a, ++a, "++a", a==2);
	MOD_VERIFY_NPGO(ModAssert::Error, ++a, "++a", a==2);
	MOD_VERIFY_SPGO(a, ModAssert::Error, ++a, "++a", a==2);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed
}

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

MA_TEST(VerifyV_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;
	Inc inc_a(a);

	MOD_VERIFY_V(a==2);
	MOD_VERIFY_VP((a), a==2);
	MOD_VERIFY_VP((a,a), a==2);
	MOD_VERIFY_VG(ModAssert::Error, a==2);
	MOD_VERIFY_VPG((a), ModAssert::Error, a==2);
	MOD_VERIFY_VO(inc_a, "++a", a==2);
	MOD_VERIFY_VPO((a), inc_a, "++a", a==2);
	MOD_VERIFY_VGO(ModAssert::Error, inc_a, "++a", a==2);
	MOD_VERIFY_VPGO((a), ModAssert::Error, inc_a, "++a", a==2);

	MOD_VERIFY_VNP(a==2);
	MOD_VERIFY_VSP((a), a==2);
	MOD_VERIFY_VSP((a,a), a==2);
	MOD_VERIFY_VNPG(ModAssert::Error, a==2);
	MOD_VERIFY_VSPG((a), ModAssert::Error, a==2);
	MOD_VERIFY_VNPO(inc_a, "++a", a==2);
	MOD_VERIFY_VSPO((a), inc_a, "++a", a==2);
	MOD_VERIFY_VNPGO(ModAssert::Error, inc_a, "++a", a==2);
	MOD_VERIFY_VSPGO((a), ModAssert::Error, inc_a, "++a", a==2);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed
}

MA_TEST(VerifyB_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;
	Inc inc_a(a);

	META_ASSERT((bool)MOD_VERIFY_B(a==2));
	META_ASSERT((bool)MOD_VERIFY_BP((a), a==2));
	META_ASSERT((bool)MOD_VERIFY_BP((a,a), a==2));
	META_ASSERT((bool)MOD_VERIFY_BG(ModAssert::Error, a==2));
	META_ASSERT((bool)MOD_VERIFY_BPG((a), ModAssert::Error, a==2));
	META_ASSERT((bool)MOD_VERIFY_BO(inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BPO((a), inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BGO(ModAssert::Error, inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BPGO((a), ModAssert::Error, inc_a, "++a", a==2));

	META_ASSERT((bool)MOD_VERIFY_BNP(a==2));
	META_ASSERT((bool)MOD_VERIFY_BSP((a), a==2));
	META_ASSERT((bool)MOD_VERIFY_BSP((a,a), a==2));
	META_ASSERT((bool)MOD_VERIFY_BNPG(ModAssert::Error, a==2));
	META_ASSERT((bool)MOD_VERIFY_BSPG((a), ModAssert::Error, a==2));
	META_ASSERT((bool)MOD_VERIFY_BNPO(inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BSPO((a), inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BNPGO(ModAssert::Error, inc_a, "++a", a==2));
	META_ASSERT((bool)MOD_VERIFY_BSPGO((a), ModAssert::Error, inc_a, "++a", a==2));

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed
}

MA_TEST(Assert_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_ASSERT(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_ASSERT_P(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_ASSERT_P(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_ASSERT_G(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_ASSERT_PG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_ASSERT_O(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_ASSERT_PO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_ASSERT_GO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_ASSERT_PGO(a, ModAssert::Error, ++a, "++a", a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_ASSERT_NP(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_ASSERT_SP(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_ASSERT_SP(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_ASSERT_NPG(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_ASSERT_SPG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_ASSERT_NPO(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_ASSERT_SPO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_ASSERT_NPGO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_ASSERT_SPGO(a, ModAssert::Error, ++a, "++a", a==1);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed

	EXPECT_NO_FAILURE;
}

MA_TEST(Verify_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_VERIFY(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_VERIFY_P(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_VERIFY_P(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_VERIFY_G(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_VERIFY_PG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_VERIFY_O(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_VERIFY_PO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_VERIFY_GO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_VERIFY_PGO(a, ModAssert::Error, ++a, "++a", a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_VERIFY_NP(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_VERIFY_SP(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_VERIFY_SP(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_VERIFY_NPG(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_VERIFY_SPG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_VERIFY_NPO(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_VERIFY_SPO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_VERIFY_NPGO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_VERIFY_SPGO(a, ModAssert::Error, ++a, "++a", a==1);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyV_NoPass)
{
	int a=2;
	Inc inc_a(a);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_VERIFY_V(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_VERIFY_VP((a), a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_VERIFY_VP((a,a+1), a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_VERIFY_VG(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_VERIFY_VPG((a), ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_VERIFY_VO(inc_a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_VERIFY_VPO((a), inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_VERIFY_VGO(ModAssert::Error, inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_VERIFY_VPGO((a), ModAssert::Error, inc_a, "++a", a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_VERIFY_VNP(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_VERIFY_VSP((a), a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_VERIFY_VSP((a,a+1), a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_VERIFY_VNPG(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_VERIFY_VSPG((a), ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	MOD_VERIFY_VNPO(inc_a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	MOD_VERIFY_VSPO((a), inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	MOD_VERIFY_VNPGO(ModAssert::Error, inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_VERIFY_VSPGO((a), ModAssert::Error, inc_a, "++a", a==1);

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyB_NoPass)
{
	int a=2;
	Inc inc_a(a);

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	META_ASSERT(!MOD_VERIFY_B(a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	META_ASSERT(!MOD_VERIFY_BP((a), a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	META_ASSERT(!MOD_VERIFY_BP((a,a+1), a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	META_ASSERT(!MOD_VERIFY_BG(ModAssert::Error, a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	META_ASSERT(!MOD_VERIFY_BPG((a), ModAssert::Error, a==1));

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	META_ASSERT(!MOD_VERIFY_BO(inc_a, "++a", a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	META_ASSERT(!MOD_VERIFY_BPO((a), inc_a, "++a", a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	META_ASSERT(!MOD_VERIFY_BGO(ModAssert::Error, inc_a, "++a", a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	META_ASSERT(!MOD_VERIFY_BPGO((a), ModAssert::Error, inc_a, "++a", a==1));

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	META_ASSERT(!MOD_VERIFY_BNP(a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	META_ASSERT(!MOD_VERIFY_BSP((a), a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	META_ASSERT(!MOD_VERIFY_BSP((a,a+1), a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	META_ASSERT(!MOD_VERIFY_BNPG(ModAssert::Error, a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	META_ASSERT(!MOD_VERIFY_BSPG((a), ModAssert::Error, a==1));

	EXPECT_ASSERT(false, "a==1", NULL, NULL, "++a");
	META_ASSERT(!MOD_VERIFY_BNPO(inc_a, "++a", a==1));
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a), "++a");
	META_ASSERT(!MOD_VERIFY_BSPO((a), inc_a, "++a", a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, NULL, ModAssert::Error, "++a");
	META_ASSERT(!MOD_VERIFY_BNPGO(ModAssert::Error, inc_a, "++a", a==1));
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	META_ASSERT(!MOD_VERIFY_BSPGO((a), ModAssert::Error, inc_a, "++a", a==1));

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed

	EXPECT_NO_FAILURE;
}

MA_TEST(Fail)
{
	int a=2;

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a), NULL);
	MOD_FAIL_P(a);

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_FAIL_P(a << a+1);

	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, NULL);
	MOD_FAIL_G(ModAssert::Error);

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_FAIL_PG(a, ModAssert::Error);

	EXPECT_FAIL(false, NULL, NULL, NULL, "++a");
	MOD_FAIL_O(++a, "++a");

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a), "++a");
	MOD_FAIL_PO(a, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "++a");
	MOD_FAIL_GO(ModAssert::Error, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_FAIL_PGO(a, ModAssert::Error, ++a, "++a");


	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL_NP;

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a), NULL);
	MOD_FAIL_SP(a);

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("a+1", a+1), NULL);
	MOD_FAIL_SP(a << a+1);

	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, NULL);
	MOD_FAIL_NPG(ModAssert::Error);

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_FAIL_SPG(a, ModAssert::Error);

	EXPECT_FAIL(false, NULL, NULL, NULL, "++a");
	MOD_FAIL_NPO(++a, "++a");

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a), "++a");
	MOD_FAIL_SPO(a, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "++a");
	MOD_FAIL_NPGO(ModAssert::Error, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, "++a");
	MOD_FAIL_SPGO(a, ModAssert::Error, ++a, "++a");

	META_ASSERT(rbEQUAL(a,2)); // check that the optional action was not executed

	EXPECT_NO_FAILURE;
}

MA_TEST(VerifyV_Nested_PassBoth)
{
	EXPECT_NO_FAILURE;

	int a=2;

	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,3));
}

MA_TEST(VerifyV_Nested_FailFirst)
{
	int a=0;

	EXPECT_ASSERT(false, "a", NULL, NULL, NULL);
	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,1));
}


MA_TEST(VerifyV_Nested_FailSecond)
{
	int a=-1;

	EXPECT_ASSERT(false, "MOD_VERIFY_V(a)+1", NULL, NULL, NULL);
	int b = MOD_VERIFY_V(MOD_VERIFY_V(a)+1);
	META_ASSERT(rbEQUAL(b,0));
}

MA_TEST(VerifyB_Nested_PassBoth)
{
	EXPECT_NO_FAILURE;

	int a=2;

	bool b = MOD_VERIFY_B(MOD_VERIFY_B(a==2));
	META_ASSERT(b);
}

MA_TEST(VerifyB_Nested_FailFirst)
{
	int a=0;

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	bool b = MOD_VERIFY_B(!MOD_VERIFY_B(a==1));
	META_ASSERT(b);
}


MA_TEST(VerifyB_Nested_FailSecond)
{
	int a=1;

	EXPECT_ASSERT(false, "!MOD_VERIFY_B(a==1)", NULL, NULL, NULL);
	bool b = MOD_VERIFY_B(!MOD_VERIFY_B(a==1));
	META_ASSERT(!b);
}

MA_TEST(Assert_BadValue)
{
#if MOD_ASSERT_REPORTS
	// Here we test whether a Rich Boolean that detects a bad value,
	// gives a fatal level instead of an error level.

	int *p=0;

	RichBool::SharedAnalysis eq = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("*p", ":")(RichBool::PtrToString(0), false)(" == ").expr("1", ":")("1", true);

	EXPECT_ASSERT_GL(false, "rbEQUAL(*p,1)", eq, NULL, ModAssert::Fatal, 3, NULL);

	MOD_ASSERT(rbEQUAL(*p,1));
#endif
}
