//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_WIN32_DLG_H__QM
#define MOD_ASSERT_WIN32_DLG_H__QM

#include "richbool/analysis.hpp"
#include <windows.h>

namespace InfoProviders
{
	class InfoUser;
}

namespace ModAssert
{
	class Properties;
	class Result;

	struct Data
	{
		Data(const Properties &properties_, const Result &result_, const InfoProviders::InfoUser &infoUser_):
			properties(&properties_), result(&result_), infoUser(&infoUser_) {}

		const Properties *properties;
		const Result *result;
		const InfoProviders::InfoUser *infoUser;
	};

	BOOL CALLBACK ModAssertDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif // #ifndef MOD_ASSERT_WIN32_DLG_H__QM
