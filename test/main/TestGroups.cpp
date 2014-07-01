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

static ModAssert::Group<ModAssert::ReportFailure> Enabled("enabled");
static ModAssert::Group<ModAssert::ReportNone> Disabled("disabled");

MA_TEST(Group_Pass)
{
	EXPECT_NO_FAILURE;

	MOD_ASSERT_G(Enabled, true);
	MOD_ASSERT_G(Disabled, true);
}

MA_TEST(Group_Enabled_Fail)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL, Enabled, NULL);
	MOD_ASSERT_G(Enabled, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_Disabled_Fail)
{
	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(Disabled, false);
	META_ASSERT(!CheckLoggerCalled());
}

static ModAssert::Group<ModAssert::ReportFailure>
	g1("1"), g2("2"), g3("3"), g4("4");

MA_TEST(GroupList_Of_1_Group)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList(g1);

	META_ASSERT(rbEQUAL(gl.GetSize(), 2u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "Level: Error"));
}

MA_TEST(GroupList_Of_2_Groups)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList(g1 && g2);

	META_ASSERT(rbEQUAL(gl.GetSize(), 3u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "Level: Error"));
}

MA_TEST(GroupList_Of_3_Groups_A)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList(g1 && g2 && g3);

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Error"));
}

MA_TEST(GroupList_Of_3_Groups_B)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList(g1 && (g2 || g3));

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Error"));
}

MA_TEST(GroupList_Of_3_Groups_C)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList((g1 && g2) || g3);

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Error"));
}

MA_TEST(GroupList_Of_2_Groups_Embraced)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList(g1(g2));

	META_ASSERT(rbEQUAL(gl.GetSize(), 3u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "Level: Error"));
}

MA_TEST(GroupList_Of_4_Groups_Embraced)
{
	const ModAssert::GroupList &gl = ModAssert::MakeGroupList((g1&&g2)(g3||g4));

	META_ASSERT(rbEQUAL(gl.GetSize(), 5u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "4"));
	META_ASSERT(rbEQUAL(gl.GetName(4), "Level: Error"));
}

MA_TEST(GroupList_Of_1_Group_And_Level)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList(g1%ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 2u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "Level: Fatal"));
}

MA_TEST(GroupList_Of_2_Groups_And_Level)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList((g1 && g2) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 3u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "Level: Fatal"));
}

MA_TEST(GroupList_Of_3_Groups_And_Level_A)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList((g1 && g2 && g3) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Fatal"));
}

MA_TEST(GroupList_Of_3_Groups_And_Level_B)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList(((g1 && g2) || g3) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Fatal"));
}

MA_TEST(GroupList_Of_3_Groups_And_Level_C)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList(((g1 && g2) || g3) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 4u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "Level: Fatal"));
}

MA_TEST(GroupList_Of_2_Groups_Embraced_With_Level)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList(g1(g2) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 3u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "Level: Fatal"));
}

MA_TEST(GroupList_Of_4_Groups_Embraced_With_Level)
{
	const ModAssert::GroupList &gl =
		ModAssert::MakeGroupList((g1&&g2)(g3||g4) % ModAssert::Fatal);

	META_ASSERT(rbEQUAL(gl.GetSize(), 5u));
	META_ASSERT(rbEQUAL(gl.GetName(0), "1"));
	META_ASSERT(rbEQUAL(gl.GetName(1), "2"));
	META_ASSERT(rbEQUAL(gl.GetName(2), "3"));
	META_ASSERT(rbEQUAL(gl.GetName(3), "4"));
	META_ASSERT(rbEQUAL(gl.GetName(4), "Level: Fatal"));
}




MA_TEST(GroupListHas_Single)
{
	META_ASSERT(!ModAssert::MakeGroupList(ModAssert::Error).Has("enabled"));

	META_ASSERT(ModAssert::MakeGroupList(Enabled).Has("enabled"));
	META_ASSERT(!ModAssert::MakeGroupList(Disabled).Has("enabled"));

	META_ASSERT(!ModAssert::MakeGroupList(Enabled).Has("disabled"));
	META_ASSERT(ModAssert::MakeGroupList(Disabled).Has("disabled"));
}

MA_TEST(GroupListHas_Combinations)
{
	META_ASSERT(ModAssert::MakeGroupList(Enabled && Disabled).Has("enabled"));
	META_ASSERT(ModAssert::MakeGroupList(Enabled && Disabled).Has("disabled"));

	META_ASSERT(ModAssert::MakeGroupList(Enabled || Disabled).Has("enabled"));
	META_ASSERT(ModAssert::MakeGroupList(Enabled || Disabled).Has("disabled"));

	META_ASSERT(ModAssert::MakeGroupList(Enabled % ModAssert::Warning).Has("enabled"));
	META_ASSERT(!ModAssert::MakeGroupList(Enabled % ModAssert::Warning).Has("disabled"));

	META_ASSERT(ModAssert::MakeGroupList((Enabled && Disabled) % ModAssert::Warning).Has("enabled"));
	META_ASSERT(ModAssert::MakeGroupList((Enabled && Disabled) % ModAssert::Warning).Has("disabled"));
}
