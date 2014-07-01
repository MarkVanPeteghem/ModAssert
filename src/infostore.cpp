//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/infouser.hpp"
#include "modassert/threads.hpp"
#include "modassert/filters.hpp"
#include "modassert/logtype.hpp"

#if defined(RICHBOOL_USE_WX)
	#include "wx/dynarray.h"
#else
	#include <vector>
	#include <algorithm>
#endif

namespace ModAssert
{
#if defined(RICHBOOL_USE_WX)

	WX_DEFINE_ARRAY_PTR(InfoProviders::InfoProvider*, InfoProviderArray);
	WX_DEFINE_ARRAY_PTR(const Filter*, FilterArray);

	InfoProviderArray infoProviders;
	FilterArray filters;

	void AddInfoProvider(InfoProviders::InfoProvider *infoProvider, const Filter *filter)
	{
		ScopedLock lock;

		infoProviders.Add(infoProvider);
		filters.Add(filter);

	}
	void RemoveInfoProvider(InfoProviders::InfoProvider *infoProvider)
	{
		ScopedLock lock;

		int idx = infoProviders.Index(infoProvider);
		if (idx!=wxNOT_FOUND)
		{
			infoProviders.RemoveAt(idx);
			filters.RemoveAt(idx);
		}
	}
	#define NR_INFO_PROVIDERS infoProviders.GetCount()

#else

	typedef std::vector<InfoProviders::InfoProvider*> InfoProviderArray;
	InfoProviderArray infoProviders;

	typedef std::vector<const Filter*> FilterArray;
	FilterArray filters;

	void AddInfoProvider(InfoProviders::InfoProvider *infoProvider, const Filter *filter)
	{
		ScopedLock lock;

		infoProviders.push_back(infoProvider);
		filters.push_back(filter);
	}
	void RemoveInfoProvider(InfoProviders::InfoProvider *infoProvider)
	{
		ScopedLock lock;

		std::vector<InfoProviders::InfoProvider*>::iterator it =
			std::find(infoProviders.begin(), infoProviders.end(), infoProvider);
		if (it!=infoProviders.end())
		{
			size_t idx = it-infoProviders.begin();
			infoProviders.erase(it);
			filters.erase(filters.begin()+idx);
		}
	}
	#define NR_INFO_PROVIDERS infoProviders.size()

#endif

	bool InfoProviderIterator::Accept()
	{
		if (!infoProviders[idx]->HasInfo())
			return false;

		if (logType)
		{
			InfoProviders::When when =
				logType->type==LogType::AtBegin ? InfoProviders::Once : InfoProviders::Always;
			if (infoUser && !infoUser->ShouldUseInfo(*infoProviders[idx], when))
				return false;
			return !filters[idx] || filters[idx]->Accept(*logType);
		}
		else if (properties)
		{
			if (infoUser && !infoUser->ShouldUseInfo(*infoProviders[idx], InfoProviders::Always))
				return false;
			return !filters[idx] || filters[idx]->Accept(*properties, *result);
		}
		else
			return true;
	}

	void InfoProviderIterator::SkipForward()
	{
		while ( (idx<NR_INFO_PROVIDERS) && !Accept() )
			++idx;
	}

	void InfoProviderIterator::SkipBackward()
	{
		while ( (idx<NR_INFO_PROVIDERS) && !Accept() )
			--idx;
	}

	InfoProviderIterator::InfoProviderIterator(size_t n):
		idx(n)
	{}

	InfoProviderIterator::InfoProviderIterator(size_t n, const LogType &lt, const InfoProviders::InfoUser &iu):
		idx(n), logType(&lt), properties(0), result(0), infoUser(&iu)
	{
		SkipForward();
	}

	InfoProviderIterator::InfoProviderIterator(size_t n,
			const Properties &p,
			const Result &r,
			const InfoProviders::InfoUser &iu):
		idx(n), logType(0), properties(&p), result(&r), infoUser(&iu)
	{
		SkipForward();
	}

	InfoProviders::InfoProvider& InfoProviderIterator::operator*() const
	{
		return *infoProviders[idx];
	}

	InfoProviders::InfoProvider* InfoProviderIterator::operator->() const
	{
		return infoProviders[idx];
	}

	InfoProviderIterator& InfoProviderIterator::operator++()
	{
		++idx;
		SkipForward();
		return *this;
	}

	InfoProviderIterator InfoProviderIterator::operator++(int)
	{
		InfoProviderIterator i(*this);
		++idx;
		SkipForward();
		return i;
	}

	InfoProviderIterator& InfoProviderIterator::operator--()
	{
		--idx;
		SkipBackward();
		return *this;
	}

	InfoProviderIterator InfoProviderIterator::operator--(int)
	{
		InfoProviderIterator i(*this);
		--idx;
		SkipBackward();
		return i;
	}

	const Filter* InfoProviderIterator::GetFilter()
	{
		return filters[idx];
	}

	InfoProviderIterator beginInfoProviders(const LogType &lt, const InfoProviders::InfoUser &iu)
	{
		return InfoProviderIterator(0, lt, iu);
	}

	InfoProviderIterator beginInfoProviders(const Properties &p, const Result &r, const InfoProviders::InfoUser &iu)
	{
		return InfoProviderIterator(0, p, r, iu);
	}

	InfoProviderIterator endInfoProviders()
	{
		return InfoProviderIterator(NR_INFO_PROVIDERS);
	}

	static RichBool::detail::String GetAllInfo(InfoProviderIterator begin, InfoProviderIterator end,
		const char *sep/*="\n"*/)
	{
		RichBool::detail::String allInfo;
		bool first = true;
		for (InfoProviderIterator it=begin; it!=end; ++it)
		{
			if (!first)
				allInfo += sep;
			else
				first = false;

			allInfo += it->GetType()+": "+it->GetInfo();
		}
		return allInfo;
	}

	RichBool::detail::String GetAllInfo(const LogType &lt, const InfoProviders::InfoUser &iu,
		const char *sep/*="\n"*/)
	{
		return GetAllInfo(beginInfoProviders(lt, iu), endInfoProviders(), sep);
	}

	RichBool::detail::String GetAllInfo(const Properties &p, const Result &r,
		const InfoProviders::InfoUser &iu,
		const char *sep/*="\n"*/)
	{
		return GetAllInfo(beginInfoProviders(p, r, iu), endInfoProviders(), sep);
	}
}
