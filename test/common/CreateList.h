//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef CREATE_LIST_H__QM
#define CREATE_LIST_H__QM

namespace ModAssert
{
	class CreateParameterList
	{
	public:
		CreateParameterList()
		{
			parList = new ModAssert::ParameterList;
		}
		~CreateParameterList()
		{
			delete parList;
		}
		template<typename T>
		CreateParameterList& operator()(const char *expr, const T &t)
		{
			parList->AddMessage(new ModAssert::ParameterList::Value(expr, expr+strlen(expr), RichBool::ToString(t)));
			return *this;
		}
		CreateParameterList& operator()(const char *message)
		{
			parList->AddMessage(new ModAssert::ParameterList::Message(message, message+strlen(message)));
			return *this;
		}
		operator ModAssert::ParameterList*()
		{
			ModAssert::ParameterList *rv = parList;
			parList = 0;
			return rv;
		}
		ModAssert::ParameterList *parList;
	};
}

typedef ModAssert::CreateParameterList CreateParameterList;

#endif // #ifndef CREATE_LIST_H__QM













