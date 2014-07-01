//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "modassert/context.hpp"
#include "richbool/string.hpp"

static int n=0;

class ContextWithInt: public ModAssert::Context
{
public:
	ContextWithInt(const char *file, int line, const char *func, int p):
		ModAssert::Context(file, line, func),
        a_(p)
	{}

	virtual void streamout(RichBool::detail::OutStream &stream) const
	{
		stream << "n=" << a_;
		RichBool::detail::Endl(stream);
		Context::streamout(stream);
	}

	int a_;
};

#undef MOD_ASSERT_CONTEXT
#define MOD_ASSERT_CONTEXT ContextWithInt(__FILE__, __LINE__, \
    MOD_ASSERT_FUNCTION, n)

#include "ModAssertTest.h"
#include "GetStreamString.h"
#include "StubLogger.h"
#include "richbool/richbool.hpp"

RichBool::detail::String ContextString(const char *file, int line, const char *func)
{
	RichBool::detail::String str = file;
	#ifdef _MSC_VER
	str += "("+RichBool::ToString(line)+"): ";
	#else
	str += ":"+RichBool::ToString(line)+": ";
	#endif
	if (func)
	{
    	str += "in ";
    	str += func;
    	str += " ";
	}
	return str;
}

MA_TEST(Context_A)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	n=27;

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	ModAssert::RemoveLogger(&logger);

	RichBool::detail::String str = "n=27"+NewLine();
	str += ContextString(__FILE__, __LINE__-4, MOD_ASSERT_FUNCTION);
	str += "assertion false failed"+NewLine()+"no analysis"+NewLine()+"Level: Error"+NewLine()+NewLine();

	EXPECT_NO_FAILURE;
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbSTRCMP(str.c_str(), ==, GetStreamString(memStream).c_str()));
	else
		META_ASSERT(rbEQUAL("", GetStreamString(memStream)));
}
