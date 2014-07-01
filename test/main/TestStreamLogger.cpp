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
#include "StubLogger.h"
#include "richbool/richbool.hpp"
#include "GetStreamString.h"
#include "modassert/info.hpp"

static RichBool::MakeString makeString;

MA_TEST(StreamLoggerAssertFalse)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerCheckFalse)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_CHECK_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " check false failed"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerAssertTrue)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess, true);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion true succeeded"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerCheckTrue)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_CHECK(true, "true", NULL, NULL, NULL);
	MOD_CHECK_G(ModAssert::IfSuccess, true, 0);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_CHECK_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " check true succeeded"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithRichBoolean)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	RichBool::SharedAnalysis eq = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		.expr("1", ":")("1", true)(" == ").expr("2", ":")("2", true);
	EXPECT_ASSERT(false, "rbEQUAL(1,2)", eq, NULL, NULL);
	MOD_ASSERT(rbEQUAL(1,2));

	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-4, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion rbEQUAL(1,2) failed"+NewLine()+
			"analysis: `1':<1> == `2':<2> - nok"+NewLine()+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}


MA_TEST(StreamLoggerWithParameters)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	IF_MOD_ASSERT_REPORTS(int a=1; int b=2;)

	EXPECT_ASSERT(false, "false", NULL, CreateParameterList()("a", 1)("b", 2), NULL);
	MOD_ASSERT_P(a << b, false);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+"data:"+NewLine()+
			"  a: 1"+NewLine()+"  b: 2"+NewLine()+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerFail)
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

MA_TEST(StreamLoggerCheckFail)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	EXPECT_CHECK_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_CHECK_FAIL(0);
	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-3, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_CHECK_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " unconditional check failure"+NewLine()+"no analysis"+NewLine()
			+"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}
