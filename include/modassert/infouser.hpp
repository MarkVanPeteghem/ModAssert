//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef INFO_USER_H__QM
#define INFO_USER_H__QM

#include "richbool/portability.hpp"
#include "modassert/info.hpp"

#if defined(RICHBOOL_USE_WX)
	#include <wx/hashmap.h>
#else
	#include <map>
#endif

namespace InfoProviders
{
	enum When { Never, Once, Always };

#ifdef RICHBOOL_USE_WX
	WX_DECLARE_STRING_HASH_MAP(When, StringWhenMap);
#else
	typedef std::map<std::string, When> StringWhenMap;
#endif

	class InfoUser
	{
	public:
		InfoUser();
		virtual ~InfoUser();

		void AddGranularity(Granularity granularity);
		void RemoveGranularity(Granularity granularity);
		bool HasGranularity(Granularity granularity) const;

		void UseInfo(const InfoProvider &ip, When when);

		bool ShouldUseInfo(const InfoProvider &ip, When when) const;

	private:
		unsigned int granularities;

		StringWhenMap useInfo;

		bool BaseShouldUseInfo(const InfoProvider &ip) const;
	};
}

#endif // #ifndef INFO_USER_H__QM
