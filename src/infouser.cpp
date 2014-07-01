//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/infouser.hpp"
#include "modassert/info.hpp"
#include "modassert/logtype.hpp"

#include <algorithm>

namespace InfoProviders
{
    // note: only isMultiThread is set to true,
    //       because most loggers and responders are for meant all threads
	InfoUser::InfoUser(): granularities(0)
	{
		AddGranularity(thread);
	}

	InfoUser::~InfoUser()
	{}

	void InfoUser::UseInfo(const InfoProvider &ip, When when)
	{
		useInfo[ip.GetType()] = when;
	}

	bool InfoUser::ShouldUseInfo(const InfoProvider &ip, When when) const
	{
		StringWhenMap::const_iterator it = useInfo.find(ip.GetType());
		if (it==useInfo.end())
			return (when==Once) || BaseShouldUseInfo(ip);
		else
			return it->second>=when;
	}

	bool InfoUser::BaseShouldUseInfo(const InfoProvider &ip) const
	{
		if (ip.GetGranularity()==volatileInfo)
			return true;
		else
			return HasGranularity(ip.GetGranularity());
	}

	void InfoUser::AddGranularity(Granularity granularity)
	{
		granularities |= 1<<granularity;
	}

	void InfoUser::RemoveGranularity(Granularity granularity)
	{
		granularities &= ~(1<<granularity);
	}

	bool InfoUser::HasGranularity(Granularity granularity) const
	{
		return (granularities&(1<<granularity))!=0;
	}
}
