//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef LOGGER_H__QM
#define LOGGER_H__QM

#include "richbool/portability.hpp"
#include "modassert/infouser.hpp"

namespace ModAssert
{
	class Properties;
	class Result;
	class Filter;

	// abstract base class for objects that log the information about
	// a failed assertion
	class Logger: public InfoProviders::InfoUser
	{
	public:
		virtual ~Logger() {}

		// called when an assertion fails:
		virtual void OnAssert(
			const Properties &properties,
			const Result &result) const = 0;

		virtual void AddMessage(const RichBool::detail::String &msg) const = 0;
		virtual void AddBeginMessage(const Filter *filter) const;
		virtual void AddEndMessage() const;
	};
}

#endif // #ifndef LOGGER_H__QM















