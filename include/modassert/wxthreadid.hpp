//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_GET_WX_THREADID_H__QM
#define MOD_ASSERT_GET_WX_THREADID_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class WxThreadIdInfoProvider: public InfoProvider
	{
	public:
		WxThreadIdInfoProvider(): InfoProvider(thread) {}

		virtual const wxString& GetType() const;
		virtual wxString GetInfo() const;
	};
}

#endif // #ifndef MOD_ASSERT_GET_WX_THREADID_H__QM


