//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_CONSOLE_DISPLAYER_H__QM
#define MOD_ASSERT_CONSOLE_DISPLAYER_H__QM

#include "modassert/responder.hpp"

namespace ModAssert
{
	class ConsoleDisplayer: public Responder
	{
	public:
		ConsoleDisplayer();
		ConsoleDisplayer(RichBool::detail::InStream *in, RichBool::detail::OutStream *out);
		virtual ~ConsoleDisplayer();

		virtual Response OnAssert(
			const Properties &properties,
			const Result &assertionResult,
			bool display) const;

		void SetGlobalOptionalActionSymbol(char ch);
		char GetGlobalOptionalActionSymbol() const;

		void DisplayChoices(const Properties &properties) const;
		Response AskResponse(const Properties &properties,
			const Result &assertionResult) const;
		void ProcessCharacter(char ch,
			const Properties &properties,
			const Result &assertionResult,
			Response &response,
			bool &wrong) const;

		void SetIsDebugPossible(bool b);

#ifdef RICHBOOL_USE_WX
	public:
		ConsoleDisplayer(wxInputStream *in_stream, wxOutputStream *out_stream);
	protected:
		bool m_ownStreams;
#endif

	protected:
		RichBool::detail::OutStream *out;
		RichBool::detail::InStream *in;

		char globalOptionalActionSymbol;

		bool isDebugPossible;
	};
}

#endif //#ifndef MOD_ASSERT_CONSOLE_DISPLAYER_H__QM
