//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#define MOD_ASSERT_REPORT_FILE 1

#include "modassert/use_bool.hpp"
#include "modassert/response.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/levels.hpp"
#include "modassert/report_type.hpp"
#include "modassert/category.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/assert.hpp"
#include "richbool/analysis.hpp"

namespace ModAssert
{
	Response HandleAssert(
		const Properties &properties,
		const Result &result,
		bool *displayThis);

	extern Category<Assertions> categoryAsserts;


	///////////////////////////////////////////////////////
	// class UseBool

#ifdef NDEBUG
	bool UseBool::check = false;
#else
	bool UseBool::check = true;
#endif

	UseBool::UseBool(bool b, const Context &context): m_context(context)
	{
		bits = (unsigned char)((b ? value : 0) | owned);
	}

	UseBool::UseBool(const UseBool &ub): m_context(ub.m_context)
	{
		bits = ub.bits;
		ub.bits &= ~owned;
	}

	UseBool::~UseBool()
	{
		if ( check && isOwned() && !isUsed() )
		{
			// Note: we can't use the MOD_ASSERT_P macro here,
			// because we want to preserve the context (file+linenr).

			ParameterList parmList("condition");
			parmList << getValue();

			Category<Assertions> category;

			TemplateGroupListWithLevel<Level<detail::L_<2> > > gl(Error);
			Properties properties(&category, m_context,
				"unused UseBool", gl, NULL);
			Result result(false, NULL, &parmList);

			Response response = HandleAssert(properties,
				result, NULL);

			if (response&BreakIntoDebugger)
			{ MOD_ASSERT_BREAK_HERE; }
			HandleResponse(response, properties, result);
		}
	}

	UseBool::operator bool() const
	{
		bits |= used;
		return (bits & value) != 0;
	}

	void UseBool::SetCheck(bool b)
	{
		check = b;
	}
}
