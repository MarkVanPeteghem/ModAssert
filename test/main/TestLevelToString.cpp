//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "richbool/richbool.hpp"

MA_TEST(LevelToString)
{
	META_ASSERT(rbEQUAL(ModAssert::Info.GetName(0), "Level: Info"));
	META_ASSERT(rbEQUAL(ModAssert::Warning.GetName(0), "Level: Warning"));
	META_ASSERT(rbEQUAL(ModAssert::Error.GetName(0), "Level: Error"));
	META_ASSERT(rbEQUAL(ModAssert::Fatal.GetName(0), "Level: Fatal"));
}
