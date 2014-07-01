//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WARNING_MESSAGE_H__QM
#define MOD_ASSERT_WARNING_MESSAGE_H__QM

#include "modassert/responder.hpp"

namespace ModAssert
{
	// abstract base class for objects that need to perform an action
	// when an assertion fails and we want to give the user a warning about it
	class WarningMessage: public Responder
	{
		RichBool::detail::String message;

	public:
		WarningMessage();
		virtual ~WarningMessage() {}

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

#endif // #ifndef MOD_ASSERT_WARNING_MESSAGE_H__QM
