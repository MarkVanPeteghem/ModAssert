//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32LastError.hpp"
#include "windows.h"

static DWORD s_lastError=0;

namespace InfoProviders
{
	const std::string& LastErrorInfoProvider::GetType() const
	{
		static const std::string type = "GetLastError()";
		return type;
	}

	std::string LastErrorInfoProvider::GetInfo() const
	{
		// If last error was 0, it is not interesting to show this information,
		// so we return an empty string. Most objects that process the info
		// of InfoProvider derived objects, won't show anything if an empty
		// string is returned, not even the type of the information.
		if (s_lastError==0)
			return "";

		// Show return value of GetLastError and the corresponding string.
		// We use the value that was stored by the hook
		std::string str = RichBool::ToString(s_lastError)+" (";

		LPTSTR buffer=0;
		DWORD len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			s_lastError,
			0,
			(LPTSTR)&buffer,
			0,
			NULL);
		if(len != 0)
		{
			if ( (buffer[len-1]=='\n') && (buffer[len-2]=='\r') )
				buffer[len-2] = '\0';
			str += buffer;
			LocalFree(buffer);
		}
		else
		{
			str += "?";
		}
		str += ')';
		return str;
	}

	bool LastErrorInfoProvider::HasInfo() const
	{
		return s_lastError!=0;
	}
}

namespace ModAssert
{
	void LastErrorHook::OnAssert(
				const Properties &,
	            const Result &) const
	{
		// This needs to be stored by the hook, before we log to a file
		// or display the dialog box, because these actions may reset it to 0.
		// Note that this makes it not threadsafe: it is possible that another
		// thread gives a new value after the failure and before we store it
		// here. But the only consequence is misleading information.
		s_lastError = GetLastError();
	}
}
