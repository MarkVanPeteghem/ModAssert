//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef TIME_INFO_H__QM
#define TIME_INFO_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class TimeInfoProvider: public InfoProvider
	{
	public:
		TimeInfoProvider(): InfoProvider(volatileInfo)
		{}

		virtual ~TimeInfoProvider();

		virtual const RichBool::detail::String& GetType() const;
		virtual RichBool::detail::String GetInfo() const;
		static RichBool::detail::String GetTime();
	};
}

#endif // #ifndef TIME_INFO_H__QM
