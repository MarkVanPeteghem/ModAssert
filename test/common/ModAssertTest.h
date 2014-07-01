//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_TEST_H__QM
#define MOD_ASSERT_TEST_H__QM

#include "modassert/assert.hpp"
#include "modassert/responder.hpp"
#include "modassert/properties.hpp"
#include "richbool/string.hpp"

#ifdef RICHBOOL_USE_WX
#include "richbool/wxstring.hpp"
#define STRINGCMP RichBool::WxStringCmp()
#else
#include "richbool/stdstring.hpp"
#define STRINGCMP RichBool::StringCompare()
#endif

class ModAssertTest
{
public:
	ModAssertTest(const char *name_);
	virtual void run() = 0;

	static void RunTests();
	static int GetNrTests() { return nrTests; }

	const char * GetName() const { return name; }

private:
	const char *name;
	ModAssertTest *next;
	bool loggerCalled;

	static ModAssertTest *tests;
	static int nrTests;
};

bool CheckLoggerCalled();

#define MA_TEST(NAME) \
	class ModAssertTest##NAME: public ModAssertTest \
	{ \
	public: \
		ModAssertTest##NAME(): ModAssertTest(#NAME) {} \
		virtual void run(); \
	} modAssertTest##NAME; \
	void ModAssertTest##NAME::run()

const int undefinedLevel = -10;

class ModAssertTestHandler: public ModAssert::Responder
{
public:
	ModAssertTestHandler();
	static void Activate();
	static void SetReturnValue(ModAssert::Response response_)
	{
		response = response_;
	}
	static ModAssert::Response GetReturnValue()
	{
		return response;
	}

	static void SetExpectedFailure(
		bool success,
		bool isCheck,
		bool isUnconditional,
		const ModAssert::Context &context,
		const char* condition,
		const RichBool::SharedAnalysis analysis,
		const ModAssert::ParameterList *parList,
		const ModAssert::GroupList &groupList,
		int level,
		const char *action);

	static void ExpectNoFailure(const ModAssert::Context &context);

	static int GetNrErrors();
	static void IncNrMetaAsserts();
	static int GetNrMetaAsserts();

	static void SetIgnoreAssertions(bool ignore);
protected:
	virtual ModAssert::Response OnAssert(
			const ModAssert::Properties &,
			const ModAssert::Result &,
			bool display) const;

	static ModAssert::Response response;
	static bool ignoreAssertions, active;

	void CheckAssertion(bool success, bool isCheck, bool isUnconditional,
		const ModAssert::Context &context,
		const char* condition, const RichBool::SharedAnalysis analysis,
		const ModAssert::ParameterList *parList, const ModAssert::GroupList *groupList,
		const char *action) const;
	void ReportUnexpectedAssertion(bool success, bool isCheck, bool isUnconditional,
		const ModAssert::Context &context,
		const char* condition, const RichBool::SharedAnalysis analysis,
		const ModAssert::ParameterList *parList, const ModAssert::GroupList *groupList,
		const char *action) const;

	// expected failure:
	mutable bool m_success, m_isCheck, m_isUnconditional;
	mutable ModAssert::Context m_context;
	mutable const char *m_condition;
	mutable RichBool::SharedAnalysis m_analysis;
	mutable const ModAssert::ParameterList *m_parList;
	mutable RichBool::detail::StringArray m_groupList;
	mutable const char *m_action;
	mutable int m_level;

	mutable bool m_expectFailure;
};

#define EXPECT_NO_FAILURE ModAssertTestHandler::ExpectNoFailure(MOD_ASSERT_CONTEXT)

#if MOD_ASSERT_REPORTS
	#define EXPECT_ASSERT(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, false, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(ModAssert::Error), \
			undefinedLevel, ACTION)

	#define EXPECT_FAIL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, false, true, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(ModAssert::Error), \
			undefinedLevel, ACTION)

	#define EXPECT_ASSERT_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, false, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			undefinedLevel, ACTION)

	#define EXPECT_FAIL_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, false, true, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			undefinedLevel, ACTION)

	#define EXPECT_ASSERT_GL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, LEVEL, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, false, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			LEVEL, ACTION)

#else
	#define EXPECT_ASSERT(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION)
	#define EXPECT_ASSERT_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION)
	#define EXPECT_ASSERT_GL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, LEVEL, ACTION)
	#define EXPECT_FAIL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION)
	#define EXPECT_FAIL_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION)
#endif // #if MOD_ASSERT_REPORTS


#if MOD_CHECK_REPORTS
	#define EXPECT_CHECK(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, true, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(ModAssert::Error), \
			undefinedLevel, ACTION)

	#define EXPECT_CHECK_FAIL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, true, true, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(ModAssert::Error), \
			undefinedLevel, ACTION)

	#define EXPECT_CHECK_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, true, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			undefinedLevel, ACTION)

	#define EXPECT_CHECK_FAIL_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, true, true, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			undefinedLevel, ACTION)

	#define EXPECT_CHECK_GL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, LEVEL, ACTION) \
		ModAssertTestHandler::SetExpectedFailure(SUCCESS, true, false, MOD_ASSERT_CONTEXT, COND, \
			INFO, MOD_ASSERT_DATA, ModAssert::MakeGroupList(TYPE), \
			LEVEL, ACTION)

#else
	#define EXPECT_CHECK(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION)
	#define EXPECT_CHECK_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION)
	#define EXPECT_CHECK_GL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, LEVEL, ACTION)
	#define EXPECT_CHECK_FAIL(SUCCESS, COND, INFO, MOD_ASSERT_DATA, ACTION)
	#define EXPECT_CHECK_FAIL_G(SUCCESS, COND, INFO, MOD_ASSERT_DATA, TYPE, ACTION)
#endif // #if MOD_CHECK_REPORTS

void SetAllowBreakIntoDebugger(bool b);
bool GetAllowBreakIntoDebugger();

void MetaFailure(const char *condition,
				 RichBool::SharedAnalysis analysis,
				 const ModAssert::Context &context,
				 const ModAssert::ParameterList *parList=0);

// always returns 2, but it is a function to prevent warnings in the macros META_ASSERT and META_ASSERT_P
int GetRichboolLevel();

#define META_ASSERT(cond) \
	if (GetRichboolLevel()!=0) { \
		ModAssertTestHandler::IncNrMetaAsserts(); \
		int richbool_level = GetRichboolLevel(); \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = (cond); \
		if (!richbool()) { \
			MetaFailure(#cond, richbool.GetAnalysis(), MOD_ASSERT_CONTEXT, 0); \
		} \
	} else 0

#define META_ASSERT_P(params, cond) \
	if (GetRichboolLevel()!=0) { \
		ModAssertTestHandler::IncNrMetaAsserts(); \
		int richbool_level = GetRichboolLevel(); \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = (cond); \
		if (!richbool()) { \
			MOD_ASSERT_PARM(params) \
			MetaFailure(#cond, richbool.GetAnalysis(), MOD_ASSERT_CONTEXT, &modassert_pl); \
		} \
	} else 0

#endif // #ifndef MOD_ASSERT_TEST_H__QM
