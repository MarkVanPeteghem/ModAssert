//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#define MOD_ASSERT_NO_TEXT

#include "ModAssertTest.h"
#include "CreateList.h"

MA_TEST(Assert_NoText_Pass)
{
	EXPECT_NO_FAILURE;
	MOD_ASSERT(true);
}

MA_TEST(Assert_NoText_NoPass)
{
	EXPECT_ASSERT(false, NULL, NULL, NULL, NULL);
	MOD_ASSERT(false);
}

MA_TEST(Verify_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_VERIFY(a==1);
}

MA_TEST(Verify_NoText_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, NULL, NULL, NULL, NULL);
	MOD_VERIFY(a==1);
}

MA_TEST(Check_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_CHECK(a==1, ++a);
}

MA_TEST(Check_NoText_NoPass)
{
	int a=2;

	EXPECT_CHECK(false, NULL, NULL, NULL, NULL);
	MOD_CHECK(a==1, ++a);
}

MA_TEST(VerifyV_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_VERIFY_V(a==1);
}

MA_TEST(VerifyV_NoText_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, NULL, NULL, NULL, NULL);
	MOD_VERIFY_V(a==1);
}

MA_TEST(VerifyB_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	bool rv=MOD_VERIFY_B(a==1);
	rv = !rv; // to avoid warning
}

MA_TEST(VerifyB_NoText_NoPass)
{
	int a=2;

	EXPECT_ASSERT(false, NULL, NULL, NULL, NULL);
	bool rv=MOD_VERIFY_B(a==1);
	rv = !rv; // to avoid warning
}

MA_TEST(CheckV_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_CHECK_V(a==1, ModAssert::Nop);
}

MA_TEST(CheckV_NoText_NoPass)
{
	int a=2;

	EXPECT_CHECK(false, NULL, NULL, NULL, NULL);
	MOD_CHECK_V(a==1, ModAssert::Nop);
}

MA_TEST(CheckB_NoText_Pass)
{
	int a=1;

	EXPECT_NO_FAILURE;
	bool b=MOD_CHECK_B(a==1);
	b = false;
}

MA_TEST(CheckB_NoText_NoPass)
{
	int a=2;

	EXPECT_CHECK(false, NULL, NULL, NULL, NULL);
	bool b=MOD_CHECK_B(a==1);
	b = false;
}
