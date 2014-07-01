//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
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
#include "modassert/verifyv.hpp"


MA_TEST(DefaultAssert_Pass2)
{
	EXPECT_NO_FAILURE;

	IF_MOD_ASSERT_REPORTS(int a=2;)

	ASSERT(a==2);
}

MA_TEST(DefaultAssert_NoPass2)
{
	IF_MOD_ASSERT_REPORTS(int a=2;)

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	ASSERT(a==1);
}

MA_TEST(DefaultVerifyV_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;

	VERIFY(a==2);
}

MA_TEST(DefaultVerifyV_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	VERIFY(a==1);
}

MA_TEST(DefaultVerifyV_ReturnInt_Pass)
{
	EXPECT_NO_FAILURE;

	int a=2;

	int b = VERIFY(a);
	META_ASSERT(rbEQUAL(b,2));
}

MA_TEST(DefaultVerifyV_ReturnInt_NoPass)
{
	int a=0;

	EXPECT_ASSERT(false, "a", NULL, NULL, NULL);
	int b = VERIFY(a);
	META_ASSERT(rbEQUAL(b,0));
}
