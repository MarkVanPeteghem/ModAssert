//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32ProcessId.hpp"
#include <windows.h>

namespace InfoProviders
{
	const std::string& Win32ProcessIdInfoProvider::GetType() const
	{
		static const std::string type = "process id";
		return type;
	}

	std::string Win32ProcessIdInfoProvider::GetInfo() const
	{
		return RichBool::detail::IntToHex(GetCurrentProcessId());
	}
}
