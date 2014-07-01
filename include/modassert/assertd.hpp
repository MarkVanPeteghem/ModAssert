//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_D_H__QM
#define MOD_ASSERT_D_H__QM

#include "modassert/assert.hpp"

#ifdef ASSERT
#undef ASSERT
#endif

#define ASSERT MOD_ASSERT

#ifdef VERIFY
#undef VERIFY
#endif

#define VERIFY MOD_VERIFY

#endif // #ifndef MOD_ASSERT_D_H__QM
