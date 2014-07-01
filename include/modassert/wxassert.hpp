//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_WX_ASSERT_H__QM
#define MOD_WX_ASSERT_H__QM

#include "modassert/assert.hpp"

// #include this file in code where you have wxWidgets
// runtime assertions, to redefine them to equivalent ModAssert
// assertions.
// Make sure you #include this file *after* wx/debug.h.
// Note that there are two subtle differences in reporting:
// - the real wxFAIL* assertions have "wxAssertFailure" as the condition text,
//   while the ModAssert redefinitions don't have condition text.
// - the real wxCHECK* assertions also have "wxAssertFailure" as the condition text,
//   while the ModAssert redefinitions have the actual condition text.

#define wxASSERT MOD_ASSERT
#define wxASSERT_MSG(cond,msg) MOD_ASSERT_P(msg, cond)
#define wxFAIL MOD_FAIL
#define wxFAIL_MSG MOD_FAIL_P
#define wxCHECK(cond, rv) MOD_CHECK(cond, return rv)
#define wxCHECK_MSG(cond, rv, msg) MOD_CHECK_P(msg, cond, return rv)
#define wxCHECK_RET(cond, msg) MOD_CHECK_P(msg, cond, return)
#define wxCHECK2(cond, action) MOD_CHECK(cond, action)
#define wxCHECK2_MSG(cond, action, msg) MOD_CHECK_P(msg, cond, action)

#endif // #ifndef MOD_WX_ASSERT_H__QM
