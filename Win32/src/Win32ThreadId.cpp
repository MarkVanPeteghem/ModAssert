//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32ThreadId.hpp"
#include "modassert/Win32Displayer.hpp"

namespace InfoProviders
{
	static DWORD mainThreadId = 0;

	const std::string& Win32ThreadIdInfoProvider::GetType() const
	{
		static const std::string type = "threadid";
		return type;
	}

	std::string Win32ThreadIdInfoProvider::GetInfo() const
	{
		DWORD id = GetCurrentThreadId();
		return RichBool::ToString(id)+
			(id==mainThreadId ? " (main thread)" : " (not main thread)");
	}

	void Win32ThreadIdInfoProvider::SetMainThreadId(DWORD id)
	{
		mainThreadId = id;
	}
}
