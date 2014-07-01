//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/wxwarningmessage.hpp"
#include "modassert/result.hpp"
#include <wx/msgdlg.h>

namespace ModAssert
{
	Response WxWarningMessage::OnAssert(
		const Properties &,
		const Result &result,
		bool display) const
	{
		// We use display here, although it can't be changed by the user
		// in the ModAssert info dialog,
		// because if the mode continueWithWarning is chosen,
		// that info dialog will never be shown.
		// But display is still affected by e.g. SetDisplayInFile.

		// We only show this in the main thread, although we could use
		// wxMutexGuiEnter and wxMutexGuiLeave, because wxMutexGuiLeave
		// can take a long time after wxMessageBox.

		if (display && wxIsMainThread())
		{
			wxString msg = GetText();
			if (result.GetParameterList())
				msg += "\n"+RichBool::ToString(*result.GetParameterList());
			wxMessageBox(msg, "ModAssert");
		}
		return (Response)0;
	}
}
