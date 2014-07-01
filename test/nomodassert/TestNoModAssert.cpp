//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include <stdio.h>
#include "modassert/assert.hpp"
#include "richbool/richbool.hpp"

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

int main(int , char* [])
{
	int a=0;
	MOD_ASSERT(rbEQUAL(a, 2));

	printf("This application was created to test that an application for which\n"
		"MOD_ASSERT_DONT_REPORT and MOD_CHECK_DONT_REPORT are globally defined,\n"
		"(and RICHBOOL_DONT_LINK for certain compilers), and MOD_ASSERT_REPORT_FILE\n"
		"and MOD_CHECK_REPORT_FILE are defined nowhere,\n"
		"doesn't need to link to the ModAssert or RichBooleans library.\n");

	return a;
}
