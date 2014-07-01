//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxfreememory.hpp"
#include <wx/utils.h>

namespace InfoProviders
{
	const wxString& WxFreeMemoryInfoProvider::GetType() const
	{
		static const wxString type = "free memory";
		return type;
	}

	bool WxFreeMemoryInfoProvider::HasInfo() const
	{
		return wxGetFreeMemory()>=0;
	}

	wxString WxFreeMemoryInfoProvider::GetInfo() const
	{
		return RichBool::ToString(wxGetFreeMemory())+" bytes";
	}
}
