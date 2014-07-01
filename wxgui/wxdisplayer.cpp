//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxdisplayer.hpp"
#include "modassert/wxdlg.hpp"
#include <wx/thread.h>

namespace ModAssert
{
	Response WxDisplayer::OnAssert(const Properties &properties,
	                               const Result &assertionResult,
								   bool display) const
	{
		if (!display)
			return Response(0);

		if (!wxIsMainThread())
		{
#ifndef NDEBUG
			return wxIsDebuggerRunning() ? BreakIntoDebugger : Response(0);
#else
			return Response(0);
#endif
		}

		WxDlg dlg(properties, assertionResult, *this);

		int rv = dlg.ShowModal();
		return (Response)rv;
	}
}
