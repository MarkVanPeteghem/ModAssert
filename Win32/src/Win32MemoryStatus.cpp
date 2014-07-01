//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32MemoryStatus.hpp"
#include <windows.h>

namespace InfoProviders
{
	/////////////////////////////////////////////////////////////////
	// class Win32TotalMemoryInfoProvider

	const std::string& Win32TotalMemoryInfoProvider::GetType() const
	{
		static const std::string type = "total memory";
		return type;
	}

	std::string Win32TotalMemoryInfoProvider::GetInfo() const
	{
		MEMORYSTATUS stat;
		GlobalMemoryStatus (&stat);

		return "physical "+RichBool::ToString(stat.dwTotalPhys)+
			", paging file "+RichBool::ToString(stat.dwTotalPageFile)+
			", virtual "+RichBool::ToString(stat.dwTotalVirtual);
	}


	/////////////////////////////////////////////////////////////////
	// class Win32FreeMemoryInfoProvider

	const std::string& Win32FreeMemoryInfoProvider::GetType() const
	{
		static const std::string type = "free memory";
		return type;
	}

	std::string Win32FreeMemoryInfoProvider::GetInfo() const
	{
		MEMORYSTATUS stat;
		GlobalMemoryStatus (&stat);

		return "physical "+RichBool::ToString(stat.dwAvailPhys)+
			", paging file "+RichBool::ToString(stat.dwAvailPageFile)+
			", virtual "+RichBool::ToString(stat.dwAvailVirtual);
	}
}
