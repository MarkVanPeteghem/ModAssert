//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxlog.hpp"
#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/categorybase.hpp"
#include "wx/log.h"
#include "richbool/analysis.hpp"

namespace ModAssert
{
	void WxLog::OnAssert(const Properties &properties,
			const Result &assertionResult) const
	{
		const GroupList *groupList = properties.GetGroupList();

		wxString groups;
		for (size_t idx=0; idx<groupList->GetSize(); ++idx)
		{
			if (idx!=0)
				groups += ", ";
			groups += groupList->GetName(idx);
		}

		const ParameterList *parList = assertionResult.GetParameterList();
		const bool hasValues = (parList!=NULL) && (parList->GetFirst()!=NULL);
		
		wxString info = GetAllInfo(properties, assertionResult, *this, "\n  ");

		RichBool::SharedAnalysis analysis = assertionResult.GetAnalysis();

		const char *condition = properties.GetCondition();

		// start with newline, so that the context is shown on a new line
		// and double clicking it in an IDE brings up the line in the source code
		wxLogDebug(
			"\n%s\n"
			"%s%s%s\n"
			"analysis: %s\n"
			"parameters:\n%s"
			"%s: %s\n"
			"%s%s",
			
			RichBool::ToString(properties.GetContext()).c_str(),
			properties.GetCategory()->GetName(),
			condition ? (assertionResult.Succeeded() ? " succeeded: " : " failed: ") : " failed unconditionally",
			condition ? condition : "",
			analysis  ? RichBool::ToString(*analysis).c_str() : "no analysis",
			hasValues ? RichBool::ToString(*parList).c_str() : "  no parameters\n",
			groupList->GetSize()==0 ? "no groups" : "groups",
			groups.c_str(),
			RichBool::detail::is_empty(info) ? "" : "info:\n",
			RichBool::detail::is_empty(info) ? "" : ("  "+info+"\n").c_str()
		);
	}

	void WxLog::AddMessage(const wxString &msg) const
	{
		wxLogDebug(msg);
	}
}






















