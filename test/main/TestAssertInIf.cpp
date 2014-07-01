//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "richbool/richbool.hpp"

MA_TEST(AssertInIfTruePass)
{
	int a=0;
	if (true)
		MOD_ASSERT(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfFalsePass)
{
	int a=0;
	if (false)
		MOD_ASSERT(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfTrueFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (true)
		MOD_ASSERT(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfFalseFail)
{
	int a=0;
	if (false)
		MOD_ASSERT(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfElseTruePass)
{
	int a=0;
	if (true)
		MOD_ASSERT(a==0);
	else
		MOD_ASSERT(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfElseFalsePass)
{
	int a=0;
	if (false)
		MOD_ASSERT(a==1);
	else
		MOD_ASSERT(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfElseTrueFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (true)
		MOD_ASSERT(a==1);
	else
		MOD_ASSERT(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(AssertInIfElseFalseFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (false)
		MOD_ASSERT(a==0);
	else
		MOD_ASSERT(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyV_InIfTruePass)
{
	int a=1;
	int b=0;
	if (true)
		b=MOD_VERIFY_V(a);
	++a;
	META_ASSERT(rbEQUAL(a,2));
	META_ASSERT(rbEQUAL(b,1));
}

MA_TEST(VerifyV_InIfFalsePass)
{
	int a=0,b=1;
	if (false)
		b=MOD_VERIFY_V(a);
	++a;
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,1));
}

MA_TEST(VerifyV_InIfTrueFail)
{
	int a=0, b=1;
	EXPECT_ASSERT(false, "a", NULL, NULL, NULL);
	if (true)
		b=MOD_VERIFY_V(a);
	++a;
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,0));
}

MA_TEST(VerifyV_InIfFalseFail)
{
	int a=0, b=1;
	if (false)
		b=MOD_VERIFY_V(a);
	++a;
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(rbEQUAL(b,1));
}

MA_TEST(VerifyV_InIfElseTruePass)
{
	int a=1, b=0;
	if (true)
		b=MOD_VERIFY_V(a);
	else
		b=MOD_VERIFY_V(a);
	++a;
	META_ASSERT(rbEQUAL(a,2));
	META_ASSERT(rbEQUAL(b,1));
}

MA_TEST(VerifyV_InIfElseFalsePass)
{
	int a=0;
	if (false)
		MOD_VERIFY_V(a==1);
	else
		MOD_VERIFY_V(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyV_InIfElseTrueFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (true)
		MOD_VERIFY_V(a==1);
	else
		MOD_VERIFY_V(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyV_InIfElseFalseFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (false)
		MOD_VERIFY_V(a==0);
	else
		MOD_VERIFY_V(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfTruePass)
{
	int a=0;
	bool rv=false;
	if (true)
		rv=MOD_VERIFY_B(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfFalsePass)
{
	int a=0;
	bool rv=false;
	if (false)
		rv=MOD_VERIFY_B(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfTrueFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	bool rv=false;
	if (true)
		rv=MOD_VERIFY_B(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfFalseFail)
{
	int a=0;
	bool rv=false;
	if (false)
		rv=MOD_VERIFY_B(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfElseTruePass)
{
	int a=0;
	bool rv=false;
	if (true)
		rv=MOD_VERIFY_B(a==0);
	else
		rv=MOD_VERIFY_B(a==1);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfElseFalsePass)
{
	int a=0;
	bool rv=false;
	if (false)
		rv=MOD_VERIFY_B(a==1);
	else
		rv=MOD_VERIFY_B(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfElseTrueFail)
{
	int a=0;
	bool rv=false;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	if (true)
		rv=MOD_VERIFY_B(a==1);
	else
		rv=MOD_VERIFY_B(a==0);
	++a;
	META_ASSERT(a==1);
}

MA_TEST(VerifyB_InIfElseFalseFail)
{
	int a=0;
	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	bool rv=false;
	if (false)
		rv=MOD_VERIFY_B(a==0);
	else
		rv=MOD_VERIFY_B(a==1);
	++a;
	META_ASSERT(a==1);
}
