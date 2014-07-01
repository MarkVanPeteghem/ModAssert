//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


static const int def1 = 5, def2 = 6;
#define MOD_ASSERT_DEFAULT_PARAMETERS def1 << def2
#define MOD_ASSERT_DEFAULT_PARAMETERS_V (def1, def2)

#include "ModAssertTest.h"
#include "CreateList.h"
#include "richbool/richbool.hpp"

MA_TEST(CheckPass_2DefaultParams)
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

MA_TEST(CheckV_Pass_2DefaultParam)
{
	int a=2;

	Inc inc_a(a);

	MOD_CHECK_V(a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VP((a), a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VG(ModAssert::Error, a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VPG((a), ModAssert::Error, a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VO(inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VPO((a), inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VGO(ModAssert::Error, inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VPGO((a), ModAssert::Error, inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);


	MOD_CHECK_VNP(a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VSP((a), a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VNPG(ModAssert::Error, a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VSPG((a), ModAssert::Error, a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VNPO(inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VSPO((a), inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VNPGO(ModAssert::Error, inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);

	MOD_CHECK_VSPGO((a), ModAssert::Error, inc_a, "++a", a==2, inc_a);
	META_ASSERT(a==2);
}

MA_TEST(CheckB_Pass_2DefaultParam)
{
	int a=2;

	Inc inc_a(a);

	bool b=false;

	b=MOD_CHECK_B(a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BP((a), a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BG(ModAssert::Error, a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BPG((a), ModAssert::Error, a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BO(inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BPO((a), inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BGO(ModAssert::Error, inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BPGO((a), ModAssert::Error, inc_a, "++a", a==2);
	META_ASSERT(a==2);


	b=MOD_CHECK_BNP(a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BSP((a), a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BNPG(ModAssert::Error, a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BSPG((a), ModAssert::Error, a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BNPO(inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BSPO((a), inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BNPGO(ModAssert::Error, inc_a, "++a", a==2);
	META_ASSERT(a==2);

	b=MOD_CHECK_BSPGO((a), ModAssert::Error, inc_a, "++a", a==2);
	META_ASSERT(a==2);
}

MA_TEST(CheckNoPass_2DefaultParams)
{
	int a=2;

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), NULL);
	MOD_CHECK(a==1, ++a);
	META_ASSERT(a==3);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), NULL);
	MOD_CHECK_P(a, a==1, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_G(ModAssert::Error, a==1, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_PG(a, ModAssert::Error, a==1, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), "--a");
	MOD_CHECK_O(--a, "--a", a==1, ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), "--a");
	MOD_CHECK_PO(a, --a, "--a", a==1, ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, "--a");
	MOD_CHECK_GO(ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), ModAssert::Error, "--a");
	MOD_CHECK_PGO(a, ModAssert::Error, --a, "--a", a==1, ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckV_NoPass_2DefaultParam)
{
	int a=2;
	IF_MOD_CHECK_REPORTS(int n=0;)

	Inc inc_a(a);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), NULL);
	MOD_CHECK_V(a==1, inc_a);
	META_ASSERT(a==3);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), NULL);
	MOD_CHECK_VP((n), a==1, inc_a);
	META_ASSERT(a==4);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_VG(ModAssert::Error, a==1, inc_a);
	META_ASSERT(a==5);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_VPG((n), ModAssert::Error, a==1, inc_a);
	META_ASSERT(a==6);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), "++a");
	MOD_CHECK_VO(inc_a, "++a", a==1, inc_a);
	META_ASSERT(a==7);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), "++a");
	MOD_CHECK_VPO((n), inc_a, "++a", a==1, inc_a);
	META_ASSERT(a==8);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, "++a");
	MOD_CHECK_VGO(ModAssert::Error, inc_a, "++a", a==1, inc_a);
	META_ASSERT(a==9);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), ModAssert::Error, "++a");
	MOD_CHECK_VPGO((n), ModAssert::Error, inc_a, "++a", a==1, inc_a);
	META_ASSERT(a==10);
}

MA_TEST(CheckB_NoPass_2DefaultParam)
{
	int a=2;
	IF_MOD_CHECK_REPORTS(int n=0;)

	Inc inc_a(a);

	bool b=false;

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), NULL);
	b=MOD_CHECK_B(a==1);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), NULL);
	b=MOD_CHECK_BP((n), a==1);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, NULL);
	b=MOD_CHECK_BG(ModAssert::Error, a==1);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), ModAssert::Error, NULL);
	b=MOD_CHECK_BPG((n), ModAssert::Error, a==1);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), "++a");
	b=MOD_CHECK_BO(inc_a, "++a", a==1);
	META_ASSERT(a==2);

	EXPECT_CHECK(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), "++a");
	b=MOD_CHECK_BPO((n), inc_a, "++a", a==1);
	META_ASSERT(a==2);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, "++a");
	b=MOD_CHECK_BGO(ModAssert::Error, inc_a, "++a", a==1);
	META_ASSERT(a==2);

	EXPECT_CHECK_G(false, "a==1", NULL, CreateParameterList()("n", n)("def1", def1)("def2", def2), ModAssert::Error, "++a");
	b=MOD_CHECK_BPGO((n), ModAssert::Error, inc_a, "++a", a==1);
	META_ASSERT(a==2);
}

MA_TEST(CheckNoPass2_2DefaultParams)
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

MA_TEST(CheckFail_2DefaultParams)
{
	int a=2;

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("def1", def1)("def2", def2), NULL);
	MOD_CHECK_FAIL(++a);
	META_ASSERT(a==3);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), NULL);
	MOD_CHECK_FAIL_P(a, ++a);
	META_ASSERT(a==4);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_FAIL_G(ModAssert::Error, ++a);
	META_ASSERT(a==5);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), ModAssert::Error, NULL);
	MOD_CHECK_FAIL_PG(a, ModAssert::Error, ++a);
	META_ASSERT(a==6);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("def1", def1)("def2", def2), "--a");
	MOD_CHECK_FAIL_O(--a, "--a", ++a);
	META_ASSERT(a==7);

	EXPECT_CHECK_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), "--a");
	MOD_CHECK_FAIL_PO(a, --a, "--a", ++a);
	META_ASSERT(a==8);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("def1", def1)("def2", def2), ModAssert::Error, "--a");
	MOD_CHECK_FAIL_GO(ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==9);

	EXPECT_CHECK_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a)("def1", def1)("def2", def2), ModAssert::Error, "--a");
	MOD_CHECK_FAIL_PGO(a, ModAssert::Error, --a, "--a", ++a);
	META_ASSERT(a==10);
}

MA_TEST(CheckFail2_2DefaultParams)
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
