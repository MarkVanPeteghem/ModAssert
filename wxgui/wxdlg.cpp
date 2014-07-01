//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "modassert/wxdlg.hpp"
#include "modassert/logger.hpp"
#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/handler.hpp"
#include <wx/listctrl.h>
#include <wx/checkbox.h>
#include "richbool/richbool.hpp"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
#include "ModAssertF.xpm"
#include "ModAssertS.xpm"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    Ok = 1,
	OptionalLogger
};

namespace ModAssert
{
	BEGIN_EVENT_TABLE(WxDlg, wxDialog)
		EVT_BUTTON(Ok,  WxDlg::OnOK)
		EVT_BUTTON(OptionalLogger,  WxDlg::OnOptionalLogger)
	END_EVENT_TABLE()

	// Dialog constructor
	WxDlg::WxDlg(const Properties &properties,
			const Result &assertionResult,
			const InfoProviders::InfoUser &infoUser):

	wxDialog((wxWindow*) NULL, wxWindowID(5),
			"",
			wxDefaultPosition),
		m_properties(properties),
		m_assertionResult(assertionResult),
		m_infoUser(infoUser),
		m_debug(0), m_exit(0), m_optional(0), m_globalOptional(0),
		m_stopDisplayingThis(0), m_stopDisplayingThisFile(0),
		m_stopDisplayingAll(0),
		m_stopDisplayingCustom1(0), m_stopDisplayingCustom2(0),
		m_stopDisplayingCustom3(0), m_stopDisplayingCustom4(0)
	{
		wxString title = m_properties.GetCategory()->GetName();
		title += m_assertionResult.Succeeded() ? " succeeded" : " failed";
		title[0] = toupper(title[0]);
		SetTitle(title);

		wxBoxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );
		
		mainSizer->AddSpacer(10); // empty space at the top

		wxString message;
		if (!m_properties.IsUnconditional())
		{
			message << properties.GetCategory()->GetName();
			if (m_properties.GetCondition())
				message << " " << m_properties.GetCondition();
			message << (m_assertionResult.Succeeded() ?  " succeeded" : " failed");
			if (!m_properties.GetCondition())
				message << " (no text of condition available)";
		}
		else
			message << "Unconditional " << properties.GetCategory()->GetName()
				<< " failure";
		int x=0, y=0;
		GetTextExtent(message, &x, &y);
		int nrLines = x/375+1;
		wxTextCtrl *msgWnd = new wxTextCtrl(this, -1, message,
			wxDefaultPosition, wxSize(400, y*nrLines+y/2),
			wxTE_MULTILINE|wxTE_READONLY);
		mainSizer->Add(msgWnd);

		mainSizer->AddSpacer(5);

		message = RichBool::ToString(m_properties.GetContext());
		mainSizer->Add(new wxStaticText(this, -1, message));

		const int fontSize = GetFont().GetPointSize();

		if (m_assertionResult.GetAnalysis())
		{
			wxTextCtrl *textCtrl = new wxTextCtrl(this, -1,
				RichBool::ToString(*m_assertionResult.GetAnalysis()),
				wxDefaultPosition, wxSize(400, 80), wxTE_MULTILINE|wxTE_READONLY);

			wxFont font(fontSize, wxFONTFAMILY_MODERN, wxNORMAL, wxNORMAL);
			textCtrl->SetFont(font);

			mainSizer->AddSpacer(10);
			mainSizer->Add(textCtrl);
		}

		if (m_assertionResult.GetParameterList() && m_assertionResult.GetParameterList()->GetFirst())
		{
			wxListCtrl *listCtrl = new wxListCtrl(this, -1, wxDefaultPosition,
				wxSize(400, 80), wxLC_REPORT);

			listCtrl->InsertColumn(0, "Expressions", wxLIST_FORMAT_LEFT, 160);
			listCtrl->InsertColumn(1, "Values",      wxLIST_FORMAT_LEFT, 230);

			int idx = 0;
			for (const ParameterList::Message *msg=m_assertionResult.GetParameterList()->GetFirst();
				msg; msg = msg->GetNext(), ++idx)
			{
				wxString message = msg->GetMessage();
				if (msg->GetType()==ParameterList::eMessage)
				{
					listCtrl->InsertItem(idx, "message");
					listCtrl->SetItem(idx, 1, message);
				}
				else if (msg->GetType()==ParameterList::eValue)
				{
					ParameterList::Value *value =
						(ParameterList::Value*)msg;
					wxString str = "expr: ";
					listCtrl->InsertItem(idx, str+message);
					listCtrl->SetItem(idx, 1,
						value->GetValue());
				}
			}

			mainSizer->AddSpacer(10);
			mainSizer->Add(listCtrl);
		}

		wxString extraInfo = GetAllInfo(m_properties, m_assertionResult, m_infoUser);
		if (!extraInfo.IsEmpty())
		{
			wxTextCtrl *textCtrl = new wxTextCtrl(this, -1, extraInfo,
				wxDefaultPosition, wxSize(400, 6*fontSize), wxTE_MULTILINE|wxTE_READONLY);

			wxFont font(fontSize, wxFONTFAMILY_MODERN, wxNORMAL, wxNORMAL);
			textCtrl->SetFont(font);

			mainSizer->AddSpacer(10);
			mainSizer->Add(textCtrl);
		}

		wxBoxSizer *leftInputsSizer  = new wxBoxSizer( wxVERTICAL );

		wxBoxSizer *debugExitSizer  = new wxBoxSizer( wxHORIZONTAL );
		m_debug = new wxCheckBox(this, -1, _("Debug"));

		if (!GetAllowBreakIntoDebugger())
			m_debug->Disable();
	#if defined(__WIN32__) || (defined(__WXMAC__) && defined(__MWERKS__))
		if (!wxIsDebuggerRunning() || !IsDebugPossible())
			m_debug->Disable();
	#endif

		m_exit = new wxCheckBox(this, -1, _("Exit"));
		if (!GetAllowExit())
			m_exit->Disable();

		debugExitSizer->Add(m_debug);
		debugExitSizer->AddSpacer(15);
		debugExitSizer->Add(m_exit);

		leftInputsSizer->Add(debugExitSizer);
		leftInputsSizer->AddSpacer(8);
		
		if (GetGlobalOptionalAction() && GetAllowGlobalOptional())
		{
			m_globalOptional = new wxCheckBox(this, -1, GetGlobalOptionalActionDescription());
			leftInputsSizer->AddSpacer(8);
			leftInputsSizer->Add(m_globalOptional);
		}

		if (m_properties.GetOptional() && GetAllowOptional())
		{
			m_optional = new wxCheckBox(this, -1, m_properties.GetOptional());
			leftInputsSizer->AddSpacer(8);
			leftInputsSizer->Add(m_optional);
		}

		if (GetOptionalLogger())
		{
			leftInputsSizer->AddSpacer(8);
			leftInputsSizer->Add(
				new wxButton(this, OptionalLogger, GetOptionalLoggerText(),
					wxDefaultPosition, wxDefaultSize)
			);
		}

		leftInputsSizer->AddSpacer(8);
		leftInputsSizer->Add(
			new wxButton(this, Ok, _("Ok"), wxDefaultPosition, wxDefaultSize)
		);
		
		wxBoxSizer *stopDisplayingLeftSizer = new wxBoxSizer(wxVERTICAL),
			*stopDisplayingRightSizer = new wxBoxSizer(wxVERTICAL);

		const int spacing = 5;
		if (properties.CanStopDisplayingThis())
		{
			m_stopDisplayingThis = new wxCheckBox(this, -1, "This");
			stopDisplayingLeftSizer->Add(m_stopDisplayingThis);
			stopDisplayingLeftSizer->AddSpacer(spacing);
		}
		m_stopDisplayingThisFile = new wxCheckBox(this, -1, "In this file");
		m_stopDisplayingAll = new wxCheckBox(this, -1,
			wxString("All ")+m_properties.GetCategory()->GetName()+"s");
		stopDisplayingLeftSizer->Add(m_stopDisplayingThisFile);
		stopDisplayingLeftSizer->AddSpacer(spacing);
		stopDisplayingLeftSizer->Add(m_stopDisplayingAll);

		const GroupList *groupList = m_properties.GetGroupList();
		m_stopDisplayingCustom1 =
			new wxCheckBox(this, -1, groupList->GetSize()>0 ? groupList->GetName(0) : "-");
		m_stopDisplayingCustom1->Enable(groupList->GetSize()>0);
		
		m_stopDisplayingCustom2 =
			new wxCheckBox(this, -1, groupList->GetSize()>1 ? groupList->GetName(1) : "-");
		m_stopDisplayingCustom2->Enable(groupList->GetSize()>1);
		
		m_stopDisplayingCustom3 =
			new wxCheckBox(this, -1, groupList->GetSize()>2 ? groupList->GetName(2) : "-");
		m_stopDisplayingCustom3->Enable(groupList->GetSize()>2);
		
		m_stopDisplayingCustom4 =
			new wxCheckBox(this, -1, groupList->GetSize()>3 ? groupList->GetName(3) : "-");
		m_stopDisplayingCustom4->Enable(groupList->GetSize()>3);

		stopDisplayingRightSizer->Add(m_stopDisplayingCustom1);
		stopDisplayingRightSizer->AddSpacer(spacing);
		stopDisplayingRightSizer->Add(m_stopDisplayingCustom2);
		stopDisplayingRightSizer->AddSpacer(spacing);
		stopDisplayingRightSizer->Add(m_stopDisplayingCustom3);
		stopDisplayingRightSizer->AddSpacer(spacing);
		stopDisplayingRightSizer->Add(m_stopDisplayingCustom4);

		wxString stopDisplayingTitle = "Stop displaying ";
		stopDisplayingTitle += m_properties.GetCategory()->GetName();
		stopDisplayingTitle += "s";
		wxStaticBoxSizer *stopDisplayingSizer =
			new wxStaticBoxSizer(wxHORIZONTAL, this, stopDisplayingTitle);

		stopDisplayingSizer->Add(stopDisplayingLeftSizer);
		stopDisplayingSizer->AddSpacer(6);
		stopDisplayingSizer->Add(stopDisplayingRightSizer);

		wxBoxSizer *inputsSizer = new wxBoxSizer( wxHORIZONTAL );
		inputsSizer->Add(leftInputsSizer);
		inputsSizer->AddSpacer(50);
		inputsSizer->Add(stopDisplayingSizer);

		mainSizer->AddSpacer(10);
		mainSizer->Add(inputsSizer);

		mainSizer->AddSpacer(10); // empty space at the bottom

		wxBoxSizer *wrapperSizer = new wxBoxSizer(wxHORIZONTAL);
		wrapperSizer->AddSpacer(10);
		wrapperSizer->Add(mainSizer);
		wrapperSizer->AddSpacer(10);

		SetSizerAndFit(wrapperSizer);

		// set the Dialog icon
		if (m_assertionResult.Succeeded())
			SetIcon(ModAssertS_xpm);
		else
			SetIcon(ModAssertF_xpm);

		Fit();
	}

	// Dialog destructor
	WxDlg::~WxDlg()
	{
	}

	// event handlers

	void WxDlg::OnOptionalLogger(wxCommandEvent& WXUNUSED(event))
	{
		if (GetOptionalLogger())
			GetOptionalLogger()->OnAssert(m_properties, m_assertionResult);
	}

	void WxDlg::OnOK(wxCommandEvent& WXUNUSED(event))
	{
		int response = 0;

		if (m_debug->GetValue() && IsDebugPossible())
			response |= BreakIntoDebugger;
		if (m_exit->GetValue())
			response |= Exit;
		if (m_globalOptional && m_globalOptional->GetValue())
			response |= GlobalOptional;
		if (m_optional && m_optional->GetValue())
			response |= Optional;

		if (m_stopDisplayingThis && m_stopDisplayingThis->GetValue())
			response |= StopDisplayingThis;
		if (m_stopDisplayingThisFile->GetValue())
			response |= StopDisplayingFile;
		if (m_stopDisplayingAll->GetValue())
			response |= StopDisplayingAll;

		if (m_stopDisplayingCustom1->GetValue())
			response |= StopDisplayingCustom1;
		if (m_stopDisplayingCustom2->GetValue())
			response |= StopDisplayingCustom2;
		if (m_stopDisplayingCustom3->GetValue())
			response |= StopDisplayingCustom3;
		if (m_stopDisplayingCustom4->GetValue())
			response |= StopDisplayingCustom4;

		EndModal(response);
	}
}












