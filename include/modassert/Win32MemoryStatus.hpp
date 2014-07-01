//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifndef WIN32_MEMORY_STATUS_H__QM
#define WIN32_MEMORY_STATUS_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class Win32TotalMemoryInfoProvider: public InfoProvider
	{
	public:
		Win32TotalMemoryInfoProvider(): InfoProvider(machine)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
	};

	class Win32FreeMemoryInfoProvider: public InfoProvider
	{
	public:
		Win32FreeMemoryInfoProvider(): InfoProvider(volatileInfo)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
	};
}

#endif // #ifndef WIN32_MEMORY_STATUS_H__QM
