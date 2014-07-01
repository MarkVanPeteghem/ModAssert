//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/parmlist.hpp"

namespace ModAssert
{
	bool SubString::operator==(const SubString& str) const
	{
		if (size()!=str.size())
			return false;
		return strncmp(begin_, str.begin_, size())==0;
	}

	RB_CONVERSION_HEADER(SubString)
	{
		const char *cur = val.begin();
		while(cur!=val.end())
			str << *cur++;
		return str;
	}

	ParameterList::ParameterList(): messages(0), lastMessage(0), cur(0)
	{}

	ParameterList::ParameterList(const char *expressions):
		messages(0), lastMessage(0), cur(0)
	{
		ParseExpressions(expressions);
	}

	ParameterList::~ParameterList()
	{
		delete messages;
	}

	ParameterList* ParameterList::clone() const
	{
		ParameterList *newParameterList = new ParameterList;
		for (const Message *msg=messages; msg; msg=msg->GetNext())
			newParameterList->AddMessage(msg->clone());
		return newParameterList;
	}

	bool IsWhiteSpace(char ch)
	{
		return (ch==' ') || (ch=='\t') || (ch=='\r') || (ch=='\n');
	}

	void SkipWhiteSpace(const char *&sz)
	{
		while (IsWhiteSpace(*sz))
			++sz;
	}

	// only called if a non-whitespace character has already passed
	void SkipWhiteSpaceBackwards(const char *&sz)
	{
		while (IsWhiteSpace(*(sz-1)))
			--sz;
	}

	void SkipStringLiteral(const char *&sz)
	{
		++sz;
		while (*sz)
		{
			if (*sz=='\"')
			{
				++sz;
				break;
			}
			if ( (*sz=='\\') && (*(sz+1)) )
				++sz;
			++sz;
		}
	}

	void SkipCharLiteral(const char *&sz)
	{
		++sz;
		while (*sz)
		{
			if (*sz=='\'')
			{
				++sz;
				break;
			}
			if ( (*sz=='\\') && (*(sz+1)) )
				++sz;
			++sz;
		}
	}

	void ParameterList::ParseExpressions(const char *expressions)
	{
		int level = 0;
		SkipWhiteSpace(expressions);
		const char *begin = expressions;
		bool stringLiteral = true;
		while (*expressions)
		{
			switch (*expressions)
			{
			case '(':
			case '[':
				++level;
				stringLiteral = false;
				break;
			case ')':
			case ']':
				--level;
				stringLiteral = false;
				break;
			case '<':
				if ( (0==level) && (*(expressions+1)=='<') )
				{
					const char *end = expressions;
					SkipWhiteSpaceBackwards(end);
					AddExpression(begin, end, stringLiteral);
					expressions += 2;
					SkipWhiteSpace(expressions);
					begin = expressions;
					--expressions;
					stringLiteral = true;
				}
				break;
			case '"':
				SkipStringLiteral(expressions);
				SkipWhiteSpace(expressions);
				--expressions;
				break;
			case '\'':
				SkipCharLiteral(expressions);
				--expressions;
				stringLiteral = false;
				break;
			default:
				stringLiteral = false;
				break;
			}
			++expressions;
		}
		AddExpression(begin, expressions, stringLiteral);
	}

	void ParameterList::AddCommaSeparatedList(const char *expressions)
	{
		SkipWhiteSpace(expressions);
		if (*expressions!='(')
			return; // something has gone wrong!!
		++expressions;

		int level = 0;
		SkipWhiteSpace(expressions);
		const char *begin = expressions;
		bool stringLiteral = true;
		while (*expressions)
		{
			switch (*expressions)
			{
			case '(':
			case '[':
				++level;
				stringLiteral = false;
				break;
			case ')':
			case ']':
				--level;
				break;
			case ',':
				if (0==level)
				{
					const char *end = expressions;
					SkipWhiteSpaceBackwards(end);
					AddExpression(begin, end, stringLiteral);
					++expressions;
					SkipWhiteSpace(expressions);
					begin = expressions;
					--expressions;
					stringLiteral = true;
				}
				break;
			case '"':
				SkipStringLiteral(expressions);
				SkipWhiteSpace(expressions);
				--expressions;
				break;
			case '\'':
				SkipCharLiteral(expressions);
				--expressions;
				stringLiteral = false;
				break;
			default:
				stringLiteral = false;
				break;
			}
			++expressions;
		} // while (*expressions)

		// -1 to ignore the final paren:
		AddExpression(begin, expressions-1, stringLiteral);
	}

	void ParameterList::AddExpression(const char *begin, const char *end,
		bool stringLiteral)
	{
		if (stringLiteral)
			AddMessage(new Message(begin, end));
		else
			AddMessage(new Value(begin, end));
	}


	template<class End>
	static bool IsStringLiteral(const char *str, const End &end)
	{
		if (*str!='"')
			return false;
		bool inString=true;
		while (!end(str+1))
		{
			++str;
			if (inString)
			{
				if ( (*str=='\\') && (*(str+1)=='"') )
					++str;
				else if (*str=='"')
					inString = false;
			}
			else
			{
				if (*str=='"')
					inString = true;
				else if ( (*str!=' ') && (*str!='\t')
					&& (*str!='\n') && (*str!='\r') )
						return false;
			}
		}
		return !inString;
	}

	struct IsNull
	{
		bool operator()(const char *str) const
		{
			return !*str;
		}
	};

	bool ParameterList::IsStringLiteral(const char *str)
	{
		return ModAssert::IsStringLiteral(str, IsNull());
	}

	struct IsEnd
	{
		IsEnd(const char *end): end_(end) {}
		bool operator()(const char *str) const
		{
			return str==end_;
		}
		const char *end_;
	};

	bool ParameterList::IsStringLiteral(const char *begin, const char *end)
	{
		return ModAssert::IsStringLiteral(begin, IsEnd(end));
	}

	bool ParameterList::operator==(const ParameterList &parameterList) const
	{
		if (messages)
			return parameterList.messages ? (*messages==*parameterList.messages) : false;
		else
			return parameterList.messages==0;
	}

	// virtual equivalent of operator== to solve a DLL problem in UquoniTest
	bool ParameterList::Equals(const ParameterList &valueList) const
	{
		return *this==valueList;
	}

	void ParameterList::AddMessage(const char *msg)
	{
		AddMessage(new Message(msg));
	}

	void ParameterList::AddMessage(Message *msg)
	{
		if (messages)
		{
			lastMessage->next = msg;
			lastMessage = msg;
		}
		else
		{
			messages = lastMessage = cur = msg;
		}
	}

	void ParameterList::streamout(RichBool::detail::OutStream &str) const
	{
		for (const ModAssert::ParameterList::Message *msg=messages; msg; msg=msg->GetNext())
		{
			str << "  ";
			if (msg->GetType()==eMessage)
			{
				str << msg->GetMessage();
			}
			else
			{
				Value *val = (Value*)msg;
				str << val->GetMessage() << ": " << val->GetValuePtr();
			}
			RichBool::detail::Endl(str);
		}
	}

	const char* ParameterList::Value::GetValuePtr() const
	{
		return value.c_str();
	}
}
