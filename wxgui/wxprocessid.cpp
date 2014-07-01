//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxprocessid.hpp"
#include <wx/utils.h>

namespace InfoProviders
{
	const wxString& WxProcessIdInfoProvider::GetType() const
	{
		static const wxString type = "process id";
		return type;
	}

	wxString WxProcessIdInfoProvider::GetInfo() const
	{
		return RichBool::detail::IntToHex(wxGetProcessId());
	}
}

