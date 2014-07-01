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

MA_TEST(RemoveById1)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	size_t idAssert = ModAssert::AddLogger(&logger, &ModAssert::filterIfAssertion);
	size_t idCheck  = ModAssert::AddLogger(&logger, &ModAssert::filterIfCheck);

	META_ASSERT( ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT( ModAssert::IsLoggerUsed(idCheck));

	ModAssert::RemoveLogger(idAssert);

	META_ASSERT(!ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT( ModAssert::IsLoggerUsed(idCheck));

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(idCheck);

	META_ASSERT(!ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT(!ModAssert::IsLoggerUsed(idCheck));

	RichBool::detail::String str = "";

	// assertion should not be reported

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(RemoveById2)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	size_t idAssert = ModAssert::AddLogger(&logger, &ModAssert::filterIfAssertion);
	size_t idCheck  = ModAssert::AddLogger(&logger, &ModAssert::filterIfCheck);

	META_ASSERT( ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT( ModAssert::IsLoggerUsed(idCheck));

	ModAssert::RemoveLogger(idCheck);

	META_ASSERT( ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT(!ModAssert::IsLoggerUsed(idCheck));

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(idAssert);

	META_ASSERT(!ModAssert::IsLoggerUsed(idAssert));
	META_ASSERT(!ModAssert::IsLoggerUsed(idCheck));

	ModAssert::Context context(__FILE__, __LINE__-7, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}
