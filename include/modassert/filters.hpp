//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef FILTERS_H__QM
#define FILTERS_H__QM

#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/categorybase.hpp"

namespace ModAssert
{
	class LogType;

	// abstract base class
	class Filter
	{
	protected:
		// to be filled in in derived classes:
		RichBool::detail::String description;
	public:
		virtual ~Filter() {}

		virtual bool Accept(const LogType &logType) const;
		virtual bool Accept(const Properties &properties,
			const Result &result) const;

		const RichBool::detail::String& GetDescription() const
		{
			return description;
		}
	};

	// derived classes
	class FilterIfFailed: public Filter
	{
	public:
		FilterIfFailed()
		{
			description = "failed";
		}

		virtual bool Accept(const Properties &,
			const Result &result) const
		{
			return !result.Succeeded();
		}
	};

	extern FilterIfFailed filterIfFailed;


	class FilterIfAssertion: public Filter
	{
	public:
		FilterIfAssertion()
		{
			description = "assertion";
		}

		virtual bool Accept(const Properties &properties,
			const Result &) const
		{
			return properties.GetCategory()->IsAssertion();
		}
	};

	extern FilterIfAssertion filterIfAssertion;


	class FilterIfCheck: public Filter
	{
	public:
		FilterIfCheck()
		{
			description = "check";
		}

		virtual bool Accept(const Properties &properties,
			const Result &) const
		{
			return properties.GetCategory()->IsCheck();
		}
	};

	extern FilterIfCheck filterIfCheck;


	class FilterIfHasGroup: public Filter
	{
		const char *name;
	public:
		FilterIfHasGroup(const char *name_): name(name_)
		{
			description = "has ";
			description += name;
		}
		virtual bool Accept(const Properties &properties,
			const Result &) const
		{
			return properties.GetGroupList() &&
				properties.GetGroupList()->Has(name);
		}
	};

	class FilterByLevel: public Filter
	{
		int level;
		const char* comparison;
	public:
		FilterByLevel(const char* comparison_): level(0), comparison(comparison_)
		{}

		int GetLevel() const
		{
			return level;
		}

		void SetLevel(int level_)
		{
			level = level_;
			description = "level ";
			description += comparison;
			description += " "+RichBool::ToString(level);
		}
	};

	class FilterMinimumLevel: public FilterByLevel
	{
	public:
		FilterMinimumLevel(int level_): FilterByLevel(">=")
		{
			SetLevel(level_);
		}

		template<class Level_>
		FilterMinimumLevel(Level_): FilterByLevel(">=")
		{
			SetLevel(Level_::level);
		}

		virtual bool Accept(const Properties &properties,
			const Result &) const
		{
			return properties.GetGroupList() &&
				properties.GetGroupList()->GetLevel()>=GetLevel();
		}
	};

	class FilterMaximumLevel: public FilterByLevel
	{
	public:
		FilterMaximumLevel(int level_): FilterByLevel("<=")
		{
			SetLevel(level_);
		}

		template<class Level_>
		FilterMaximumLevel(Level_): FilterByLevel("<=")
		{
			SetLevel(Level_::level);
		}

		virtual bool Accept(const Properties &properties,
			const Result &) const
		{
			return properties.GetGroupList() &&
				properties.GetGroupList()->GetLevel()<=GetLevel();
		}
	};

	class FilterInFile: public Filter
	{
		const char *file;
	public:
		FilterInFile(const char *file_): file(file_)
		{
			description = "in file ";
			description += file;
		}

		virtual bool Accept(const Properties &properties,
			const Result &result) const;
	};

	class FilterMessages: public Filter
	{
	public:
		FilterMessages()
		{
			description = "messages";
		}

		// messages never come through OnAssert,
		// so it suffices to let OnAssert return false
		virtual bool Accept(const Properties &,
			const Result &) const
		{
			return false;
		}
	};

	extern FilterMessages filterMessages;

	class FilterBadValue: public Filter
	{
	public:
		FilterBadValue()
		{
			description = "bad value";
		}

		virtual bool Accept(const Properties &,
			const Result &res) const
		{
			return res.GetAnalysis() &&
				(res.GetAnalysis()->GetState()==RichBool::Analysis::BadValue);
		}
	};

	extern FilterBadValue filterBadValue;

	class FilterNot: public Filter
	{
		const Filter &filter;

		FilterNot& operator=(const FilterNot&) { return *this; }
	public:
		FilterNot(const Filter &filter_): filter(filter_)
		{
			description = "not ("+filter.GetDescription()+')';
		}

		virtual bool Accept(const Properties &properties,
			const Result &result) const
		{
			return !filter.Accept(properties, result);
		}
	};

	class FilterAnd: public Filter
	{
		const Filter &filter1, &filter2;

		FilterAnd& operator=(const FilterAnd&) { return *this; }
	public:
		FilterAnd(const Filter &filter1_, const Filter &filter2_):
			filter1(filter1_), filter2(filter2_)
		{
			description = '('+filter1.GetDescription()+" and "+
				filter2.GetDescription()+')';
		}

		virtual bool Accept(const Properties &properties,
			const Result &result) const
		{
			return filter1.Accept(properties, result)
				&& filter2.Accept(properties, result);
		}
	};

	class FilterOr: public Filter
	{
		const Filter &filter1, &filter2;

		FilterOr& operator=(const FilterOr&) { return *this; }
	public:
		FilterOr(const Filter &filter1_, const Filter &filter2_):
			filter1(filter1_), filter2(filter2_)
		{
			description = '('+filter1.GetDescription()+" or "+
				filter2.GetDescription()+')';
		}

		virtual bool Accept(const Properties &properties,
			const Result &result) const
		{
			return filter1.Accept(properties, result)
				|| filter2.Accept(properties, result);
		}
	};

	class FilterLogType: public Filter
	{
		bool m_showOnAssert, m_showAtBegin, m_showAtEnd, m_showInBetween;
	public:
		FilterLogType(bool showOnAssert, bool showAtBegin, bool showAtEnd, bool showInBetween);

		virtual bool Accept(const LogType &logType) const;
		virtual bool Accept(const Properties &properties,
			const Result &result) const;
	};

	extern FilterLogType filterNoAssertionsAndChecks, filterOnlyAssertionsAndChecks;

	extern FilterNot filterIfSuccess, filterIfNotAssertion, filterIfNotCheck,
		filterNoBadValue;
}

#endif // #ifndef FILTERS_H__QM
