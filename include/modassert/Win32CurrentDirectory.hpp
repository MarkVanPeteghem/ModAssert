//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MODASSERT_WIN32_CURRENT_DIRECTORY_H__QM
#define MODASSERT_WIN32_CURRENT_DIRECTORY_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class Win32CurrentDirectoryInfoProvider: public InfoProvider
	{
	public:
		Win32CurrentDirectoryInfoProvider():
            InfoProvider(volatileInfo)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
	};
}

#endif // #ifndef MODASSERT_WIN32_CURRENT_DIRECTORY_H__QM
