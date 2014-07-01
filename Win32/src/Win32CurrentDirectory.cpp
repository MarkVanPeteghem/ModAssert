//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32CurrentDirectory.hpp"
#include <windows.h>

namespace InfoProviders
{
	const std::string& Win32CurrentDirectoryInfoProvider::GetType() const
	{
		static const std::string type = "current directory";
		return type;
	}

	std::string Win32CurrentDirectoryInfoProvider::GetInfo() const
	{
		std::string str=" ";
		DWORD len = GetCurrentDirectory(1, &str[0]);
		str.resize(len);
		GetCurrentDirectory(len, &str[0]);
		if (str[len-1]=='\0')
			str.resize(len-1);

		return str;
	}
}
