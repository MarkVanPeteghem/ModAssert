//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "CreateList.h"
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

// we copy the type, because for some it has to const, for other it has
// to be non-const, so we can't use a reference
template<class TheType>
void TestIfAssertDisabled(TheType IF_MOD_ASSERT_REPORTS(type))
{
	int a=1;

	EXPECT_NO_FAILURE;

	MOD_ASSERT_G(type, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_PG(a, type, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_GO(type, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	MOD_ASSERT_PGO(a, type, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));


	// the condition should still be evaluated,
	// so a should increase

	MOD_VERIFY_G(type, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));

	MOD_VERIFY_PG(a, type, ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	MOD_VERIFY_GO(type, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 4));

	MOD_VERIFY_PGO(a, type, ++a, "++a", ++a==0);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	Inc inc_a(a);

	int rv = 0;
	a=0;
	rv = MOD_VERIFY_VG(type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VPG((a), type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VGO(type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VPGO((a), type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VNPG(type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VSPG((a), type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VNPGO(type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VSPGO((a), type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv = MOD_VERIFY_VG(type, rbvMORE(a++,1));
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));
}

// we copy the type, because for some it has to const, for other it has
// to be non-const, so we can't use a reference
template<class TheType>
void TestIfCheckDisabled(TheType IF_MOD_CHECK_REPORTS(type))
{
	int a=1;

	// the condition should still be evaluated,
	// so a should increase
	// the condition always fails, so it's increased twice

	MOD_CHECK_G(type, ++a==0, ++a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	MOD_CHECK_PG(a, type, ++a==0, ++a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	MOD_CHECK_GO(type, ++a, "++a", ++a==0, ++a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 7));

	MOD_CHECK_PGO(a, type, ++a, "++a", ++a==0, ++a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 9));

	Inc inc_a(a);

	int rv=0;
	a=0;
	rv=MOD_CHECK_VG(type, a++, inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv=MOD_CHECK_VPG((a), type, a++, inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv=MOD_CHECK_VGO(type, inc_a, "++a", a++, inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv=MOD_CHECK_VPGO((a), type, inc_a, "++a", a++, inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	rv=MOD_CHECK_VG(type, rbvMORE(a++, 1), inc_a);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	bool b;
	a=0;
	b=MOD_CHECK_BG(type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	a=0;
	b=MOD_CHECK_BPG((a), type, a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	a=0;
	b=MOD_CHECK_BGO(type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	a=0;
	b=MOD_CHECK_BPGO((a), type, inc_a, "++a", a++);
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));

	a=0;
	b=MOD_CHECK_BG(type, rbvMORE(a++, 0));
	META_ASSERT(!CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
}

// we copy the type, because for some it has to const, for other it has
// to be non-const, so we can't use a reference
template<class TheType>
void TestIfAssertEnabled(TheType IF_MOD_ASSERT_REPORTS(type))
{
	int a=1;

	EXPECT_ASSERT_G(false, "++a==0", NULL, NULL, type, NULL);
	MOD_ASSERT_G(type, ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));

	EXPECT_ASSERT_G(false, "++a==0", NULL, CreateParameterList()("a", 3), type, NULL);
	MOD_ASSERT_PG(a, type, ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	EXPECT_ASSERT_G(false, "++a==0", NULL, NULL, type, "++a");
	MOD_ASSERT_GO(type, ++a, "++a", ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 4));

	EXPECT_ASSERT_G(false, "++a==0", NULL, CreateParameterList()("a", 5), type, "++a");
	MOD_ASSERT_PGO(a, type, ++a, "++a", ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	a=1;

	// the condition should still be evaluated,
	// so a should increase

	EXPECT_ASSERT_G(false, "++a==0", NULL, NULL, type, NULL);
	MOD_VERIFY_G(type, ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));

	EXPECT_ASSERT_G(false, "++a==0", NULL, CreateParameterList()("a", 3), type, NULL);
	MOD_VERIFY_PG(a, type, ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	EXPECT_ASSERT_G(false, "++a==0", NULL, NULL, type, "++a");
	MOD_VERIFY_GO(type, ++a, "++a", ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 4));

	EXPECT_ASSERT_G(false, "++a==0", NULL, CreateParameterList()("a", 5), type, "++a");
	MOD_VERIFY_PGO(a, type, ++a, "++a", ++a==0);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	// in the macros that return a value, the order of evaluation
	// of the condition and the expressions is undefined,
	// so we use a different variable
	IF_MOD_ASSERT_REPORTS(int n=27;)

	Inc inc_a(a);

	int rv;
	a=0;
	EXPECT_ASSERT_G(false, "a++", NULL, NULL, type, NULL);
	rv=MOD_VERIFY_VG(type, a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	EXPECT_ASSERT_G(false, "a++", NULL, CreateParameterList()("n", n), type, NULL);
	rv=MOD_VERIFY_VPG((n), type, a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	EXPECT_ASSERT_G(false, "a++", NULL, NULL, type, "++a");
	rv=MOD_VERIFY_VGO(type, inc_a, "++a", a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	EXPECT_ASSERT_G(false, "a++", NULL, CreateParameterList()("n", n), type, "++a");
	rv=MOD_VERIFY_VPGO((n), type, inc_a, "++a", a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));

	RichBool::SharedAnalysis analysis = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		.expr("a++", ":")("0", true)(" > ").expr("1", ":")("1", true);

	a=0;
	EXPECT_ASSERT_G(false, "rbvMORE(a++,1)", analysis, NULL, type, NULL);
	rv=MOD_VERIFY_VG(type, rbvMORE(a++,1));
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(rbEQUAL(rv, 0));
}

// we copy the type, because for some it has to const, for other it has
// to be non-const, so we can't use a reference
template<class TheType>
void TestIfCheckEnabled(TheType IF_MOD_CHECK_REPORTS(type))
{
	int a=1;

	// the condition should be evaluated,
	// so a should increase
	// the condition always fails, so it's increased twice

	EXPECT_CHECK_G(false, "++a==0", NULL, NULL, type, NULL);
	MOD_CHECK_G(type, ++a==0, ++a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 3));

	EXPECT_CHECK_G(false, "++a==0", NULL, CreateParameterList()("a", 4), type, NULL);
	MOD_CHECK_PG(a, type, ++a==0, ++a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 5));

	EXPECT_CHECK_G(false, "++a==0", NULL, NULL, type, "++a");
	MOD_CHECK_GO(type, ++a, "++a", ++a==0, ++a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 7));

	EXPECT_CHECK_G(false, "++a==0", NULL, CreateParameterList()("a", 8), type, "++a");
	MOD_CHECK_PGO(a, type, ++a, "++a", ++a==0, ++a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 9));


	Inc inc_a(a);

	int rv;
	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, NULL, type, NULL);
	rv=MOD_CHECK_VG(type, a++, inc_a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));

	// in the macros that return a value, the order of evaluation
	// of the condition and the expressions is undefined,
	// so we use a different variable
	IF_MOD_CHECK_REPORTS(int n=27;)

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, CreateParameterList()("n", n), type, NULL);
	rv=MOD_CHECK_VPG((n), type, a++, inc_a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, NULL, type, "++a");
	rv=MOD_CHECK_VGO(type, inc_a, "++a", a++, inc_a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(rv, 0));

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, CreateParameterList()("n", n), type, "++a");
	rv=MOD_CHECK_VPGO((n), type, inc_a, "++a", a++, inc_a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(rv, 0));

	RichBool::SharedAnalysis analysis = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		.expr("a++", ":")("0", true)(" > ").expr("1", ":")("1", true);

	a=0;
	EXPECT_CHECK_G(false, "rbvMORE(a++, 1)", analysis, NULL, type, NULL);
	rv=MOD_CHECK_VG(type, rbvMORE(a++, 1), inc_a);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 2));
	META_ASSERT(rbEQUAL(rv, 0));


	bool b;
	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, NULL, type, NULL);
	b=MOD_CHECK_BG(type, a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(!b);

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, CreateParameterList()("n", n), type, NULL);
	b=MOD_CHECK_BPG((n), type, a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(!b);

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, NULL, type, "++a");
	b=MOD_CHECK_BGO(type, inc_a, "++a", a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(!b);

	a=0;
	EXPECT_CHECK_G(false, "a++", NULL, CreateParameterList()("n", n), type, "++a");
	b=MOD_CHECK_BPGO((n), type, inc_a, "++a", a++);
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(!b);

	a=0;
	EXPECT_CHECK_G(false, "rbvMORE(a++, 1)", analysis, NULL, type, NULL);
	b=MOD_CHECK_BG(type, rbvMORE(a++, 1));
	META_ASSERT(CheckLoggerCalled());
	META_ASSERT(rbEQUAL(a, 1));
	META_ASSERT(!b);
}
