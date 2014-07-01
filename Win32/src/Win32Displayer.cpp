//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include <windows.h>

#include "modassert/Win32Displayer.hpp"
#include "modassert/Win32Dlg.hpp"
#include "modassert/threads.hpp"
#include "modassert/resource.h"

namespace ModAssert
{
	HINSTANCE Win32Displayer::hInstance = 0;

	Win32Displayer::Win32Displayer()
	{}

	Response Win32Displayer::OnAssert(const Properties &properties,
	                                  const Result &result,
	                                  bool display) const
	{
		if (!display)
			return Response(0);

		if (!IsGUIThread())
	#ifndef NDEBUG
			return IsDebuggerPresent() ? BreakIntoDebugger : (Response)0;
	#else
			return (Response)0;
	#endif

		Data data(properties, result, *this);

		int rv = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MOD_ASSERT_DLG),
			GetForegroundWindow(), ModAssertDlg, (LPARAM)&data);

		if (rv<0)
		{
			OutputDebugString("\nAssert dialog could not be created.\n"
				"Did you forget to add the resources of the ModAssert dialog?\n"
				"See the ModAssert documentation for more info\n");
			return BreakIntoDebugger;
		}
		return (Response)rv;
	}
}
