//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32TerminateMessage.hpp"
#include "modassert/Win32Displayer.hpp"
#include "modassert/threads.hpp"
#include "modassert/result.hpp"

#include <windows.h>

namespace ModAssert
{
	void Win32TerminateMessage::OnAssert(
		const Properties &,
		const Result &result) const
	{
		if (IsGUIThread())
		{
			std::string msg = GetText();
			if (result.GetParameterList())
				msg += "\n"+RichBool::ToString(*result.GetParameterList());
			MessageBox(GetForegroundWindow(),
				msg.c_str(),
				"ModAssert",
				MB_OK);
		}
	}
}
