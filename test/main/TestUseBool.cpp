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


MA_TEST(UseBool_True_DirectUse)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	ModAssert::UseBool ub(true, MOD_ASSERT_CONTEXT);
	bool b = ub;

	META_ASSERT(b);
}

MA_TEST(UseBool_False_DirectUse)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	ModAssert::UseBool ub(false, MOD_ASSERT_CONTEXT);
	bool b = ub;

	META_ASSERT(!b);
}

MA_TEST(UseBool_True_Direct_NotUsed)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", true), NULL);
	ModAssert::UseBool ub(true, MOD_ASSERT_CONTEXT);
}

MA_TEST(UseBool_False_Direct_NotUsed)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", false), NULL);
	ModAssert::UseBool ub(false, MOD_ASSERT_CONTEXT);
}

MA_TEST(UseBool_True_IndirectUse)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	ModAssert::UseBool ub1(true, MOD_ASSERT_CONTEXT);
	ModAssert::UseBool ub2(ub1);
	bool b = ub2;

	META_ASSERT(b);
}

MA_TEST(UseBool_False_IndirectUse)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	ModAssert::UseBool ub1(false, MOD_ASSERT_CONTEXT);
	ModAssert::UseBool ub2(ub1);
	bool b = ub2;

	META_ASSERT(!b);
}

MA_TEST(UseBool_True_Inirect_NotUsed)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", true), NULL);
	ModAssert::UseBool ub1(true, MOD_ASSERT_CONTEXT);
	ModAssert::UseBool ub2(ub1);
}

MA_TEST(UseBool_False_Indirect_NotUsed)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	EXPECT_ASSERT(false, "unused UseBool", NULL, CreateParameterList()("condition", false), NULL);
	ModAssert::UseBool ub1(false, MOD_ASSERT_CONTEXT);
	ModAssert::UseBool ub2(ub1);
}

MA_TEST(UseBool_Copy_AndUse)
{
	IF_MOD_ASSERT_REPORTS(ModAssert::UseBool::SetCheck(true);)

	ModAssert::UseBool ub1(false, MOD_ASSERT_CONTEXT);
	ModAssert::UseBool ub2(ub1);
	bool b = ub2;
	META_ASSERT(!b);
}
