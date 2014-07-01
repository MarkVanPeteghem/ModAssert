//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef INFO_STORE_H__QM
#define INFO_STORE_H__QM

namespace InfoProviders
{
	class InfoProvider;
	class InfoUser;
}

namespace ModAssert
{
	class Filter;
	class LogType;
	class Properties;
	class Result;

	class InfoProviderIterator
	{
		size_t idx;
		const LogType *logType;
		const Properties *properties;
		const Result *result;
		const InfoProviders::InfoUser *infoUser;
	public:
		InfoProviderIterator(size_t n);
		InfoProviderIterator(size_t n, const LogType &lt, const InfoProviders::InfoUser &iu);
		InfoProviderIterator(size_t n, const Properties &p, const Result &r, const InfoProviders::InfoUser &iu);

		InfoProviders::InfoProvider& operator*() const;
		InfoProviders::InfoProvider* operator->() const;

		InfoProviderIterator& operator++();
		InfoProviderIterator operator++(int);
		InfoProviderIterator& operator--();
		InfoProviderIterator operator--(int);

		const Filter* GetFilter();

		bool operator==(const InfoProviderIterator &ip) const
		{
			return idx==ip.idx;
		}

		bool operator!=(const InfoProviderIterator &ip) const
		{
			return idx!=ip.idx;
		}

	private:
		bool Accept();
		void SkipForward();
		void SkipBackward();
	};

	// many InfoProvider derived objects can be active at the same time
	void AddInfoProvider(InfoProviders::InfoProvider *infoProvider, const Filter *filter=0);
	void RemoveInfoProvider(InfoProviders::InfoProvider *infoProvider);

	InfoProviderIterator beginInfoProviders(const LogType &lt, const InfoProviders::InfoUser &iu);
	InfoProviderIterator beginInfoProviders(const Properties &p, const Result &r, const InfoProviders::InfoUser &iu);
	InfoProviderIterator endInfoProviders();

	RichBool::detail::String GetAllInfo(const LogType &lt, const InfoProviders::InfoUser &iu,
		const char *sep="\n");
	RichBool::detail::String GetAllInfo(const Properties &p, const Result &r,
		const InfoProviders::InfoUser &iu,
		const char *sep="\n");
}

#endif // #ifndef INFO_STORE_H__QM
