//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WIN32_TERMINATE_WARNING_H__QM
#define MOD_ASSERT_WIN32_TERMINATE_WARNING_H__QM

#include "richbool/portability.hpp"
#include "modassert/terminate_message.hpp"

namespace ModAssert
{
	class Win32TerminateMessage: public TerminateMessage
	{
	public:
		virtual void OnAssert(
			const Properties &properties,
			const Result &result) const;
	};
}

#endif //#ifndef MOD_ASSERT_WIN32_TERMINATE_WARNING_H__QM
