//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/filters.hpp"
#include "modassert/context.hpp"
#include "modassert/logtype.hpp"
#include <stdlib.h>

namespace ModAssert
{
	bool Filter::Accept(const LogType &) const
	{
		return true;
	}

	bool Filter::Accept(const Properties &, const Result &) const
	{
		return true;
	}

	FilterIfFailed filterIfFailed;

	FilterIfAssertion filterIfAssertion;

	FilterIfCheck filterIfCheck;

	FilterMessages filterMessages;

	FilterBadValue filterBadValue;

	FilterNot filterIfSuccess(filterIfFailed),
		filterIfNotAssertion(filterIfAssertion),
		filterIfNotCheck(filterIfCheck),
		filterNoBadValue(filterBadValue);

	FilterLogType filterNoAssertionsAndChecks(false, true, true, true),
		filterOnlyAssertionsAndChecks(true, false, false, false);

	bool FilterInFile::Accept(const Properties &properties,
			const Result &) const
	{
		return strcmp(file, properties.GetContext().file_)==0;
	}

	FilterLogType::FilterLogType(bool showOnAssert, bool showAtBegin, bool showAtEnd, bool showInBetween):
		m_showOnAssert(showOnAssert), m_showAtBegin(showAtBegin),
		m_showAtEnd(showAtEnd), m_showInBetween(showInBetween)
	{
		description  = showOnAssert  ? "assertions, " : "no assertions, ";
		description += showAtBegin   ? "at begin, " : "not at begin, ";
		description += showAtEnd     ? "at end, " : "not at end, ";
		description += showInBetween ? "in between" : "not in between";
	}

	bool FilterLogType::Accept(const LogType &logType) const
	{
		switch (logType.type)
		{
		case LogType::AtBegin:
			return m_showAtBegin;
		case LogType::AtEnd:
			return m_showAtEnd;
		case LogType::InBetween:
			return m_showInBetween;
		default:
			return false;
		}
	}

	bool FilterLogType::Accept(const Properties &,
		const Result &) const
	{
		return m_showOnAssert;
	}
}
