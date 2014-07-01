//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32ComputerName.hpp"
#include <windows.h>

namespace InfoProviders
{
	const std::string& Win32ComputerNameInfoProvider::GetType() const
	{
		static const std::string type = "computer name";
		return type;
	}

	std::string Win32ComputerNameInfoProvider::GetInfo() const
	{
		DWORD len = MAX_COMPUTERNAME_LENGTH+1;
		std::string str(len, ' ');
		GetComputerName(&str[0], &len);
		if (str[len-1]=='\0')
			str.resize(len-1);
		else
			str.resize(len);

		return str;
	}
}
