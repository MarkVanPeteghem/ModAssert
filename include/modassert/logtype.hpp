//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef LOGTYPE_H__QM
#define LOGTYPE_H__QM

namespace ModAssert
{
	class LogType
	{
	public:
		enum Type { AtBegin, AtEnd, InBetween } type;

		LogType(Type t): type(t) {}
	};
}

#endif // #ifndef LOGTYPE_H__QM












