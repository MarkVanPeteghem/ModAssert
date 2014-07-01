//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef WX_MOD_ASSERT_DIALOG_H__QM
#define WX_MOD_ASSERT_DIALOG_H__QM

#include "wx/dialog.h"
#include "modassert/assert.hpp"

class wxCheckBox;

namespace InfoProviders
{
	class InfoUser;
}

namespace ModAssert
{
	class Properties;
	class Result;

	class WxDlg: public wxDialog
	{
	public:
		WxDlg(const Properties &properties,
			const Result &assertionResult,
			const InfoProviders::InfoUser &infoUser);

		virtual ~WxDlg();

		void OnOK(wxCommandEvent& event);
		void OnOptionalLogger(wxCommandEvent& event);

	private:
		const Properties &m_properties;
		const Result &m_assertionResult;
		const InfoProviders::InfoUser &m_infoUser;

		DECLARE_EVENT_TABLE()

		wxCheckBox *m_debug, *m_exit, *m_optional, *m_globalOptional,
			*m_stopDisplayingThis, *m_stopDisplayingThisFile, *m_stopDisplayingAll,
			*m_stopDisplayingCustom1, *m_stopDisplayingCustom2,
			*m_stopDisplayingCustom3, *m_stopDisplayingCustom4;
	};
}

#endif // #ifndef WX_MOD_ASSERT_DIALOG_H__QM
