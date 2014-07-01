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
#include "modassert/assertd.hpp"


MA_TEST(DefaultAssert_Pass)
{
	EXPECT_NO_FAILURE;

	ASSERT(true);
}

MA_TEST(DefaultAssert_NoPass)
{
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	ASSERT(false);
}

MA_TEST(DefaultVerify_Pass)
{
	EXPECT_NO_FAILURE;

	VERIFY(true);
}

MA_TEST(DefaultVerify_NoPass)
{
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	VERIFY(false);
}
