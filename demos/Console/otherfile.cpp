//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "modassert/assert.hpp"
#include "richbool/richbool.hpp"

void OnFailingAssert(const std::string &extra="");

void OnFailInOtherFile()
{
	OnFailingAssert();

	int a = 3;
	MOD_ASSERT(rbEQUAL(5, a));
}















