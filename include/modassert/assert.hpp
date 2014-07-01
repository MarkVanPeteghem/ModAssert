//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_H__QM
#define MOD_ASSERT_H__QM

// Header file for MOD_ASSERT, MOD_VERIFY, MOD_CHECK, MOD_FAIL, MOD_CHECK_FAIL
// and variations, that have much more functionality
// than the standard assert(...)

#include "modassert/levels.hpp"
#include "modassert/ifsuccess.hpp"
#include "modassert/report_type.hpp"
#include "modassert/context.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/response.hpp"
#include "modassert/hold_ref.hpp"
#include "modassert/use_bool.hpp"
#include "modassert/category.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "richbool/bool.hpp"

// Important: defining MODASSERT_IMPORT or MODASSERT_EXPORT hs not yet been tested.
#if defined(MODASSERT_IMPORT)
	#define MODASSERT_API __declspec(dllimport)
#elif defined(MODASSERT_EXPORT)
	#define MODASSERT_API __declspec(dllexport)
#else
	#define MODASSERT_API
#endif

#if defined(__unix__) && defined(__i386__)
	#define MOD_ASSERT_BREAK_HERE __asm__ __volatile__ ("int $03")
	// Alternative: kill(getpid(),SIGSTOP)
#elif defined(__i386__)
	#define MOD_ASSERT_BREAK_HERE __asm("int $03");
#elif defined(_M_IX86)
	#define MOD_ASSERT_BREAK_HERE __asm { int 3 }
#elif defined(__UNIX__)
    #include <signal.h>
    #define MOD_ASSERT_BREAK_HERE raise(SIGTRAP)
#elif defined(macintosh) && macintosh
	#if __powerc
		#define MOD_ASSERT_BREAK_HERE Debugger()
	#else
		#define MOD_ASSERT_BREAK_HERE SysBreak()
	#endif
#else
	#define MOD_ASSERT_BREAK_HERE ModAssert::ManualBreak()
#endif



#ifdef MOD_ASSERT_REPORTS
	// Did you intend to define MOD_ASSERT_REPORT instead?
	#error You should not define MOD_ASSERT_REPORTS
#endif

#ifdef MOD_CHECK_REPORTS
	// Did you intend to define MOD_CHECK_REPORT instead?
	#error You should not define MOD_CHECK_REPORTS
#endif

#if (!defined(NDEBUG) || defined(MOD_ASSERT_REPORT)) && !defined(MOD_ASSERT_DONT_REPORT)

	#if !defined(MOD_ASSERT_DONT_REPORT_FILE)
		#define MOD_ASSERT_REPORTS 1
	#else
		#define MOD_ASSERT_REPORTS 0
	#endif

#else

	#if !defined(MOD_ASSERT_REPORT_FILE)
		#define MOD_ASSERT_REPORTS 0
	#else
		#define MOD_ASSERT_REPORTS 1
	#endif

#endif

#if (!defined(NDEBUG) || defined(MOD_CHECK_REPORT)) && !defined(MOD_CHECK_DONT_REPORT)

	#if !defined(MOD_CHECK_DONT_REPORT_FILE)
		#define MOD_CHECK_REPORTS 1
	#else
		#define MOD_CHECK_REPORTS 0
	#endif

#else

	#if !defined(MOD_CHECK_REPORT_FILE)
		#define MOD_CHECK_REPORTS 0
	#else
		#define MOD_CHECK_REPORTS 1
	#endif

#endif

#ifndef MOD_ASSERT_DEFAULT_OPTIONAL_ACTION
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION NULL
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1 NULL
#else
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1 MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT
#endif

#ifndef MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V ModAssert::Nop
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2 NULL
#else
#define MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2 MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT
#endif

// save compile time if neither are reported:
#if MOD_ASSERT_REPORTS || MOD_CHECK_REPORTS

namespace ModAssert
{
	extern Category<Assertions> categoryAsserts;
	extern Category<Checks> categoryChecks;

	MODASSERT_API Response HandleAssert(
		const Properties &properties,
		const Result &result,
		bool *displayThis);

	// for backward compatibility:
	inline Response HandleAssert(
		bool success,
		bool isCheck,
		const Context &context,
		const char* condition,
		const RichBool::SharedAnalysis &analysis,
		const ParameterList *parList,
		const GroupList &groupList,
		const char *optionalDescr,
		bool *displayThis)
	{
		const CategoryBase &category = isCheck ?
			(const CategoryBase&) categoryChecks :
			(const CategoryBase&) categoryAsserts ;
		Properties properties(&category, context,
			condition, groupList, optionalDescr, displayThis!=0);
		Result result(success, analysis, parList);
		return HandleAssert(properties, result, displayThis);
	}


	// this function is provided for environments that don't allow
	// hardcoded breaking into the debugger, so the user can still
	// manually add a breakpoint in this method
	void ManualBreak();

	MODASSERT_API void ExecuteGlobalOptionalAction();

	MODASSERT_API void HandleResponse(Response response, const Properties &properties,
		const Result &result);

	// Note: assertions and checks that are expressions can't store a
	// static boolean, so the last parameter to HandleAssert is NULL.
#define MOD_ASSERT_HANDLE_V(analysis) \
	if (fail || groupList.IfSuccess()) { \
		Properties properties(&category, context, \
			str, groupList, optionalDescr, false); \
		Result result(!fail, analysis, parList); \
		Response ma_response = \
			HandleAssert(properties, result, NULL); \
		if (ma_response&BreakIntoDebugger) \
		{ MOD_ASSERT_BREAK_HERE; } \
		if (ma_response&Optional) \
		{ optionalAction(); } \
		HandleResponse(ma_response, properties, result); \
	}

	// template methods used in assertion macros that return a value:
	template<typename T, typename OptionalAction, typename FailureAction>
	T HandleAssertAndReturnValue(const T& t, const char *str,
		const ParameterList *parList, const GroupList &groupList, const Context &context,
		OptionalAction optionalAction, const char *optionalDescr,
		FailureAction failureAction,
		const CategoryBase &category)
	{
		bool fail = !t;
		MOD_ASSERT_HANDLE_V(NULL)
		if (fail)
			failureAction();
		return t;
	}

	template<typename T, class Bind, typename OptionalAction, typename FailureAction>
	T HandleAssertAndReturnValue(const Bind &bind, const char *str1, const T& t, const char *str,
		const ParameterList *parList, const GroupList &groupList, const Context &context,
		OptionalAction optionalAction, const char *optionalDescr,
		FailureAction failureAction,
		const CategoryBase &category)
	{
		bool fail = !bind(t);
		MOD_ASSERT_HANDLE_V(bind.Analyse(t, str1))
		if (fail)
			failureAction();
		return t;
	}

	template<typename T, typename OptionalAction>
	UseBool HandleAssertAndReturnBool(const T& t, const char *str,
		const ParameterList *parList, const GroupList &groupList, const Context &context,
		OptionalAction optionalAction, const char *optionalDescr,
		const CategoryBase &category)
	{
		bool fail = !t;
		MOD_ASSERT_HANDLE_V(NULL);
		UseBool b(!fail, context);
		return b;
	}

	template<typename T, class Bind, typename OptionalAction>
	UseBool HandleAssertAndReturnBool(const Bind &bind, const char *str1, const T& t, const char *str,
		const ParameterList *parList, const GroupList &groupList, const Context &context,
		OptionalAction optionalAction, const char *optionalDescr,
		const CategoryBase &category)
	{
		bool fail = !bind(t);
		MOD_ASSERT_HANDLE_V(bind.Analyse(t, str1))
		UseBool b(!fail, context);
		return b;
	}
#undef MOD_ASSERT_HANDLE_V
}

#endif

namespace ModAssert
{
	template<typename T, typename FailureAction>
	T EvaluateAndReturnValue(const T& t, FailureAction failureAction)
	{
		if (!t)
			failureAction();
		return t;
	}

	template<typename T, class Bind, typename FailureAction>
	T EvaluateAndReturnValue(const Bind &bind, const char *, const T& t,
		FailureAction failureAction)
	{
		if (!bind(t))
			failureAction();
		return t;
	}

	template<typename T>
	UseBool EvaluateAndReturnBool(const T& t, const Context &context)
	{
		UseBool b(!!t, context);
		return b;
	}

	template<typename T, class Bind>
	UseBool EvaluateAndReturnBool(const Bind &bind, const char *, const T& t,
		const Context &context)
	{
		UseBool b(bind(t), context);
		return b;
	}

	// A struct that is used as the argument if no optional
	// action is chosen in a returning verify macro:
	struct Nop_
	{
		void operator()() const {}
	};

	extern Nop_ Nop;
}

// If MOD_ASSERT_NO_TEXT is defined before assert.hpp is included,
// the condition text is replaced by (char*)1, to indicate that there
// is a condition but that we can't see it.
// This way the properties class can distinguish between assertions (and checks)
// with a condition and unconditional assertions (and checks) for which
// the condition text is a null pointer.
#ifdef MOD_ASSERT_NO_TEXT
#define MOD_ASSERT_STR_COND(text) (char*)1
#else
#define MOD_ASSERT_STR_COND(text) text
#endif

// we use if-blocks instead of a switch statement here to handle the response,
// because the optional action could be break,
// and because more than one response could be chosen

// note that the order of the checks on the responses is important

#define MOD_ASSERT_HANDLE(success, category, str_cond, analysis, parList, \
			 groupList, optionalAction, optionalActionDescr) \
	const ModAssert::GroupList &modassert_gl = ModAssert::MakeGroupList(groupList); \
	parList \
	const ModAssert::Context &modassert_context = MOD_ASSERT_CONTEXT; \
	ModAssert::Properties modassert_properties(&category, modassert_context, \
		str_cond, modassert_gl, optionalActionDescr, true); \
	ModAssert::Result modassert_result(success, analysis, &modassert_pl); \
	ModAssert::Response modassert_response = ModAssert::HandleAssert(modassert_properties, \
		modassert_result, &modassert_display); \
	if (modassert_response&ModAssert::BreakIntoDebugger)\
	{ MOD_ASSERT_BREAK_HERE; }\
	if (modassert_response&ModAssert::Optional)\
	{ optionalAction; }\
	ModAssert::HandleResponse(modassert_response, modassert_properties, modassert_result);



#ifndef MOD_ASSERT_LEVEL
	#define MOD_ASSERT_LEVEL 0
#endif


#if defined(_MSC_VER)
	#define MOD_ASSERT_STRINGIZE(text) MOD_ASSERT_STRINGIZE_1((text))
	#define MOD_ASSERT_STRINGIZE_1(text) MOD_ASSERT_STRINGIZE_2 ## (text)
	#define MOD_ASSERT_STRINGIZE_2(text) MOD_ASSERT_STRINGIZE_IMPL ## text
#elif defined (__MWERKS__)
	#define MOD_ASSERT_STRINGIZE(text) MOD_ASSERT_STRINGIZE_1((text))
	#define MOD_ASSERT_STRINGIZE_1(text) MOD_ASSERT_STRINGIZE_IMPL ## text
#else
	#define MOD_ASSERT_STRINGIZE(text) MOD_ASSERT_STRINGIZE_IMPL(text)
#endif
#define MOD_ASSERT_STRINGIZE_IMPL(text) #text


#define MOD_ASSERT_NO_PARM ModAssert::ParameterList &modassert_pl = *((ModAssert::ParameterList*)NULL);
#define MOD_ASSERT_SPECIFIC_PARM(params) \
	ModAssert::ParameterList modassert_pl(MOD_ASSERT_STRINGIZE(params)); \
	modassert_pl << params;

#ifdef MOD_ASSERT_DEFAULT_PARAMETERS
	#define MOD_ASSERT_DEFAULT_PARM \
		ModAssert::ParameterList modassert_pl(MOD_ASSERT_STRINGIZE(MOD_ASSERT_DEFAULT_PARAMETERS)); \
		modassert_pl << MOD_ASSERT_DEFAULT_PARAMETERS;
	#define MOD_ASSERT_PARM(params) \
		ModAssert::ParameterList modassert_pl(MOD_ASSERT_STRINGIZE(params) "<<" MOD_ASSERT_STRINGIZE(MOD_ASSERT_DEFAULT_PARAMETERS)); \
		modassert_pl << params << MOD_ASSERT_DEFAULT_PARAMETERS;
#else
	#define MOD_ASSERT_DEFAULT_PARM MOD_ASSERT_NO_PARM
	#define MOD_ASSERT_PARM(params) MOD_ASSERT_SPECIFIC_PARM(params)
#endif


#ifdef MOD_ASSERT_DEFAULT_PARAMETERS_V
	#define MOD_ASSERT_DEFAULT_PARM_V \
	&(ModAssert::ParameterList().AddParameters( \
		ModAssert::MakeHoldReferencesAndString( \
			ModAssert::MakeHoldReferences MOD_ASSERT_DEFAULT_PARAMETERS_V , MOD_ASSERT_STRINGIZE(MOD_ASSERT_DEFAULT_PARAMETERS_V))))
	#define MOD_ASSERT_PARM_V(params) \
	&(ModAssert::ParameterList().AddParameters( \
		ModAssert::MakeDoubleHoldReferencesAndString( \
			ModAssert::MakeHoldReferences params , MOD_ASSERT_STRINGIZE(params), \
			ModAssert::MakeHoldReferences MOD_ASSERT_DEFAULT_PARAMETERS_V , MOD_ASSERT_STRINGIZE(MOD_ASSERT_DEFAULT_PARAMETERS_V))))
#else
	#define MOD_ASSERT_DEFAULT_PARM_V ((ModAssert::ParameterList*)NULL)
	#define MOD_ASSERT_PARM_V(params) \
	&(ModAssert::ParameterList().AddParameters( \
		ModAssert::MakeHoldReferencesAndString( \
			ModAssert::MakeHoldReferences params , MOD_ASSERT_STRINGIZE(params))))
#endif

#define MOD_ASSERT_NO_PARM_V ((ModAssert::ParameterList*)NULL)
#define MOD_ASSERT_SPECIFIC_PARM_V(params) \
	&(ModAssert::ParameterList().AddParameters( \
		ModAssert::MakeHoldReferencesAndString( \
			ModAssert::MakeHoldReferences params , MOD_ASSERT_STRINGIZE(params))))


#if MOD_ASSERT_REPORTS

#define IF_MOD_ASSERT_REPORTS(a) a
#define IF_NOT_MOD_ASSERT_REPORTS(a)
#define IF_MOD_ASSERT_REPORTS_ELSE(a,b) a

#ifndef MOD_ASSERT_DEFAULT_GROUP
#define MOD_ASSERT_DEFAULT_GROUP ModAssert::Error
#endif

#define MOD_ASSERT_GROUPS_ENABLED(groups) \
	( (groups).enabled && \
		( (groups).level >= MOD_ASSERT_LEVEL ) )

// we don't use 'do { ... } while (false)' like in many macros,
// but 'if (...) { ... } else 0',
// because the optional action could be break

#define MOD_ASSERT_GENERAL(cond, str_cond, parameterlist, groups, optional, optionalDescr) \
	if (MOD_ASSERT_GROUPS_ENABLED(groups))\
	{\
		static bool modassert_display = true;\
		int richbool_level = (groups).ifSuccess ? 3 : 2; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = (cond); \
		if (!richbool() || (groups).ifSuccess) { \
			MOD_ASSERT_HANDLE(richbool(), ModAssert::categoryAsserts, MOD_ASSERT_STR_COND(str_cond), richbool.GetAnalysis(), \
			parameterlist, (groups), optional, optionalDescr); \
		} \
	} else 0


#define MOD_ASSERT(cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_P(params, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_ASSERT_O(optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)
#define MOD_ASSERT_PO(params, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_ASSERT_G(groups, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_PG(params, groups, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_ASSERT_GO(groups, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, groups, optional, optionalDescr)
#define MOD_ASSERT_PGO(params, groups, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), groups, optional, optionalDescr)

#define MOD_ASSERT_NP(cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_NPO(optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_ASSERT_NPG(groups, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_NPGO(groups, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, groups, optional, optionalDescr)

#define MOD_ASSERT_SP(params, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_SPO(params, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_ASSERT_SPG(params, groups, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_ASSERT_SPGO(params, groups, optional, optionalDescr, cond) \
	MOD_ASSERT_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), groups, optional, optionalDescr)

// MOD_VERIFY macros are implemented differently,
// because if the grouplist is disabled,
// the expression still has to be evaluated,
// whereas MOD_ASSERT can optimize it away by evaluating nothing

#define MOD_VERIFY_GENERAL(cond, str_cond, params, groups, optional, optionalDescr) \
	if (true) { \
		static bool modassert_display = true;\
		int richbool_level = MOD_ASSERT_GROUPS_ENABLED(groups) ? ((groups).ifSuccess ? 3 : 2) : 0; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = (cond); \
		if ( MOD_ASSERT_GROUPS_ENABLED(groups) && ((groups).ifSuccess || !richbool()) ) { \
			MOD_ASSERT_HANDLE(richbool(), ModAssert::categoryAsserts, MOD_ASSERT_STR_COND(str_cond), richbool.GetAnalysis(), \
				params, (groups), optional, optionalDescr); \
		} \
	} else 0

#define MOD_VERIFY(cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_P(params, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_VERIFY_O(optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)
#define MOD_VERIFY_PO(params, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_VERIFY_G(groups, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_PG(params, groups, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_VERIFY_GO(groups, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_DEFAULT_PARM, groups, optional, optionalDescr)
#define MOD_VERIFY_PGO(params, groups, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_PARM(params), groups, optional, optionalDescr)

#define MOD_VERIFY_NP(cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_NPO(optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_VERIFY_NPG(groups, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_NPGO(groups, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_NO_PARM, groups, optional, optionalDescr)

#define MOD_VERIFY_SP(params, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_SPO(params, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_VERIFY_SPG(params, groups, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_VERIFY_SPGO(params, groups, optional, optionalDescr, cond) \
	MOD_VERIFY_GENERAL(cond, #cond, MOD_ASSERT_SPECIFIC_PARM(params), groups, optional, optionalDescr)



#define MOD_FAIL_GENERAL(params, groups, optional, optionalDescr) \
	if (MOD_ASSERT_GROUPS_ENABLED(groups))\
	{\
		static bool modassert_display = true;\
		MOD_ASSERT_HANDLE(false, ModAssert::categoryAsserts, NULL, NULL, params, \
			(groups), optional, optionalDescr); \
	} else 0

#define MOD_FAIL \
	MOD_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_P(params) \
	MOD_FAIL_GENERAL(MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_FAIL_O(optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)
#define MOD_FAIL_PO(params, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_FAIL_G(groups) \
	MOD_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_PG(params, groups) \
	MOD_FAIL_GENERAL(MOD_ASSERT_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_FAIL_GO(groups, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, groups, optional, optionalDescr)
#define MOD_FAIL_PGO(params, groups, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_PARM(params), groups, optional, optionalDescr)

#define MOD_FAIL_NP \
	MOD_FAIL_GENERAL(MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_NPO(optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_NO_PARM, MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_FAIL_NPG(groups) \
	MOD_FAIL_GENERAL(MOD_ASSERT_NO_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_NPGO(groups, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_NO_PARM, groups, optional, optionalDescr)

#define MOD_FAIL_SP(params) \
	MOD_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_SPO(params, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), MOD_ASSERT_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_FAIL_SPG(params, groups) \
	MOD_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_FAIL_SPGO(params, groups, optional, optionalDescr) \
	MOD_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), groups, optional, optionalDescr)


#define MOD_VERIFY_V(cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VG(group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VP(par, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VPG(par, group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))

#define MOD_VERIFY_VO(optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VGO(group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VPO(par, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VPGO(par, group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))

#define MOD_VERIFY_VNP(cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VNPG(group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VSP(par, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VSPG(par, group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))

#define MOD_VERIFY_VNPO(optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VNPGO(group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VSPO(par, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))
#define MOD_VERIFY_VSPGO(par, group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::Nop, ModAssert::categoryAsserts) : (cond))

#define MOD_VERIFY_B(cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BP(par, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BG(group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BPG(par, group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_VERIFY_BO(optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BPO(par, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BGO(group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BPGO(par, group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_VERIFY_BNP(cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BSP(par, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BNPG(group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BSPG(par, group, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_VERIFY_BNPO(optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BSPO(par, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(MOD_ASSERT_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_ASSERT_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BNPGO(group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_VERIFY_BSPGO(par, group, optional, optionalDescr, cond) \
	(MOD_ASSERT_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryAsserts) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#else // #if MOD_ASSERT_REPORTS


#define IF_MOD_ASSERT_REPORTS(a)
#define IF_NOT_MOD_ASSERT_REPORTS(a) a
#define IF_MOD_ASSERT_REPORTS_ELSE(a,b) b

#define MOD_ASSERT(cond) do {} while (false)
#define MOD_ASSERT_P(params, cond) do {} while (false)

#define MOD_ASSERT_O(optional, optionalDescr, cond) do {} while (false)
#define MOD_ASSERT_PO(params, optional, optionalDescr, cond) do {} while (false)

#define MOD_ASSERT_G(groups, cond) do {} while (false)
#define MOD_ASSERT_PG(params, groups, cond) do {} while (false)

#define MOD_ASSERT_GO(cond, groups, optional, optionalDescr) do {} while (false)
#define MOD_ASSERT_PGO(params, groups, optional, optionalDescr, cond) do {} while (false)

#define MOD_ASSERT_NP(cond) do {} while (false)
#define MOD_ASSERT_SP(params, cond) do {} while (false)

#define MOD_ASSERT_NPO(optional, optionalDescr, cond) do {} while (false)
#define MOD_ASSERT_SPO(params, optional, optionalDescr, cond) do {} while (false)

#define MOD_ASSERT_NPG(groups, cond) do {} while (false)
#define MOD_ASSERT_SPG(params, groups, cond) do {} while (false)

#define MOD_ASSERT_NPGO(cond, groups, optional, optionalDescr) do {} while (false)
#define MOD_ASSERT_SPGO(params, groups, optional, optionalDescr, cond) do {} while (false)


// richbool_level is 0 for MOD_VERIFY*, because only the arguments
// of the condition need to be evaluated
#define MOD_VERIFY(cond) \
	do { \
		int richbool_level = 0; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		(void)(cond); \
	} while (false)
#define MOD_VERIFY_P(params, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_O(optional, optionalDescr, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_PO(params, optional, optionalDescr, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_G(groups, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_PG(params, groups, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_GO(groups, optional, optionalDescr, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_PGO(params, groups, optional, optionalDescr, cond) \
	MOD_VERIFY(cond)

#define MOD_VERIFY_NP(cond) MOD_VERIFY(cond)
#define MOD_VERIFY_SP(params, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_NPO(optional, optionalDescr, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_SPO(params, optional, optionalDescr, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_NPG(groups, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_SPG(params, groups, cond) MOD_VERIFY(cond)

#define MOD_VERIFY_NPGO(groups, optional, optionalDescr, cond) MOD_VERIFY(cond)
#define MOD_VERIFY_SPGO(params, groups, optional, optionalDescr, cond) \
	MOD_VERIFY(cond)


#define MOD_FAIL do {} while (false)
#define MOD_FAIL_P(msg) do {} while (false)

#define MOD_FAIL_O(optional, optionalDescr) do {} while (false)
#define MOD_FAIL_PO(msg, optional, optionalDescr) do {} while (false)

#define MOD_FAIL_G(groups) do {} while (false)
#define MOD_FAIL_PG(msg, groups) do {} while (false)

#define MOD_FAIL_GO(groups, optional, optionalDescr) do {} while (false)
#define MOD_FAIL_PGO(msg, groups, optional, optionalDescr) do {} while (false)

#define MOD_FAIL_NP do {} while (false)
#define MOD_FAIL_SP(msg) do {} while (false)

#define MOD_FAIL_NPO(optional, optionalDescr) do {} while (false)
#define MOD_FAIL_SPO(msg, optional, optionalDescr) do {} while (false)

#define MOD_FAIL_NPG(groups) do {} while (false)
#define MOD_FAIL_SPG(msg, groups) do {} while (false)

#define MOD_FAIL_NPGO(groups, optional, optionalDescr) do {} while (false)
#define MOD_FAIL_SPGO(msg, groups, optional, optionalDescr) do {} while (false)


#define MOD_VERIFY_V(cond) (cond)
#define MOD_VERIFY_VP(par, cond) (cond)
#define MOD_VERIFY_VG(group, cond) (cond)
#define MOD_VERIFY_VPG(par, group, cond) (cond)

#define MOD_VERIFY_VO(optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VPO(par, optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VGO(group, optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VPGO(par, group, optional, optionalDesc, cond) (cond)

#define MOD_VERIFY_VNP(cond) (cond)
#define MOD_VERIFY_VSP(par, cond) (cond)
#define MOD_VERIFY_VNPG(group, cond) (cond)
#define MOD_VERIFY_VSPG(par, group, cond) (cond)

#define MOD_VERIFY_VNPO(optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VSPO(par, optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VNPGO(group, optional, optionalDesc, cond) (cond)
#define MOD_VERIFY_VSPGO(par, group, optional, optionalDesc, cond) (cond)

#define MOD_VERIFY_B(cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BP(par, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BG(group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BPG(par, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_VERIFY_BO(optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BPO(par, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BGO(group, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BPGO(par, optional, optionalDescr, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_VERIFY_BNP(cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BSP(par, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BNPG(group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BSPG(par, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_VERIFY_BNPO(optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BSPO(par, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BNPGO(group, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_VERIFY_BSPGO(par, optional, optionalDescr, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)


#endif // #if MOD_ASSERT_REPORTS



#ifndef MOD_CHECK_LEVEL
	#define MOD_CHECK_LEVEL 0
#endif

#if MOD_CHECK_REPORTS

#define IF_MOD_CHECK_REPORTS(a) a
#define IF_NOT_MOD_CHECK_REPORTS(a)
#define IF_MOD_CHECK_REPORTS_ELSE(a,b) a

#ifndef MOD_CHECK_DEFAULT_GROUP
#define MOD_CHECK_DEFAULT_GROUP ModAssert::Error
#endif

#define MOD_CHECK_GROUPS_ENABLED(groups) \
	( (groups).enabled && \
		( (groups).level >= MOD_CHECK_LEVEL ) )

#define MOD_CHECK_GENERAL(cond, str_cond, failAction, params, groups, optional, optionalDescr) \
	if (true) { \
		static bool modassert_display = true;\
		int richbool_level = MOD_CHECK_GROUPS_ENABLED(groups) ? ((groups).ifSuccess ? 3 : 2) : 1; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = (cond); \
		if ( MOD_CHECK_GROUPS_ENABLED(groups) && (!richbool() || (groups).ifSuccess) ) { \
			MOD_ASSERT_HANDLE(richbool(), ModAssert::categoryChecks, MOD_ASSERT_STR_COND(str_cond), richbool.GetAnalysis(), \
				params, (groups), optional, optionalDescr); \
		} \
		if (!richbool()) { failAction; } \
	} else 0


#define MOD_CHECK(cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_DEFAULT_PARM, MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_CHECK_P(params, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_PARM(params), MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_CHECK_O(optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_DEFAULT_PARM, MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr)
#define MOD_CHECK_PO(params, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_PARM(params), MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_CHECK_G(groups, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_DEFAULT_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_CHECK_PG(params, groups, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_CHECK_GO(groups, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_DEFAULT_PARM, groups, optional, optionalDescr)
#define MOD_CHECK_PGO(params, groups, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_PARM(params), groups, optional, optionalDescr)


#define MOD_CHECK_NP(cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_NO_PARM, MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_CHECK_SP(params, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_SPECIFIC_PARM(params), MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_CHECK_NPO(optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_NO_PARM, MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr)
#define MOD_CHECK_SPO(params, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_SPECIFIC_PARM(params), MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr)

#define MOD_CHECK_NPG(groups, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_NO_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)
#define MOD_CHECK_SPG(params, groups, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_SPECIFIC_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1)

#define MOD_CHECK_NPGO(groups, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_NO_PARM, groups, optional, optionalDescr)
#define MOD_CHECK_SPGO(params, groups, optional, optionalDescr, cond, action) \
	MOD_CHECK_GENERAL(cond, #cond, action, MOD_ASSERT_SPECIFIC_PARM(params), groups, optional, optionalDescr)



#define MOD_CHECK_FAIL_GENERAL(params, groups, optional, optionalDescr, action) \
	if (MOD_CHECK_GROUPS_ENABLED(groups))\
	{\
		static bool modassert_display = true;\
		MOD_ASSERT_HANDLE(false, ModAssert::categoryChecks, NULL, NULL, params, \
			(groups), optional, optionalDescr); \
		action; \
	} else 0


#define MOD_CHECK_FAIL(action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)
#define MOD_CHECK_FAIL_P(params, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_PARM(params), MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)

#define MOD_CHECK_FAIL_O(optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr, action)
#define MOD_CHECK_FAIL_PO(params, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_PARM(params), MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr, action)

#define MOD_CHECK_FAIL_G(groups, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)
#define MOD_CHECK_FAIL_PG(params, groups, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)

#define MOD_CHECK_FAIL_GO(groups, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_DEFAULT_PARM, groups, optional, optionalDescr, action)
#define MOD_CHECK_FAIL_PGO(params, groups, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_PARM(params), groups, optional, optionalDescr, action)


#define MOD_CHECK_FAIL_NP(action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_NO_PARM, MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)
#define MOD_CHECK_FAIL_SP(params, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), MOD_CHECK_DEFAULT_GROUP, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)

#define MOD_CHECK_FAIL_NPO(optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_NO_PARM, MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr, action)
#define MOD_CHECK_FAIL_SPO(params, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), MOD_CHECK_DEFAULT_GROUP, optional, optionalDescr, action)

#define MOD_CHECK_FAIL_NPG(groups, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_NO_PARM, groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)
#define MOD_CHECK_FAIL_SPG(params, groups, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), groups, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT1, action)

#define MOD_CHECK_FAIL_NPGO(groups, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_NO_PARM, groups, optional, optionalDescr, action)
#define MOD_CHECK_FAIL_SPGO(params, groups, optional, optionalDescr, action) \
	MOD_CHECK_FAIL_GENERAL(MOD_ASSERT_SPECIFIC_PARM(params), groups, optional, optionalDescr, action)


#define MOD_CHECK_V(cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VP(par, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VG(group, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VPG(par, group, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))

#define MOD_CHECK_VO(optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VPO(par, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VGO(group, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VPGO(par, group, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))

#define MOD_CHECK_VNP(cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VSP(par, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VNPG(group, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VSPG(par, group, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))

#define MOD_CHECK_VNPO(optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VSPO(par, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VNPGO(group, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))
#define MOD_CHECK_VSPGO(par, group, optional, optionalDescr, cond, action) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnValue(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, action, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnValue(cond, action))


#define MOD_CHECK_B(cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BP(par, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BG(group, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BPG(par, group, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_CHECK_BO(optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BPO(par, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BGO(group, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BPGO(par, group, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_CHECK_BNP(cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BSP(par, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BNPG(group, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_DEFAULT_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BSPG(par, group, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_V, MOD_ASSERT_DEFAULT_OPTIONAL_ACTION_TEXT2, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#define MOD_CHECK_BNPO(optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BSPO(par, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(MOD_CHECK_DEFAULT_GROUP) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(MOD_CHECK_DEFAULT_GROUP), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BNPGO(group, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_NO_PARM_V, \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))
#define MOD_CHECK_BSPGO(par, group, optional, optionalDescr, cond) \
	(MOD_CHECK_GROUPS_ENABLED(group) ? ModAssert::HandleAssertAndReturnBool(cond, MOD_ASSERT_STR_COND(#cond), MOD_ASSERT_SPECIFIC_PARM_V(par), \
	ModAssert::MakeGroupList(group), MOD_ASSERT_CONTEXT, optional, optionalDescr, ModAssert::categoryChecks) \
	: ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT))

#else

#define IF_MOD_CHECK_REPORTS(a)
#define IF_NOT_MOD_CHECK_REPORTS(a) a
#define IF_MOD_CHECK_REPORTS_ELSE(a,b) b

// richbool_level is 1 for MOD_CHECK*, because
// the condition needs to be evaluated
#define MOD_CHECK(cond, action) \
	if (true) { \
		int richbool_level = 1; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool_bool = (cond); \
		if (!richbool_bool()) { \
			action; \
		} \
	} else 0

#define MOD_CHECK_P(params, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_O(optional, optionalDescr, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_PO(params, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_G(groups, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_PG(params, groups, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_GO(groups, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_PGO(params, groups, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)


#define MOD_CHECK_NP(cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_SP(params, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_NPO(optional, optionalDescr, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_SPO(params, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_NPG(groups, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_SPG(params, groups, cond, action) MOD_CHECK(cond, action)

#define MOD_CHECK_NPGO(groups, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)
#define MOD_CHECK_SPGO(params, groups, optional, optionalDescr, cond, action) MOD_CHECK(cond, action)


#define MOD_CHECK_FAIL(action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_P(params, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_O(optional, optionalDescr, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_PO(params, optional, optionalDescr, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_G(groups, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_PG(params, groups, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_GO(groups, optional, optionalDescr, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_PGO(params, groups, optional, optionalDescr, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_NP(action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_SP(params, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_NPO(optional, optionalDescr, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_SPO(params, optional, optionalDescr, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_NPG(groups, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_SPG(params, groups, action) if (true) { action; } else 0

#define MOD_CHECK_FAIL_NPGO(groups, optional, optionalDescr, action) if (true) { action; } else 0
#define MOD_CHECK_FAIL_SPGO(params, groups, optional, optionalDescr, action) if (true) { action; } else 0


#define MOD_CHECK_B(cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BP(par, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BG(group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BPG(par, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_CHECK_BO(optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BPO(par, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BGO(group, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BPGO(par, optional, optionalDescr, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_CHECK_BNP(cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BSP(par, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BNPG(group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BSPG(par, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_CHECK_BNPO(optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BSPO(par, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BNPGO(group, optional, optionalDescr, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)
#define MOD_CHECK_BSPGO(par, optional, optionalDescr, group, cond) ModAssert::EvaluateAndReturnBool(cond, MOD_ASSERT_CONTEXT)

#define MOD_CHECK_V(cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VP(par, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VG(group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VPG(par, group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)

#define MOD_CHECK_VO(optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VPO(par, optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VGO(group, optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VPGO(par, optional, optionalDescr, group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)

#define MOD_CHECK_VNP(cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VSP(par, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VNPG(group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VSPG(par, group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)

#define MOD_CHECK_VNPO(optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VSPO(par, optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VNPGO(group, optional, optionalDescr, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)
#define MOD_CHECK_VSPGO(par, optional, optionalDescr, group, cond, action) ModAssert::EvaluateAndReturnValue(cond, action)


#endif // #if MOD_CHECK_REPORTS



#endif // #ifndef MOD_ASSERT_H__QM
