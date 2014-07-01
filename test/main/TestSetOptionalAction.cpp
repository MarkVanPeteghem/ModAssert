//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "modassert/handler.hpp"
#include "ScopedSetReturnValue.h"
#include "richbool/richbool.hpp"

static int n=0;
void IncN()
{
	++n;
}

MA_TEST(SetOptionalAction_WithAssert)
{
	ModAssert::SetGlobalOptionalAction(IncN, "IncN");

	ScopedSetReturnValue rv(ModAssert::GlobalOptional);

	n=0;
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(n, 1));
	}


	ModAssert::SetGlobalOptionalAction(NULL, NULL);

	n=0;
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(n, 0));
	}
}

MA_TEST(SetOptionalAction_WithVerifyV)
{
	ModAssert::SetGlobalOptionalAction(IncN, "IncN");

	ScopedSetReturnValue rv(ModAssert::GlobalOptional);

	n=0;
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_VERIFY_V(false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(n, 1));
	}


	ModAssert::SetGlobalOptionalAction(NULL, NULL);

	n=0;
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	EXPECT_NO_FAILURE;

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(n, 0));
	}
}
