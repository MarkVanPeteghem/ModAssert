//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "windows.h"
#include "modassert/Win32Trace.hpp"
#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/categorybase.hpp"
#include "richbool/analysis.hpp"

namespace ModAssert
{
	void Win32Trace::OnAssert(const Properties &properties,
	                          const Result &result) const
	{
		OutputDebugString(RichBool::ToString(properties.GetContext()).c_str());
		OutputDebugString("\n");

		if (properties.GetCondition())
		{
			OutputDebugString(properties.GetCategory()->GetName());
			OutputDebugString(" ");
			OutputDebugString(properties.GetCondition());
			OutputDebugString(result.Succeeded() ? " succeeded\n" : " failed\n");
		}
		else
			OutputDebugString("unconditional failure\n");

		OutputDebugString("analysis: ");
		OutputDebugString(result.GetAnalysis() ?
			RichBool::ToString(*result.GetAnalysis()).c_str() : "no analysis");
		OutputDebugString("\n");

		if (result.GetParameterList())
		{
			OutputDebugString("parameters:\n");
			OutputDebugString(RichBool::ToString(*result.GetParameterList()).c_str());
		}

		OutputDebugString("extra info:\n");
		for (InfoProviderIterator it=beginInfoProviders(properties, result, *this); it!=endInfoProviders(); ++it)
		{
			OutputDebugString("  ");
			OutputDebugString(it->GetType().c_str());
			OutputDebugString(": ");
			OutputDebugString(it->GetInfo().c_str());
			OutputDebugString("\n");
		}

		OutputDebugString("group list:\n");
		for (size_t idx=0; idx<properties.GetGroupList()->GetSize(); ++idx)
		{
			OutputDebugString("  ");
			OutputDebugString(properties.GetGroupList()->GetName(idx).c_str());
			OutputDebugString("\n");
		}

		OutputDebugString("\n");
	}

	void Win32Trace::AddMessage(const std::string &msg) const
	{
		OutputDebugString(msg.c_str());
		OutputDebugString("\n");
	}
}
