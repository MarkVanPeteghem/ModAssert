//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32UserName.hpp"
#include <windows.h>
#include <lmcons.h>

namespace InfoProviders
{
	std::string GetUserName()
	{
		DWORD len = UNLEN+1;
		std::string str(len, ' ');
		::GetUserName(&str[0], &len);
		if (str[len-1]=='\0')
			str.resize(len-1);
		else
			str.resize(len);

		return str;
	}

	/////////////////////////////////////////////////////////////////
	// class Win32UserNameInfoProvider

	const std::string& Win32UserNameInfoProvider::GetType() const
	{
		static const std::string type = "user";
		return type;
	}

	std::string Win32UserNameInfoProvider::GetInfo() const
	{
		return GetUserName();
	}


	/////////////////////////////////////////////////////////////////
	// class Win32ImpersonatedUserNameInfoProvider

	const std::string& Win32ImpersonatedUserNameInfoProvider::GetType() const
	{
		static const std::string type = "impersonated user";
		return type;
	}

	std::string Win32ImpersonatedUserNameInfoProvider::GetInfo() const
	{
		return GetUserName();
	}
}
