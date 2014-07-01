//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "modassert/assert.hpp"
#include "richbool/richbool.hpp"

#if MOD_ASSERT_REPORTS
	#define ONE_OR_ZERO 1
#else
	#define ONE_OR_ZERO 0
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

MA_TEST(SideEffectsOfAssert)
{
	int a=0;
	MOD_ASSERT(++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_P(a, ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_P(a<<a, ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_P(++a, ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_P(++a << ++a, ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_O(a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_PO(a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_PO(a<<a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_PO(++a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));

	a=0;
	MOD_ASSERT_PO(++a << ++a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,ONE_OR_ZERO));
}

MA_TEST(SideEffectsOfVerify)
{
	int a=0;
	MOD_VERIFY(++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_P(a, ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_P(a<<a, ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_P(--a, ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_P(--a<<--a, ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_O(a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_PO(a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_PO(a<<a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_PO(--a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_PO(--a<<--a, a=10, "a=10", ++a==1);
	META_ASSERT(rbEQUAL(a,1));
}

MA_TEST(SideEffectsOfVerifyV)
{
	int a=0, b=0;
	MOD_VERIFY_V(++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_VP((a), ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_VERIFY_VP((a,a), ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	// difference with MOD_VERIFY_P: expressions (i.e. first argument) are evaluated!!
	MOD_VERIFY_VP((++b), ++a==1);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,ONE_OR_ZERO));

	a=0;
	b=0;
	MOD_VERIFY_VP((++b,++b), ++a==1);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,2*ONE_OR_ZERO));

	DoubleInt da(a);

	a=2;
	MOD_VERIFY_VO(da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	MOD_VERIFY_VPO((a), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	MOD_VERIFY_VPO((a,a), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	b=0;
	MOD_VERIFY_VPO((++b), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));
	META_ASSERT(rbEQUAL(b,ONE_OR_ZERO));

	a=2;
	b=0;
	MOD_VERIFY_VPO((++b,++b), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));
	META_ASSERT(rbEQUAL(b,2*ONE_OR_ZERO));
}

MA_TEST(SideEffectsOfVerifyB)
{
	int a=0, b=0;
	bool rv=MOD_VERIFY_B(++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	rv=MOD_VERIFY_BP((a), ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	rv=MOD_VERIFY_BP((a,a), ++a==1);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	// difference with MOD_VERIFY_P: expressions (i.e. first argument) are evaluated!!
	rv=MOD_VERIFY_BP((++b), ++a==1);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,ONE_OR_ZERO));

	a=0;
	b=0;
	rv=MOD_VERIFY_BP((++b,++b), ++a==1);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,2*ONE_OR_ZERO));

	DoubleInt da(a);

	a=2;
	rv=MOD_VERIFY_BO(da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	rv=MOD_VERIFY_BPO((a), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	rv=MOD_VERIFY_BPO((a,a), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));

	a=2;
	b=0;
	rv=MOD_VERIFY_BPO((++b), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));
	META_ASSERT(rbEQUAL(b,ONE_OR_ZERO));

	a=2;
	b=0;
	rv=MOD_VERIFY_BPO((++b,++b), da, "da", ++a==3);
	META_ASSERT(rbEQUAL(a,3));
	META_ASSERT(rbEQUAL(b,2*ONE_OR_ZERO));
}

MA_TEST(SideEffectsOfCheck)
{
	int a=0;
	MOD_CHECK(++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_P(a, ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_P(a<<a, ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_P(--a, ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_P(--a<<--a, ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_O(a=10, "a=10", ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_PO(a, a=10, "a=10", ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_PO(a<<a, a=10, "a=10", ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_PO(--a, a=10, "a=10", ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));

	a=0;
	MOD_CHECK_PO(--a<<--a, a=10, "a=10", ++a==1, a=10);
	META_ASSERT(rbEQUAL(a,1));
}
