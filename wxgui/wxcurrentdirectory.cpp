//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxcurrentdirectory.hpp"
#include <wx/utils.h>

namespace InfoProviders
{
	const wxString& WxCurrentDirectoryInfoProvider::GetType() const
	{
		static const wxString type = "current directory";
		return type;
	}

	wxString WxCurrentDirectoryInfoProvider::GetInfo() const
	{
		return wxGetCwd();
	}
}
