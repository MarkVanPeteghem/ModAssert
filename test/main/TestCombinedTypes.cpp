//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_LEVEL 1

#include "ModAssertTest.h"
#include "richbool/richbool.hpp"
#include "modassert/category.hpp"
#include "modassert/categories.hpp"
#include "ScopedSetReturnValue.h"

using namespace ModAssert;

Group<ReportFailure> G1("group 1"), G2("group 2"), G3("group 3"),
	G4("group 4"), G5("group 5"), G6("group 6"), G7("group 7"), G8("group 8");

#define EIGHT_GROUPS (G1 && G2 && G3 && G4 && G5 && G6 && G7 && G8)

Group<ReportNone> GOff("group off");

int countNrIgnored()
{
	return
		(!G1.GetDisplay(false) ? 1 : 0) +
		(!G2.GetDisplay(false) ? 1 : 0) +
		(!G3.GetDisplay(false) ? 1 : 0) +
		(!G4.GetDisplay(false) ? 1 : 0) +
		(!G5.GetDisplay(false) ? 1 : 0) +
		(!G6.GetDisplay(false) ? 1 : 0) +
		(!G7.GetDisplay(false) ? 1 : 0) +
		(!G8.GetDisplay(false) ? 1 : 0);
}

int countNrNotLogged()
{
	return
		(!G1.GetLog(false) ? 1 : 0) +
		(!G2.GetLog(false) ? 1 : 0) +
		(!G3.GetLog(false) ? 1 : 0) +
		(!G4.GetLog(false) ? 1 : 0) +
		(!G5.GetLog(false) ? 1 : 0) +
		(!G6.GetLog(false) ? 1 : 0) +
		(!G7.GetLog(false) ? 1 : 0) +
		(!G8.GetLog(false) ? 1 : 0);
}

MA_TEST(Combined2_GetSize)
{
	META_ASSERT(rbEQUAL((G1 && G2).GetSize(), 2u));
}

MA_TEST(GroupListOf_Combined2_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(G1 && G2).GetSize(), 3u));
}

MA_TEST(Combined2_Or_GetSize)
{
	META_ASSERT(rbEQUAL((G1 || G2).GetSize(), 2u));
}

MA_TEST(GroupListOf_Combined2_Or_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(G1 || G2).GetSize(), 3u));
}

MA_TEST(Combined2_Embraced_GetSize)
{
	META_ASSERT(rbEQUAL((G1(G2)).GetSize(), 2u));
}

MA_TEST(GroupListOf_Combined2_Embraced_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(G1(G2)).GetSize(), 3u));
}

MA_TEST(Combined3_And_GetSize)
{
	META_ASSERT(rbEQUAL((G1 && G2 && G3).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined3_And_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(G1 && G2 && G3).GetSize(), 4u));
}

MA_TEST(Combined3_And_Or_A_GetSize)
{
	META_ASSERT(rbEQUAL((G1 && (G2 || G3)).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined3_And_Or_A_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(G1 && (G2 || G3)).GetSize(), 4u));
}

MA_TEST(Combined3_And_Or_B_GetSize)
{
	META_ASSERT(rbEQUAL(((G1 && G2) || G3).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined3_And_Or_B_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList((G1 && G2) || G3).GetSize(), 4u));
}

MA_TEST(Combined2_WithLevel_GetSize)
{
	META_ASSERT(rbEQUAL(((G1 && G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined2_WithLevel_GetSize)
{
	// GroupList adds none, because there is already a level
	META_ASSERT(rbEQUAL(MakeGroupList((G1 && G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(Combined2_Or_WithLevel_GetSize)
{
	META_ASSERT(rbEQUAL(((G1 || G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined2_Or_WithLevel_GetSize)
{
	// GroupList adds none, because there is already a level
	META_ASSERT(rbEQUAL(MakeGroupList((G1 || G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(Combined2_Embraced_WithLevel_GetSize)
{
	META_ASSERT(rbEQUAL((G1(G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(GroupListOf_Combined2_Embraced_WithLevel_GetSize)
{
	// GroupList adds none, because there is already a level
	META_ASSERT(rbEQUAL(MakeGroupList(G1(G2) % ModAssert::Fatal).GetSize(), 3u));
}

MA_TEST(Combined8_GetSize)
{
	META_ASSERT(rbEQUAL((EIGHT_GROUPS).GetSize(), 8u));
}

MA_TEST(GroupListOf_Combined8_GetSize)
{
	// GroupList adds one: the default level
	META_ASSERT(rbEQUAL(MakeGroupList(EIGHT_GROUPS).GetSize(), 9u));
}

static Category<Assertions> assertions;

MA_TEST(Combined2_SetDisplay)
{
	(G1 && G2).SetDisplay(0, false);
	META_ASSERT(!G1.GetDisplay(false));
	META_ASSERT( G2.GetDisplay(false));
	META_ASSERT(rbEQUAL(countNrIgnored(), 1));

	G1.SetDisplay(true);

	(G1 && G2).SetDisplay(1, false);
	META_ASSERT( G1.GetDisplay(false));
	META_ASSERT(!G2.GetDisplay(false));
	META_ASSERT(rbEQUAL(countNrIgnored(), 1));

	G2.SetDisplay(true);
}

MA_TEST(Combined8_SetDisplay)
{
	(EIGHT_GROUPS).SetDisplay(0, false);
	META_ASSERT(!G1.GetDisplay(false));
	META_ASSERT( G2.GetDisplay(false));
	META_ASSERT(rbEQUAL(countNrIgnored(), 1));

	G1.SetDisplay(true);

	(EIGHT_GROUPS).SetDisplay(1, false);
	META_ASSERT( G1.GetDisplay(false));
	META_ASSERT(!G2.GetDisplay(false));
	META_ASSERT(rbEQUAL(countNrIgnored(), 1));

	G2.SetDisplay(true);

	(EIGHT_GROUPS).SetDisplay(7, false);
	META_ASSERT( G1.GetDisplay(false));
	META_ASSERT(!G8.GetDisplay(false));
	META_ASSERT(rbEQUAL(countNrIgnored(), 1));

	G8.SetDisplay(true);
}

MA_TEST(Combined2_SetLog)
{
	(G1 && G2).SetLog(0, false);
	META_ASSERT(!G1.GetLog(false));
	META_ASSERT( G2.GetLog(false));
	META_ASSERT(rbEQUAL(countNrNotLogged(), 1));

	G1.SetLog(true);

	(G1 && G2).SetLog(1, false);
	META_ASSERT( G1.GetLog(false));
	META_ASSERT(!G2.GetLog(false));
	META_ASSERT(rbEQUAL(countNrNotLogged(), 1));

	G2.SetLog(true);
}

MA_TEST(Combined8_SetLog)
{
	(EIGHT_GROUPS).SetLog(0, false);
	META_ASSERT(!G1.GetLog(false));
	META_ASSERT( G2.GetLog(false));
	META_ASSERT(rbEQUAL(countNrNotLogged(), 1));

	G1.SetLog(true);

	(EIGHT_GROUPS).SetLog(1, false);
	META_ASSERT( G1.GetLog(false));
	META_ASSERT(!G2.GetLog(false));
	META_ASSERT(rbEQUAL(countNrNotLogged(), 1));

	G2.SetLog(true);

	(EIGHT_GROUPS).SetLog(7, false);
	META_ASSERT( G1.GetLog(false));
	META_ASSERT(!G8.GetLog(false));
	META_ASSERT(rbEQUAL(countNrNotLogged(), 1));

	G8.SetLog(true);
}

typedef detail::GroupsAnd<GroupHolder<ReportFailure>, GroupHolder<ReportFailure> > Combine2;
static Combine2 combine2(G1.type, G2.type);

typedef detail::GroupsAnd<CombinationHolder<Combine2>, GroupHolder<ReportFailure> > Combine3;
static Combine3 combine3(combine2, G3.type);

typedef detail::GroupsAnd<CombinationHolder<Combine3>, GroupHolder<ReportFailure> > Combine4;
static Combine4 combine4(combine3, G4.type);

typedef detail::GroupsAnd<CombinationHolder<Combine4>, GroupHolder<ReportFailure> > Combine5;
static Combine5 combine5(combine4, G5.type);

typedef detail::GroupsAnd<CombinationHolder<Combine5>, GroupHolder<ReportFailure> > Combine6;
static Combine6 combine6(combine5, G6.type);

typedef detail::GroupsAnd<CombinationHolder<Combine6>, GroupHolder<ReportFailure> > Combine7;
static Combine7 combine7(combine6, G7.type);

typedef detail::GroupsAnd<CombinationHolder<Combine7>, GroupHolder<ReportFailure> > Combine8;
static Combine8 combine8(combine7, G8.type);

MA_TEST(Group_And_Group_Fail)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 && G2, NULL);
	MOD_ASSERT_G(G1 && G2, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_And_Group_And_Group_Fail)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 && G2 && G3, NULL);
	MOD_ASSERT_G(G1 && G2 && G3, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_Or_Group_Or_Group_Fail)
{
	// necessary in VC 6.0 to avoid compile error:
	(G1 || G2 || G3).ifSuccess;

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 || G2 || G3, NULL);

	MOD_ASSERT_G(G1 || G2 || G3, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_Or_Group_And_GroupA_Fail)
{
	// necessary in VC 6.0 to avoid compile error:
	((G1 || G2) && G3).ifSuccess;

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		(G1 || G2) && G3, NULL);

	MOD_ASSERT_G((G1 || G2) && G3, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_Or_Group_And_GroupB_Fail)
{
	// necessary in VC 6.0 to avoid compile error:
	(G1 || (G2 && G3)).ifSuccess;

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 || (G2 && G3), NULL);

	MOD_ASSERT_G(G1 || (G2 && G3), false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_And_Group_Fail_OneIsOff)
{
	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(G1 && GOff, false);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_Or_Group_Fail_OneIsOff)
{
	// necessary in VC 6.0 to avoid compile error:
	(G1 || GOff).ifSuccess;

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 || GOff, NULL);

	MOD_ASSERT_G(G1 || GOff, false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Group_With_Level_Fail)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 % Error, NULL);
	MOD_ASSERT_G(G1 % Error, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(GroupOn_Or_GroupOff_DontDisplay)
{
	G1.SetDisplay(false);

	EXPECT_NO_FAILURE;

	MOD_ASSERT_G(G1 || GOff, false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
	}

	G1.SetDisplay(true);
}

MA_TEST(GroupOn_Or_GroupOff_DontLog)
{
	G1.SetLog(false);

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		G1 || GOff, NULL);

	MOD_ASSERT_G(G1 || GOff, false);
	META_ASSERT(!CheckLoggerCalled());

	G1.SetLog(true);
}

MA_TEST(Group_And_Level_Fail_LevelIsOff)
{
	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(G1%Info, false);
	META_ASSERT(!CheckLoggerCalled());
}

typedef GroupWithLevel<Combine8, detail::L_<2> > Combine8WithError;
Group<Combine8> gCombine8(combine8);
static Combine8WithError combine8WithError(combine8);

MA_TEST(Group_And8_Fail)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		combine8WithError, NULL);
	MOD_ASSERT_G(EIGHT_GROUPS, false);

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

template<class Type>
void TestGroup_And8_Fail_Ignore(Response response,
								Type &type)
{
	ScopedSetReturnValue rv(response);

	EXPECT_ASSERT_G(false, "false", NULL, NULL,
		combine8WithError, NULL);
	MOD_ASSERT_G(EIGHT_GROUPS, false);

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(!type.GetDisplay(false));
		META_ASSERT(rbEQUAL(1, countNrIgnored()));
		META_ASSERT(CheckLoggerCalled());
	}
	else
	{
		META_ASSERT(type.GetDisplay(false));
		META_ASSERT(!CheckLoggerCalled());
	}

	// try a second time:
	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(EIGHT_GROUPS, false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(!type.GetDisplay(false));
		META_ASSERT(CheckLoggerCalled());
	}
	else
	{
		META_ASSERT(type.GetDisplay(false));
		META_ASSERT(!CheckLoggerCalled());
	}

	type.SetDisplay(true);
}

MA_TEST(Group_And8_Fail_Ignore)
{
	TestGroup_And8_Fail_Ignore(StopDisplayingCustom1, G1);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom2, G2);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom3, G3);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom4, G4);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom5, G5);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom6, G6);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom7, G7);

	TestGroup_And8_Fail_Ignore(StopDisplayingCustom8, G8);
}
