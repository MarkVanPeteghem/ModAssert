//  Copyright (C) 2004-2009 Q-Mentum.
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
#include "StubLogger.h"
#include "richbool/richbool.hpp"
#include "GetStreamString.h"
#include "modassert/info.hpp"

static RichBool::MakeString makeString;

MA_TEST(StreamLoggerAssertFalse_NoText)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, NULL, NULL, NULL, NULL);
	MOD_ASSERT(false);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion failed (no text of condition available)"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerFail_NoText)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " unconditional assertion failure"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}
