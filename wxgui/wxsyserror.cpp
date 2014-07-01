//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxsyserror.hpp"
#include <wx/log.h>

static int s_sysError = 0;

namespace InfoProviders
{
	const wxString& WxSysErrorInfoProvider::GetType() const
	{
		static const wxString type = "syserror";
		return type;
	}

	bool WxSysErrorInfoProvider::HasInfo() const
	{
		return s_sysError!=0;
	}

	wxString WxSysErrorInfoProvider::GetInfo() const
	{
		return RichBool::ToString(s_sysError)+" ("+wxSysErrorMsg(s_sysError)+")";
	}
}

namespace ModAssert
{
	void WxSysErrorHook::OnAssert(
				const Properties &,
	            const Result &) const
	{
		// This needs to be stored by the hook, before we log to a file
		// or display the dialog box, because these actions may reset it to 0.
		// Note that this makes it not threadsafe: it is possible that another
		// thread gives a new value after the failure and before we store it
		// here. But the only consequence is misleading information.
		s_sysError = wxSysErrorCode();
	}
}
