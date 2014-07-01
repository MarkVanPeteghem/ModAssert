//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef DLL_DEMO_MA_INEXE_ASSERTION_H__QM
#define DLL_DEMO_MA_INEXE_ASSERTION_H__QM

#include "modassert/handler.hpp"

#ifdef DLL_EXPORTS
	#define DLL_API __declspec(dllexport)
#else
	#define DLL_API __declspec(dllimport)
#endif

DLL_API ModAssert::State *GetModAssertStateInDll();
DLL_API void SetupModAssert(bool debugAllowed);

#endif // #ifndef DLL_DEMO_MA_INEXE_ASSERTION_H__QM
