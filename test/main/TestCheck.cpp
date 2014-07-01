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

MA_TEST(CheckPass)
{
	int a=2;

	MOD_CHECK(a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_P(a, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_G(ModAssert::Error, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_PG(a, ModAssert::Error, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_O(++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_PO(a, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_GO(ModAssert::Error, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_PGO(a, ModAssert::Error, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);


	MOD_CHECK_NP(a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_SP(a, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_NPG(ModAssert::Error, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_SPG(a, ModAssert::Error, a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_NPO(++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_SPO(a, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_NPGO(ModAssert::Error, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);

	MOD_CHECK_SPGO(a, ModAssert::Error, ++a, "++a", a==2, ++a);
	META_ASSERT(a==2);
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

MA_TEST(CheckV_Pass)
{
	int a=2, rv=0;
	Inc inc_a(a);

	rv=MOD_CHECK_V(a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VP((a), a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VG(ModAssert::Error, a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VPG((a), ModAssert::Error, a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VO(inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VPO((a), inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VGO(ModAssert::Error, inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VPGO((a), ModAssert::Error, inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));


	rv=MOD_CHECK_VNP(a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VSP((a), a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VNPG(ModAssert::Error, a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VSPG((a), ModAssert::Error, a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VNPO(inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VSPO((a), inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VNPGO(ModAssert::Error, inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));

	rv=MOD_CHECK_VSPGO((a), ModAssert::Error, inc_a, "++a", a, inc_a);
	META_ASSERT(a==2);
	META_ASSERT(rbEQUAL(rv,2));
}

MA_TEST(CheckB_Pass)
{
	int a=2;
	bool rv=false;
	Inc inc_a(a);

	rv=MOD_CHECK_B(a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BP((a), a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BG(ModAssert::Error, a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BPG((a), ModAssert::Error, a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BO(inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BPO((a), inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BGO(ModAssert::Error, inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BPGO((a), ModAssert::Error, inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);


	rv=MOD_CHECK_BNP(a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BSP((a), a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BNPG(ModAssert::Error, a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BSPG((a), ModAssert::Error, a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BNPO(inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BSPO((a), inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BNPGO(ModAssert::Error, inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);

	rv=MOD_CHECK_BSPGO((a), ModAssert::Error, inc_a, "++a", a);
	META_ASSERT(a==2);
	META_ASSERT(rv);
}

MA_TEST(CheckB_Pass_Ignored)
{
	// if ModAssert doesn't report, EXPECT_ASSERT expands to an empty statement
	// so we can't check if it is really reported.
	// This can be solved by defining a variation of EXPECT_ASSERT.
	if (MOD_ASSERT_REPORTS)
	{
		EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", true), NULL);
		ModAssert::UseBool::SetCheck(true);
		MOD_CHECK_B(true);
	}
}

ModAssert::UseBool ReturnUseBool(bool b)
{
	return MOD_CHECK_B(b);
}

MA_TEST(CheckB_InCall_Pass_NotIgnored)
{
	ModAssert::UseBool::SetCheck(true);
	if (!ReturnUseBool(true))
	{
	}
}

MA_TEST(CheckB_InCall_Pass_Ignored)
{
	// if ModAssert doesn't report, EXPECT_ASSERT expands to an empty statement
	// so we can't check if it is really reported.
	// This can be solved by defining a variation of EXPECT_ASSERT.
	if (MOD_ASSERT_REPORTS)
	{
		EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", true), NULL);
		ModAssert::UseBool::SetCheck(true);
		ReturnUseBool(true);
	}
}

MA_TEST(CheckNoPass)
{
	int a=2;

	EXPECT_CHECK(false, "a==1", NULL, NULL, NULL);
	MOD_CHECK(a==1, ++a);
	META_ASSERT(a==3);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_CHECK_P(a, a==1, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_CHECK_G(ModAssert::Error, a==1, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_CHECK_PG(a, ModAssert::Error, a==1, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK(false, "a==1", NULL, NULL, "--a");
	MOD_CHECK_O(--a, "--a", a==1, ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a), "--a");
	MOD_CHECK_PO(a, --a, "--a", a==1, ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_G(false, "a==1", NULL, NULL, ModAssert::Error, "--a");
	MOD_CHECK_GO(ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	MOD_CHECK_PGO(a, ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckVNoPass)
{
	int a=0, n=0, rv;

	Inc inc_n(n);

	EXPECT_CHECK(false, "a", NULL, NULL, NULL);
	rv=MOD_CHECK_V(a, inc_n);
	META_ASSERT(n==1);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK(false, "a", NULL, CreateParameterList()("a", a), NULL);
	rv=MOD_CHECK_VP((a), a, inc_n);
	META_ASSERT(n==2);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK_G(false, "a", NULL, NULL, ModAssert::Error, NULL);
	rv=MOD_CHECK_VG(ModAssert::Error, a, inc_n);
	META_ASSERT(n==3);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK_G(false, "a", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	rv=MOD_CHECK_VPG((a), ModAssert::Error, a, inc_n);
	META_ASSERT(n==4);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK(false, "a", NULL, NULL, "--a");
	rv=MOD_CHECK_VO(inc_n, "--a", a, inc_n);
	META_ASSERT(n==5);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK(false, "a", NULL, CreateParameterList()("a", a), "--a");
	rv=MOD_CHECK_VPO((a), inc_n, "--a", a, inc_n);
	META_ASSERT(n==6);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK_G(false, "a", NULL, NULL, ModAssert::Error, "--a");
	rv=MOD_CHECK_VGO(ModAssert::Error, inc_n, "--a", a, inc_n);
	META_ASSERT(n==7);
	META_ASSERT(rbEQUAL(rv,0));

	EXPECT_CHECK_G(false, "a", NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	rv=MOD_CHECK_VPGO((a), ModAssert::Error, inc_n, "--a", a, inc_n);
	META_ASSERT(n==8);
	META_ASSERT(rbEQUAL(rv,0));
}

MA_TEST(CheckBNoPass)
{
	int a=0, n=0;
	bool rv=false;

	Inc inc_n(n);

	EXPECT_CHECK(false, "a", NULL, NULL, NULL);
	rv=MOD_CHECK_B(a);
	META_ASSERT(!rv);

	EXPECT_CHECK(false, "a", NULL, CreateParameterList()("a", a), NULL);
	rv=MOD_CHECK_BP((a), a);
	META_ASSERT(!rv);

	EXPECT_CHECK_G(false, "a", NULL, NULL, ModAssert::Error, NULL);
	rv=MOD_CHECK_BG(ModAssert::Error, a);
	META_ASSERT(!rv);

	EXPECT_CHECK_G(false, "a", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	rv=MOD_CHECK_BPG((a), ModAssert::Error, a);
	META_ASSERT(!rv);

	EXPECT_CHECK(false, "a", NULL, NULL, "--a");
	rv=MOD_CHECK_BO(inc_n, "--a", a);
	META_ASSERT(n==0);
	META_ASSERT(!rv);

	EXPECT_CHECK(false, "a", NULL, CreateParameterList()("a", a), "--a");
	rv=MOD_CHECK_BPO((a), inc_n, "--a", a);
	META_ASSERT(n==0);
	META_ASSERT(!rv);

	EXPECT_CHECK_G(false, "a", NULL, NULL, ModAssert::Error, "--a");
	rv=MOD_CHECK_BGO(ModAssert::Error, inc_n, "--a", a);
	META_ASSERT(n==0);
	META_ASSERT(!rv);

	EXPECT_CHECK_G(false, "a", NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	rv=MOD_CHECK_BPGO((a), ModAssert::Error, inc_n, "--a", a);
	META_ASSERT(n==0);
	META_ASSERT(!rv);
}

MA_TEST(CheckNoPass2)
{
	int a=2;

	EXPECT_CHECK(false, "a==1", NULL, NULL, NULL);
	MOD_CHECK_NP(a==1, ++a);
	META_ASSERT(a==3);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a), NULL);
	MOD_CHECK_SP(a, a==1, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_G(false, "a==1", NULL, NULL, ModAssert::Error, NULL);
	MOD_CHECK_NPG(ModAssert::Error, a==1, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_CHECK_SPG(a, ModAssert::Error, a==1, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK(false, "a==1", NULL, NULL, "--a");
	MOD_CHECK_NPO(--a, "--a", a==1, ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a), "--a");
	MOD_CHECK_SPO(a, --a, "--a", a==1, ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_G(false, "a==1", NULL, NULL, ModAssert::Error, "--a");
	MOD_CHECK_NPGO(ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	MOD_CHECK_SPGO(a, ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckFail)
{
	int a=2;

	EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_CHECK_FAIL(++a);
	META_ASSERT(a==3);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a), NULL);
	MOD_CHECK_FAIL_P(a, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, NULL);
	MOD_CHECK_FAIL_G(ModAssert::Error, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_CHECK_FAIL_PG(a, ModAssert::Error, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, "--a");
	MOD_CHECK_FAIL_O(--a, "--a", ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a), "--a");
	MOD_CHECK_FAIL_PO(a, --a, "--a", ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "--a");
	MOD_CHECK_FAIL_GO(ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	MOD_CHECK_FAIL_PGO(a, ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckFail2)
{
	int a=2;

	EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_CHECK_FAIL_NP(++a);
	META_ASSERT(a==3);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a), NULL);
	MOD_CHECK_FAIL_SP(a, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, NULL);
	MOD_CHECK_FAIL_NPG(ModAssert::Error, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, NULL);
	MOD_CHECK_FAIL_SPG(a, ModAssert::Error, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, "--a");
	MOD_CHECK_FAIL_NPO(--a, "--a", ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a), "--a");
	MOD_CHECK_FAIL_SPO(a, --a, "--a", ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, NULL, ModAssert::Error, "--a");
	MOD_CHECK_FAIL_NPGO(ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a), ModAssert::Error, "--a");
	MOD_CHECK_FAIL_SPGO(a, ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckBreak)
{
	int a=2;

	int i=0;
	for ( ; i<3; ++i)
	{
		EXPECT_CHECK(false, "a==1", NULL, NULL, NULL);
		MOD_CHECK(a==1, break);
		META_ASSERT(false); // shouldn't be reached
	}
	META_ASSERT(rbEQUAL(i,0));

	EXPECT_NO_FAILURE;
}

MA_TEST(CheckContinue)
{
	int a=2;

	int i=0;
	for ( ; i<3; ++i)
	{
		EXPECT_CHECK(false, "a==1", NULL, NULL, NULL);
		MOD_CHECK(a==1, continue);
		META_ASSERT(false); // shouldn't be reached
	}
	META_ASSERT(rbEQUAL(i,3));

	EXPECT_NO_FAILURE;
}

MA_TEST(CheckFailBreak)
{
	int i=0;
	for ( ; i<3; ++i)
	{
		EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, NULL);
		MOD_CHECK_FAIL(break);
		META_ASSERT(false); // shouldn't be reached
	}
	META_ASSERT(rbEQUAL(i,0));

	EXPECT_NO_FAILURE;
}

MA_TEST(CheckFailContinue)
{
	int i=0;
	for ( ; i<3; ++i)
	{
		EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, NULL);
		MOD_CHECK_FAIL(continue);
		META_ASSERT(false); // shouldn't be reached
	}
	META_ASSERT(rbEQUAL(i,3));

	EXPECT_NO_FAILURE;
}

MA_TEST(CheckV_Nested_PassBoth)
{
	EXPECT_NO_FAILURE;

	int a=2;

	int n=0;
	Inc inc_n(n);

	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_n)+1, inc_n);
	META_ASSERT(rbEQUAL(b,3));
	META_ASSERT(rbEQUAL(n,0));
}

MA_TEST(CheckV_Nested_FailFirst)
{
	int a=0;

	int m=0, n=0;
	Inc inc_m(m), inc_n(n);

	EXPECT_CHECK(false, "a", NULL, NULL, NULL);
	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_m)+1, inc_n);
	META_ASSERT(rbEQUAL(b,1));
    META_ASSERT(rbEQUAL(m,1));
    META_ASSERT(rbEQUAL(n,0));
}


MA_TEST(CheckV_Nested_FailSecond)
{
	int a=-1;

	int m=0, n=0;
	Inc inc_m(m), inc_n(n);

	EXPECT_CHECK(false, "MOD_CHECK_V(a, inc_m)+1", NULL, NULL, NULL);
	int b = MOD_CHECK_V(MOD_CHECK_V(a, inc_m)+1, inc_n);
	META_ASSERT(rbEQUAL(b,0));
    META_ASSERT(rbEQUAL(m,0));
    META_ASSERT(rbEQUAL(n,1));
}

MA_TEST(CheckB_Nested_PassBoth)
{
	EXPECT_NO_FAILURE;

	int a=2;

	bool b = MOD_CHECK_B((bool)MOD_CHECK_B(a));
	META_ASSERT(b);
}

MA_TEST(CheckB_Nested_FailFirst)
{
	int a=0;

	EXPECT_CHECK(false, "a", NULL, NULL, NULL);
	bool b = MOD_CHECK_B(!MOD_CHECK_B(a));
	META_ASSERT(b);
}


MA_TEST(CheckB_Nested_FailSecond)
{
	int a=1;

	EXPECT_CHECK(false, "!MOD_CHECK_B(a)", NULL, NULL, NULL);
	bool b = MOD_CHECK_B(!MOD_CHECK_B(a));
	META_ASSERT(!b);
}

MA_TEST(Check_BadValue)
{
	if (MOD_CHECK_REPORTS)
	{
		int a=2, *p=0;

		RichBool::SharedAnalysis eq = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
			.expr("*p", ":")(RichBool::PtrToString(0), false)(" == ").expr("1", ":")("1", true);

		EXPECT_ASSERT_GL(false, "rbEQUAL(*p,1)", eq, NULL, ModAssert::Fatal, 3, NULL);

		MOD_CHECK(rbEQUAL(*p,1), ++a);
		META_ASSERT(a==3);
	}
}
