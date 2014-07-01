//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RESPONDER_H__QM
#define RESPONDER_H__QM

#include "modassert/response.hpp"
#include "modassert/infouser.hpp"

namespace ModAssert
{
	class Properties;
	class Result;
	class ResponderData;

	// abstract base class for objects that inform the user about
	// a failed assertion, e.g. a dialog box, and ask the user what
	// action should be taken, or objects that decide
	// on their own what to do based on the arguments
	class Responder: public InfoProviders::InfoUser
	{
		ResponderData *m_ResponderData;
	public:
		Responder()
			: m_ResponderData(0)
		{}
		virtual ~Responder() {}

		virtual Response OnAssert(
			const Properties &properties,
			const Result &assertionResult,
			bool display) const = 0;
	};
}

#endif // #ifndef RESPONDER_H__QM















