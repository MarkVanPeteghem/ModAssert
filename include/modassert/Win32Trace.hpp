//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WIN32_TRACE_H__QM
#define MOD_ASSERT_WIN32_TRACE_H__QM

#include "modassert/logger.hpp"

namespace ModAssert
{
	class Win32Trace: public Logger
	{
	public:
		virtual void OnAssert(
			const Properties &properties,
	        const Result &result) const;

		virtual void AddMessage(const std::string &msg) const;
	};
}

#endif // #ifndef MOD_ASSERT_WIN32_TRACE_H__QM














