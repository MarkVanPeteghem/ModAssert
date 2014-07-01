//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wx/file.h"

#include "DemoWxDlg.h"

// define this symbol before including "modassert/assert.hpp"
// to eliminate the text of the condition and make the executable smaller
#define MOD_ASSERT_NO_TEXT

// include this file to use the modular assertions
#include "modassert/assert.hpp"

// include this files to use basic rich booleans
#include "richbool/richbool.hpp"

void DemoWxDialog::OnNoText(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();
	MOD_ASSERT(false);
}

