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
#include "richbool/string.hpp"
#include "modassert/handler.hpp"
#include "modassert/logger.hpp"
#include "modassert/result.hpp"

static RichBool::MakeString makeString;

class TestLoggerData: public ModAssert::Logger
{
public:
	TestLoggerData();

	virtual void OnAssert(const ModAssert::Properties &properties,
		const ModAssert::Result &assertionResult) const;

	virtual void AddMessage(const RichBool::detail::String &) const
	{}

	mutable const char *m_file, *m_condition;
	mutable int m_line;
	mutable RichBool::SharedAnalysis m_analysis;
};

TestLoggerData::TestLoggerData(): m_file(""), m_condition(""), m_line(0), m_analysis(0)
{}

void TestLoggerData::OnAssert(const ModAssert::Properties &properties,
		const ModAssert::Result &assertionResult) const
{
	m_file = properties.GetContext().file_;
	m_line = properties.GetContext().line_;
	m_condition = properties.GetCondition();
	m_analysis = assertionResult.GetAnalysis();
}

static TestLoggerData testLogger1, testLogger2;

static RichBool::SharedAnalysis eq = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
	.expr("1", ":")("1", true)(" == ").expr("2", ":")("2", true);


MA_TEST(Logger)
{
	ModAssert::AddLogger(&testLogger1);
	ModAssert::AddLogger(&testLogger2);

	// next assertion should fail, the others not because they check the testLoggers
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	EXPECT_NO_FAILURE;
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(__LINE__-5, testLogger1.m_line));
		META_ASSERT(rbEQUAL(__LINE__-6, testLogger2.m_line));
		META_ASSERT(rbSTRCMP(__FILE__, ==, testLogger1.m_file));
		META_ASSERT(rbSTRCMP(__FILE__, ==, testLogger2.m_file));
		META_ASSERT(rbSTRCMP("false", ==, testLogger1.m_condition));
		META_ASSERT(rbSTRCMP("false", ==, testLogger2.m_condition));
		META_ASSERT(!testLogger1.m_analysis);
		META_ASSERT(!testLogger2.m_analysis);
	}
	else
	{
		META_ASSERT(rbEQUAL(0, testLogger1.m_line));
		META_ASSERT(rbEQUAL(0, testLogger2.m_line));
		META_ASSERT(rbSTRCMP("", ==, testLogger1.m_file));
		META_ASSERT(rbSTRCMP("", ==, testLogger2.m_file));
		META_ASSERT(rbSTRCMP("", ==, testLogger1.m_condition));
		META_ASSERT(rbSTRCMP("", ==, testLogger2.m_condition));
		META_ASSERT(!testLogger1.m_analysis);
		META_ASSERT(!testLogger2.m_analysis);
	}

	// next assertion should fail, the others not because they check the testLoggers
	EXPECT_ASSERT(false, "rbEQUAL(1,2)", eq, NULL, NULL);
	MOD_ASSERT(rbEQUAL(1,2));

	EXPECT_NO_FAILURE;
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(rbEQUAL(__LINE__-5, testLogger1.m_line));
		META_ASSERT(rbEQUAL(__LINE__-6, testLogger2.m_line));
		META_ASSERT(rbSTRCMP(__FILE__, ==, testLogger1.m_file));
		META_ASSERT(rbSTRCMP(__FILE__, ==, testLogger2.m_file));
		META_ASSERT(rbSTRCMP("rbEQUAL(1,2)", ==, testLogger1.m_condition));
		META_ASSERT(rbSTRCMP("rbEQUAL(1,2)", ==, testLogger2.m_condition));
		META_ASSERT(!!testLogger1.m_analysis);
		META_ASSERT(!!testLogger2.m_analysis);
		if (testLogger1.m_analysis)
			META_ASSERT(*testLogger1.m_analysis==*eq);
		if (testLogger2.m_analysis)
			META_ASSERT(*testLogger2.m_analysis==*eq);
	}
	else
	{
		META_ASSERT(rbEQUAL(0, testLogger1.m_line));
		META_ASSERT(rbEQUAL(0, testLogger2.m_line));
		META_ASSERT(rbSTRCMP("", ==, testLogger1.m_file));
		META_ASSERT(rbSTRCMP("", ==, testLogger2.m_file));
		META_ASSERT(rbSTRCMP("", ==, testLogger1.m_condition));
		META_ASSERT(rbSTRCMP("", ==, testLogger2.m_condition));
		META_ASSERT(!testLogger1.m_analysis);
		META_ASSERT(!testLogger2.m_analysis);
	}

	ModAssert::RemoveLogger(&testLogger1);
	ModAssert::RemoveLogger(&testLogger2);
}
