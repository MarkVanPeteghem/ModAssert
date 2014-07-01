//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include <stdio.h>

#include "modassert/consoleterminate.hpp"

namespace ModAssert
{
	void ConsoleTerminateMessage::SetConsoleMessage()
	{
		// Append some text to the text set by the parent class.
		// This is called from the constructors.
		SetText(GetText()+" (press enter)");
	}

	void ConsoleTerminateMessage::OnAssert(
		const Properties &,
		const Result &) const
	{
		*m_os << GetText() << '\n';
#ifdef RICHBOOL_USE_WX
		if (m_is)
		{
			m_is->GetC ();
		}
#else
		if (m_is)
		{
			if (m_is->peek()!=EOF)
				m_is->get();
			m_is->get();
		}
#endif
	}
}
