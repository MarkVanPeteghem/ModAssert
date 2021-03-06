//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MODASSERT_WX_GET_OS_VERSION_H__QM
#define MODASSERT_WX_GET_OS_VERSION_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class WxOsVersionInfoProvider: public InfoProvider
	{
	public:
		WxOsVersionInfoProvider(): InfoProvider(machine)
		{}

		virtual const wxString& GetType() const;
		virtual wxString GetInfo() const;
	};
}

#endif // #ifndef MODASSERT_WX_GET_OS_VERSION_H__QM
