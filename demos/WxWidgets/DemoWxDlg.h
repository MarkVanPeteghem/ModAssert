//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef DemoWxDialog_H
#define DemoWxDialog_H

// Define a new Dialog type: this is going to be our main Dialog
class DemoWxDialog : public wxDialog
{
public:
    // ctor(s)
    DemoWxDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~DemoWxDialog();

    // event handlers (these functions should _not_ be virtual)
	void OnEqualInt(wxCommandEvent& event);
	void OnEqualIntWithData(wxCommandEvent& event);
	void OnEqualString(wxCommandEvent& event);
	void OnEqualStringWithBackslash(wxCommandEvent& event);
	void OnEqualArray(wxCommandEvent& event);
	void OnEqualArrayAndList(wxCommandEvent& event);

	void OnDiffInt(wxCommandEvent& event);
	void OnDiffIntWithData(wxCommandEvent& event);
	void OnDiffString(wxCommandEvent& event);
	void OnDiffStringWithBackslash(wxCommandEvent& event);
	void OnDiffArray(wxCommandEvent& event);
	void OnDiffArrayAndList(wxCommandEvent& event);
	void OnDiffArrayArray(wxCommandEvent& event);
	void OnLessOnVector(wxCommandEvent& event);
	void OnPred1Fail(wxCommandEvent& event);
	void OnPred2Fail(wxCommandEvent& event);
	void OnPred3Fail(wxCommandEvent& event);
	void OnAnd(wxCommandEvent& event);

	void OnFailWithGroup(wxCommandEvent& event);
	void OnFailWithTwoGroups(wxCommandEvent& event);
	void OnFailWithLevelWarning(wxCommandEvent& event);
	void OnFailWithLevelFatal(wxCommandEvent& event);
	void OnFailWithOneGroupAndLevelWarning(wxCommandEvent& event);
	void OnFailWithTwoGroupsAndLevelWarning(wxCommandEvent& event);

	void OnFailWithOptional(wxCommandEvent& event);
	void OnFailInOtherThread(wxCommandEvent& event);
	void OnCheckAndReturnFalse(wxCommandEvent& event);
	void OnDisplaySuccess(wxCommandEvent& event);
	void OnDisplayReportAll(wxCommandEvent& event);
	void OnModVerifyV(wxCommandEvent& event);

	void OnWxAssert(wxCommandEvent& event);
	void OnOptional(wxCommandEvent& event);
	void OnSysError(wxCommandEvent& event);

	void OnNoText(wxCommandEvent& event);

	void OnQuit(wxCloseEvent& event);
	void OnExit(wxCommandEvent& event);

private:
    DECLARE_CLASS(DemoWxDialog)
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

void OnFailingAssert(const wxString &extra="");

#endif // DemoWxDialog_H
