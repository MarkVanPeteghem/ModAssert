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
#include "modassert/logger.hpp"
#include "modassert/hook.hpp"
#include "modassert/handler.hpp"

static RichBool::detail::String calls;

class TestLogger: public ModAssert::Logger
{
public:
	virtual void OnAssert(const ModAssert::Properties &,
			const ModAssert::Result &) const
	{
		calls += 'l';
	}

	virtual void AddMessage(const RichBool::detail::String &) const
	{}

} testLogger;

class TestHook: public ModAssert::Hook
{
public:
	virtual void OnAssert(const ModAssert::Properties &,
			const ModAssert::Result &) const
	{
		calls += 'h';
	}
} testHook;

MA_TEST(Hook)
{
	ModAssert::AddHook(&testHook);

	calls = "";
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(calls, "h"));
	}

	ModAssert::RemoveHook(&testHook);

	calls = "";
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	META_ASSERT(rbEQUAL(calls, ""));
}

MA_TEST(HookAndLogger)
{
	ModAssert::AddHook(&testHook);
	ModAssert::AddLogger(&testLogger);

	calls = "";
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(calls, "hl"));
	}

	ModAssert::RemoveHook(&testHook);

	calls = "";
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(calls, "l"));
	}

	ModAssert::RemoveLogger(&testLogger);
}
