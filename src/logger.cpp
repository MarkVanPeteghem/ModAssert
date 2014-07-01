//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/logger.hpp"
#include "modassert/handler.hpp"
#include "modassert/infostore.hpp"
#include "modassert/filters.hpp"
#include "modassert/logtype.hpp"

namespace ModAssert
{
	static const LogType logAtBegin(LogType::AtBegin), logAtEnd(LogType::AtEnd);

	void Logger::AddBeginMessage(const Filter *filter) const
	{
		AddMessage("************************************************************");
		AddMessage("ModAssert starts logging here");
		if (filter)
			AddMessage("using the filter "+filter->GetDescription());

		for (InfoProviderIterator it=beginInfoProviders(logAtBegin, *this); it!=endInfoProviders(); ++it)
		{
			AddMessage(it->GetType()+": "+it->GetInfo());
		}

		// add newline:
		AddMessage("");
	}

	void Logger::AddEndMessage() const
	{
		AddMessage("ModAssert stops logging here");
		for (InfoProviderIterator it=beginInfoProviders(logAtEnd, *this); it!=endInfoProviders(); ++it)
		{
			AddMessage(it->GetType()+": "+it->GetInfo());
		}
		AddMessage("------------------------------------------------------------");
	}
}
