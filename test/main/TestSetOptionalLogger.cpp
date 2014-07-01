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
#include "modassert/filters.hpp"
#include "GetStreamString.h"
#include "StubLogger.h"
#include "richbool/richbool.hpp"

MA_TEST(OptionalLoggerNotUsed)
{
	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::SetOptionalLogger(&logger, "", false);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::SetOptionalLogger(NULL);

	RichBool::detail::String str = "";

	// assertion should not be reported

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerUsedIfAlsoAdded)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::SetOptionalLogger(&logger, "", false);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::Context context(__FILE__, __LINE__-2, MOD_ASSERT_FUNCTION);

	ModAssert::SetOptionalLogger(NULL);
	ModAssert::RemoveLogger(&logger);

	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerNotUsed_ButGetsExtraInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::SetOptionalLogger(&logger, "", true);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::SetOptionalLogger(NULL);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"using the filter no assertions, at begin, at end, in between"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();

	// assertion should not be reported

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerUsedIfAlsoAddedAndUnset1)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);

	// call SetOptionalLogger before AddLogger
	ModAssert::SetOptionalLogger(&logger, "", true);
	size_t id = ModAssert::AddLogger(&logger);

	ModAssert::SetOptionalLogger(NULL);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::Context context(__FILE__, __LINE__-2, MOD_ASSERT_FUNCTION);

	ModAssert::RemoveLogger(id);

	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerUsedIfAlsoAddedAndUnset2)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);

	// call SetOptionalLogger after AddLogger
	size_t id = ModAssert::AddLogger(&logger);
	ModAssert::SetOptionalLogger(&logger, "", true);

	ModAssert::SetOptionalLogger(NULL);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::Context context(__FILE__, __LINE__-2, MOD_ASSERT_FUNCTION);

	ModAssert::RemoveLogger(id);

	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerNotUsedIfRemovedAgain1)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);

	// call SetOptionalLogger before AddLogger
	ModAssert::SetOptionalLogger(&logger, "", true);
	size_t id = ModAssert::AddLogger(&logger);

	ModAssert::RemoveLogger(id);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::SetOptionalLogger(NULL);

	RichBool::detail::String str;

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(OptionalLoggerNotUsedIfRemovedAgain2)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);

	// call SetOptionalLogger after AddLogger
	size_t id = ModAssert::AddLogger(&logger);
	ModAssert::SetOptionalLogger(&logger, "", true);

	ModAssert::RemoveLogger(id);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::SetOptionalLogger(NULL);

	RichBool::detail::String str;

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}
