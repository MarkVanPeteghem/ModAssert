//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "stdafx.h"
#include "DemoMFC.h"
#include "DemoMFCDlg.h"

#define MOD_ASSERT_NO_TEXT

// include this file to use the modular assertions
#include "modassert/assert.hpp"

// include this files to use basic rich booleans
#include "richbool/richbool.hpp"

void OnFailingAssert(const std::string &extra);

void CDemoMFCDlg::OnNoText()
{
	OnFailingAssert("");

	MOD_ASSERT(1==2);
}
