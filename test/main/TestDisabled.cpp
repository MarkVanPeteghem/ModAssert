//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

// usually this is defined on the command line or in the project settings,
// but here we do it in a file to make testing easier
#define MOD_ASSERT_DONT_REPORT
#include "modassert/assert.hpp"

#include "ModAssertTest.h"

MA_TEST(Test_Disabled)
{
	EXPECT_NO_FAILURE;
	MOD_FAIL;

	META_ASSERT(!CheckLoggerCalled());
}
