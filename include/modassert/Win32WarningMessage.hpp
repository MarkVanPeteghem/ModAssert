//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WIN32_WARNING_H__QM
#define MOD_ASSERT_WIN32_WARNING_H__QM

#include "richbool/portability.hpp"
#include "modassert/warning_message.hpp"

namespace ModAssert
{
	class Win32WarningMessage: public WarningMessage
	{
	public:
		virtual Response OnAssert(
			const Properties &properties,
			const Result &result,
			bool display) const;
	};
}

#endif //#ifndef MOD_ASSERT_WIN32_WARNING_H__QM
