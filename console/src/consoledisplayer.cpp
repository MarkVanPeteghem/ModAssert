//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#include "modassert/consoledisplayer.hpp"
#include "modassert/logger.hpp"
#include "modassert/grouplst.hpp"
#include "modassert/properties.hpp"
#include "modassert/handler.hpp"
#include "modassert/filters.hpp"
#include <stdlib.h>

namespace ModAssert
{
#ifdef RICHBOOL_USE_WX
	ConsoleDisplayer::ConsoleDisplayer():
		m_ownStreams(false), out(NULL), in(NULL), globalOptionalActionSymbol('G'),
		isDebugPossible(IsDebugPossible())
	{}
	ConsoleDisplayer::ConsoleDisplayer(wxTextInputStream *in_, wxTextOutputStream *out_):
		m_ownStreams(false), out(out_), in(in_), globalOptionalActionSymbol('G'),
		isDebugPossible(IsDebugPossible())
	{}

	ConsoleDisplayer::ConsoleDisplayer(wxInputStream *in_stream, wxOutputStream *out_stream):
		m_ownStreams(true),
		out(new wxTextOutputStream(*out_stream)),
		in(new wxTextInputStream(*in_stream)),
		globalOptionalActionSymbol('G'),
		isDebugPossible(IsDebugPossible())
	{}
#else
	ConsoleDisplayer::ConsoleDisplayer():
		out(NULL), in(NULL), globalOptionalActionSymbol('G'),
		isDebugPossible(IsDebugPossible())
	{}
	ConsoleDisplayer::ConsoleDisplayer(RichBool::detail::InStream *in_, RichBool::detail::OutStream *out_):
		out(out_), in(in_), globalOptionalActionSymbol('G'),
		isDebugPossible(IsDebugPossible())
	{}
#endif

	ConsoleDisplayer::~ConsoleDisplayer()
	{
#ifdef RICHBOOL_USE_WX
		if (m_ownStreams)
		{
			delete in;
			delete out;
		}
#endif
	}

	static void ShowOption(RichBool::detail::OutStream &out,
		const RichBool::detail::String &option, int &nr)
	{
		out << option;
		for (size_t idx=RichBool::detail::str_size(option); idx<34; ++idx)
			out << ' ';
		out << ' ';
		++nr;
		if (nr%2==0)
		{
			RichBool::detail::Endl(out);
		}
	}

	Response ConsoleDisplayer::OnAssert(
			const Properties &properties,
			const Result &result,
			bool display) const
	{
		// by now, the logger (if there is one) has outputted the data
		// of context, condition, analysis, parList and level,
		// so we only have to ask for the response

		if (!display)
			return Response(0);

		DisplayChoices(properties);
		return AskResponse(properties, result);
	}

	void ConsoleDisplayer::DisplayChoices(const Properties &properties) const
	{
		int nrOption = 0;
		RichBool::detail::Endl(*out);

		ShowOption(*out, "I: Ignore", nrOption);

		if (GetAllowBreakIntoDebugger() && isDebugPossible)
			ShowOption(*out, "D: Debug", nrOption);
		if (GetOptionalLogger())
			ShowOption(*out,
				RichBool::detail::String("L: ")+(GetOptionalLoggerText() ? GetOptionalLoggerText() : "Optional logger"),
				nrOption);

		if (properties.GetOptional() && GetAllowOptional())
			ShowOption(*out,
				RichBool::detail::String("O: Optional action ")+properties.GetOptional(), nrOption);

		if (GetGlobalOptionalAction() && GetAllowGlobalOptional())
		{
			RichBool::detail::String str;
			str += globalOptionalActionSymbol;
			str += ": ";
			str += GetGlobalOptionalActionDescription();
			ShowOption(*out, str, nrOption);
		}

		if (properties.CanStopDisplayingThis())
			ShowOption(*out, "S: Stop displaying this", nrOption);
		ShowOption(*out, "F: Stop displaying this file", nrOption);
		ShowOption(*out, "A: Stop displaying all", nrOption);

		for (size_t idx=0; idx<properties.GetGroupList()->GetSize(); ++idx)
		{
			ShowOption(*out,
				RichBool::ToString(idx+1)+": Stop displaying "+properties.GetGroupList()->GetName(idx),
				nrOption);
		}

		if (GetAllowExit())
			ShowOption(*out, "X: Exit", nrOption);

		RichBool::detail::Endl(*out);
		if (nrOption%2!=0)
			RichBool::detail::Endl(*out);
	}

	void ConsoleDisplayer::ProcessCharacter(char ch,
		const Properties &properties,
		const Result &result,
		Response &response,
		bool &wrongCharacter) const
	{
		wrongCharacter = false;

		if ( isdigit(ch) && (ch!='0') )
		{
			unsigned char num = (unsigned char)(ch-'1');
			if ( (num < properties.GetGroupList()->GetSize()) &&
				(num < maxNrCustomResponses) )
				response = StopDisplayingCustom1 << num;
			else
				wrongCharacter = true;
		}
		else if (toupper(ch)==globalOptionalActionSymbol)
		{
			if (GetAllowGlobalOptional() && GetGlobalOptionalAction())
				response = GlobalOptional;
			else
				wrongCharacter = true;
		}
		else
		{
			switch (toupper(ch))
			{
			case 'I': break; // do nothing
			case 'S': response = StopDisplayingThis; break;
			case 'F': response = StopDisplayingFile; break;
			case 'A': response = StopDisplayingAll; break;
			case 'X':
				if (GetAllowExit())
					response = Exit;
				else
					wrongCharacter = true;
				break;
			case 'O':
				if (properties.GetOptional() && GetAllowOptional())
					response = Optional;
				else
					wrongCharacter = true;
				break;
			case 'D':
				if (GetAllowBreakIntoDebugger() && isDebugPossible)
					response = BreakIntoDebugger;
				else
					wrongCharacter = true;
				break;
			case 'L':
				if (GetOptionalLogger())
					GetOptionalLogger()->OnAssert(properties, result);
				else
					wrongCharacter = true;
				break;
			default:
				wrongCharacter = true;
				break;
			}
		}
	}

	Response ConsoleDisplayer::AskResponse(const Properties &properties,
		const Result &result) const
	{
		RichBool::detail::String choice;

		int response = 0;

		bool hasWrongCharacter = false;
		do
		{
			*in >> choice;

			response = 0;

			hasWrongCharacter = false;

			for (RichBool::detail::String::const_iterator it=choice.begin(); it!=choice.end(); ++it)
			{
				bool wrongCharacter = false;
				Response oneResponse = 0;

				ProcessCharacter(*it, properties, result, oneResponse, wrongCharacter);
				response |= oneResponse;

				if (wrongCharacter)
				{
					hasWrongCharacter = true;
					*out << "wrong character " << *it;
					RichBool::detail::Endl(*out);
				}
			}

		} while (hasWrongCharacter);

		return (Response)response;
	}

	void ConsoleDisplayer::SetGlobalOptionalActionSymbol(char ch)
	{
		globalOptionalActionSymbol = ch;
	}

	char ConsoleDisplayer::GetGlobalOptionalActionSymbol() const
	{
		return globalOptionalActionSymbol;
	}

	void ConsoleDisplayer::SetIsDebugPossible(bool b)
	{
		isDebugPossible = b;
	}
}
