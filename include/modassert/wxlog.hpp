//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WX_LOG_H__QM
#define MOD_ASSERT_WX_LOG_H__QM

#include "modassert/logger.hpp"

namespace ModAssert
{
	class WxLog: public Logger
	{
	public:
		virtual void OnAssert(const Properties &properties,
			const Result &assertionResult) const;

		virtual void AddMessage(const wxString &msg) const;
	};
}

#endif // #ifndef MOD_ASSERT_WX_LOG_H__QM















