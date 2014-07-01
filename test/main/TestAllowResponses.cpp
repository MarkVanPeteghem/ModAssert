//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "ScopedSetReturnValue.h"
#include "richbool/richbool.hpp"
#include "modassert/handler.hpp"


MA_TEST(SetAllowBreakIntoDebugger)
{
	META_ASSERT( ModAssert::GetAllowBreakIntoDebugger());
	ModAssert::SetAllowBreakIntoDebugger(false);
	META_ASSERT(!ModAssert::GetAllowBreakIntoDebugger());
	ModAssert::SetAllowBreakIntoDebugger(true);
	META_ASSERT( ModAssert::GetAllowBreakIntoDebugger());
}

MA_TEST(SetAllowOptional)
{
	META_ASSERT( ModAssert::GetAllowOptional());
	ModAssert::SetAllowOptional(false);
	META_ASSERT(!ModAssert::GetAllowOptional());
	ModAssert::SetAllowOptional(true);
	META_ASSERT( ModAssert::GetAllowOptional());
}

MA_TEST(SetAllowExit)
{
	META_ASSERT( ModAssert::GetAllowExit());
	ModAssert::SetAllowExit(false);
	META_ASSERT(!ModAssert::GetAllowExit());
	ModAssert::SetAllowExit(true);
	META_ASSERT( ModAssert::GetAllowExit());
}

// In these tests, we call ModAssert::HandleAssert directly.
// But the macro EXPECT_FAIL does nothing if assertions aren't reported,
// so we would get an unexpected assertion. Therefore we run these tests
// only if assertions aren't reported.

#if MOD_ASSERT_REPORTS

static ModAssert::Response allResponses =
	ModAssert::Exit & ModAssert::BreakIntoDebugger & ModAssert::Optional &
	ModAssert::StopDisplayingThis & ModAssert::StopDisplayingFile & ModAssert::StopDisplayingAll &
	ModAssert::StopDisplayingCustom1 & ModAssert::StopDisplayingCustom2 &
	ModAssert::StopDisplayingCustom3 & ModAssert::StopDisplayingCustom4 &
	ModAssert::StopDisplayingCustom5 & ModAssert::StopDisplayingCustom6 &
	ModAssert::StopDisplayingCustom7 & ModAssert::StopDisplayingCustom8;

static ModAssert::Context context(__FILE__, 0, 0);
static ModAssert::Category<ModAssert::Assertions> category;
static const ModAssert::GroupList &gl = ModAssert::MakeGroupList(ModAssert::Error);
static ModAssert::Properties properties(&category, context, NULL, gl, NULL);
static ModAssert::Result result(false, NULL, NULL);

MA_TEST(NoneDisallowed)
{
	ScopedSetReturnValue rv(allResponses);

	bool b=true;

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	ModAssert::Response response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL_BITWISE(response, allResponses));
}

MA_TEST(DebugDisallowed)
{
	ScopedSetReturnValue rv(allResponses);

	ModAssert::SetAllowBreakIntoDebugger(false);

	bool b=true;

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	ModAssert::Response response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses&(~ModAssert::BreakIntoDebugger)));

	ModAssert::SetAllowBreakIntoDebugger(true);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses));
}

MA_TEST(ExitDisallowed)
{
	ScopedSetReturnValue rv(allResponses);

	ModAssert::SetAllowExit(false);

	bool b=true;

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	ModAssert::Response response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses&(~ModAssert::Exit)));

	ModAssert::SetAllowExit(true);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses));
}

MA_TEST(OptionalDisallowed)
{
	ScopedSetReturnValue rv(allResponses);

	ModAssert::SetAllowOptional(false);

	bool b=true;

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	ModAssert::Response response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses&(~ModAssert::Exit)));

	ModAssert::SetAllowOptional(true);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	response = ModAssert::HandleAssert(properties, result, &b);

	META_ASSERT(rbEQUAL(response, allResponses));
}

#endif
