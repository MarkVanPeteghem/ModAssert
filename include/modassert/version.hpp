//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_VERSION_H__QM
#define MOD_ASSERT_VERSION_H__QM

#define MOD_ASSERT_VERSION "2_0_6"

namespace ModAssert
{
	inline const char* GetInstallDirectory()
	{
		return __FILE__;
	}
}

#endif // #ifndef MOD_ASSERT_VERSION_H__QM

// This has to be outside of the include guard,
// because it is always (and should be) undefined after including auto_link.hpp
#define QMENTUM_LIB_VERSION MOD_ASSERT_VERSION
