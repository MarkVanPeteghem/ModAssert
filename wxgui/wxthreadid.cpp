//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxthreadid.hpp"
#include "wx/thread.h"

namespace InfoProviders
{
	const wxString& WxThreadIdInfoProvider::GetType() const
	{
		static const wxString type = "threadid";
		return type;
	}

	wxString WxThreadIdInfoProvider::GetInfo() const
	{
		return RichBool::ToString(wxThread::GetCurrentId())+
			(wxIsMainThread() ? " (main thread)" : " (not main thread)");
	}
}














