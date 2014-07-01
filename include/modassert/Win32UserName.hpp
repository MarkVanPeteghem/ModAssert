//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifndef WIN32_GET_USER_H__QM
#define WIN32_GET_USER_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class Win32UserNameInfoProvider: public InfoProvider
	{
	public:
		Win32UserNameInfoProvider():
            InfoProvider(InfoProviders::machine)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
	};

	class Win32ImpersonatedUserNameInfoProvider: public InfoProvider
	{
	public:
		Win32ImpersonatedUserNameInfoProvider():
            InfoProvider(InfoProviders::thread)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
	};
}

#endif // #ifndef WIN32_GET_USER_H__QM
