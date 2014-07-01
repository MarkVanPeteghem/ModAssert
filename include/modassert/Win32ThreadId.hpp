//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_GET_WIN32_THREADID_H__QM
#define MOD_ASSERT_GET_WIN32_THREADID_H__QM

#include "modassert/info.hpp"
#include "windows.h"

namespace InfoProviders
{
	class Win32ThreadIdInfoProvider: public InfoProvider
	{
	public:
		Win32ThreadIdInfoProvider():
            InfoProvider(thread)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;

		static void SetMainThreadId(DWORD id);
	};
}

#endif // #ifndef MOD_ASSERT_GET_WIN32_THREADID_H__QM
