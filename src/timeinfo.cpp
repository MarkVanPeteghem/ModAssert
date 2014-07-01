//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#if defined(RICHBOOL_USE_WX)
	#include "wx/datetime.h"
#else
#define _CRT_SECURE_NO_DEPRECATE
	#include <ctime>
#endif

#include "modassert/timeinfo.hpp"

namespace InfoProviders
{
	TimeInfoProvider::~TimeInfoProvider()
	{}

	const RichBool::detail::String& TimeInfoProvider::GetType() const
	{
		static const RichBool::detail::String type = "time";
		return type;
	}

	RichBool::detail::String TimeInfoProvider::GetTime()
	{
#if defined(RICHBOOL_USE_WX)
		wxDateTime now = wxDateTime::Now();
		return now.FormatISODate()+' '+now.FormatISOTime();
#else
		time_t ltime;

		time(&ltime);
		std::string str = ctime(&ltime);
		if (str[str.size()-1]=='\n')
			str.erase(str.size()-1);
		return str;
#endif
	}

	RichBool::detail::String TimeInfoProvider::GetInfo() const
	{
		return GetTime();
	}
}
