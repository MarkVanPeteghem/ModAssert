//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_TERMINATE_MESSAGE_H__QM
#define MOD_ASSERT_TERMINATE_MESSAGE_H__QM

#include "richbool/portability.hpp"

namespace ModAssert
{
	class Properties;
	class Result;

	// abstract base class for objects that need to perform an action
	// before the application is terminated by ModAssert
	class TerminateMessage
	{
		RichBool::detail::String message;

	public:
		TerminateMessage();
		virtual ~TerminateMessage() {}

		virtual void OnAssert(
			const Properties &properties,
			const Result &assertionResult) const = 0;

		void SetText(const RichBool::detail::String &str)
		{
			message = str;
		}

		const RichBool::detail::String& GetText() const
		{
			return message;
		}
	};
}

#endif // #ifndef MOD_ASSERT_TERMINATE_MESSAGE_H__QM
