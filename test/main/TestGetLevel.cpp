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

MA_TEST(Levels)
{
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(ModAssert::Info).GetLevel(), 0));
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(ModAssert::Warning).GetLevel(), 1));
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(ModAssert::Error).GetLevel(), 2));
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(ModAssert::Fatal).GetLevel(), 3));
}

MA_TEST(On_Off)
{
	ModAssert::Group<ModAssert::ReportFailure> on("");
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(on).GetLevel(), 2));

	ModAssert::Group<ModAssert::ReportNone> off("");
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(off).GetLevel(), 2));
}

MA_TEST(IfSuccess)
{
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(ModAssert::IfSuccess).GetLevel(), 2));
}

MA_TEST(Add_Level)
{
	ModAssert::Group<ModAssert::ReportFailure> on("");

	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(on % ModAssert::Info).GetLevel(), 0));

	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(on % ModAssert::Error).GetLevel(), 2));
}

MA_TEST(And_NoLevel)
{
	ModAssert::Group<ModAssert::ReportFailure> on("");
	META_ASSERT(rbEQUAL(ModAssert::MakeGroupList(on && ModAssert::IfSuccess).GetLevel(), 2));
}

MA_TEST(LevelPassedOn)
{
	EXPECT_ASSERT_GL(false, "false", NULL, NULL, ModAssert::Error, 2, NULL);
	MOD_ASSERT(false);

	EXPECT_ASSERT_GL(false, "false", NULL, NULL, ModAssert::Warning, 1, NULL);
	MOD_ASSERT_G(ModAssert::Warning, false);

	EXPECT_ASSERT_GL(false, "false", NULL, NULL, ModAssert::Error, 2, NULL);
	MOD_ASSERT_G(ModAssert::Error, false);

	EXPECT_ASSERT_GL(false, "false", NULL, NULL, ModAssert::Fatal, 3, NULL);
	MOD_ASSERT_G(ModAssert::Fatal, false);

	ModAssert::Group<ModAssert::ReportFailure> on("on");

	EXPECT_ASSERT_GL(false, "false", NULL, NULL, on % ModAssert::Error, 2, NULL);
	MOD_ASSERT_G(on, false);

	ModAssert::MakeGroupList(on % ModAssert::Error);
	EXPECT_ASSERT_GL(false, "false", NULL, NULL, on % ModAssert::Error, 2, NULL);
	MOD_ASSERT_G(on % ModAssert::Error, false);

	ModAssert::MakeGroupList(on % ModAssert::Fatal);
	EXPECT_ASSERT_GL(false, "false", NULL, NULL, on % ModAssert::Fatal, 3, NULL);
	MOD_ASSERT_G(on % ModAssert::Fatal, false);
}
