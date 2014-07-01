//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


static const int def = 5;
#define MOD_ASSERT_DEFAULT_PARAMETERS def
#define MOD_ASSERT_DEFAULT_PARAMETERS_V (def)

#include "ModAssertTest.h"
#include "CreateList.h"
#include "richbool/richbool.hpp"

MA_TEST(Assert_Pass_1DefaultParam)
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

MA_TEST(Verify_Pass_1DefaultParam)
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

MA_TEST(VerifyV_Pass_1DefaultParam)
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

MA_TEST(Assert_NoPass_1DefaultParam)
{
	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), NULL);
	MOD_ASSERT(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), NULL);
	MOD_ASSERT_P(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1)("def", def), NULL);
	MOD_ASSERT_P(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, NULL);
	MOD_ASSERT_G(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, NULL);
	MOD_ASSERT_PG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), "++a");
	MOD_ASSERT_O(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), "++a");
	MOD_ASSERT_PO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, "++a");
	MOD_ASSERT_GO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, "++a");
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

MA_TEST(Verify_NoPass_1DefaultParam)
{
	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), NULL);
	MOD_VERIFY(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), NULL);
	MOD_VERIFY_P(a, a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1)("def", def), NULL);
	MOD_VERIFY_P(a<<a+1, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, NULL);
	MOD_VERIFY_G(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, NULL);
	MOD_VERIFY_PG(a, ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), "++a");
	MOD_VERIFY_O(++a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), "++a");
	MOD_VERIFY_PO(a, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, "++a");
	MOD_VERIFY_GO(ModAssert::Error, ++a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, "++a");
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

MA_TEST(VerifyV_NoPass_1DefaultParam)
{
	int a=2;
	Inc inc_a(a);

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), NULL);
	MOD_VERIFY_V(a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), NULL);
	MOD_VERIFY_VP((a), a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("a+1", a+1)("def", def), NULL);
	MOD_VERIFY_VP((a,a+1), a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, NULL);
	MOD_VERIFY_VG(ModAssert::Error, a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, NULL);
	MOD_VERIFY_VPG((a), ModAssert::Error, a==1);

	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("def", def), "++a");
	MOD_VERIFY_VO(inc_a, "++a", a==1);
	EXPECT_ASSERT(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), "++a");
	MOD_VERIFY_VPO((a), inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("def", def), ModAssert::Error, "++a");
	MOD_VERIFY_VGO(ModAssert::Error, inc_a, "++a", a==1);
	EXPECT_ASSERT_G(false, "a==1", NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, "++a");
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

MA_TEST(Fail_1DefaultParam)
{
	int a=2;

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("def", def), NULL);
	MOD_FAIL;

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("def", def), NULL);
	MOD_FAIL_P(a);

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("a+1", a+1)("def", def), NULL);
	MOD_FAIL_P(a << a+1);

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("def", def), ModAssert::Error, NULL);
	MOD_FAIL_G(ModAssert::Error);

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, NULL);
	MOD_FAIL_PG(a, ModAssert::Error);

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("def", def), "++a");
	MOD_FAIL_O(++a, "++a");

	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", a)("def", def), "++a");
	MOD_FAIL_PO(a, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("def", def), ModAssert::Error, "++a");
	MOD_FAIL_GO(ModAssert::Error, ++a, "++a");

	EXPECT_FAIL_G(false, NULL, NULL, CreateParameterList()("a", a)("def", def), ModAssert::Error, "++a");
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
