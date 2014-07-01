//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_CATEGORIES_H__QM
#define MOD_ASSERT_CATEGORIES_H__QM

namespace ModAssert
{
	struct Assertions
	{
		static const char * const name;

		enum { IsAssertion = 1, IsCheck = 0 };
	};

	struct Checks
	{
		static const char * const name;

		enum { IsAssertion = 0, IsCheck = 1 };
	};
}

#endif // #ifndef MOD_ASSERT_CATEGORIES_H__QM
