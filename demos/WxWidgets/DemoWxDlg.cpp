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

// include this file to use the modular assertions
#include "modassert/assert.hpp"

// include this files to use basic rich booleans
#include "richbool/richbool.hpp"

// include this file to use rich booleans for wxWidgets strings
#include "richbool/wxstring.hpp"

// include these two files to use rich booleans for wxWidgets containers
#include "richbool/wx_iter.hpp"
#include "richbool/xcontainers.hpp"




// This is only needed for ModAssert::GetMode(); normally you don't need this
// in source files that don't setup ModAssert.
#include "modassert/handler.hpp"


#include <wx/arrimpl.cpp>
#include <wx/listimpl.cpp>

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "ModAssertWx.xpm"
    #include "ModAssertWx32x32.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,
    EqualInt,
    EqualIntWithData,
	EqualString,
	EqualStringWithBackslash,
	EqualArray,
	EqualArrayAndList,
    DiffInt,
    DiffIntWithData,
	DiffString,
	DiffStringWithBackslash,
	DiffArray,
	DiffArrayAndList,
	DiffArrayArray,
	LessOnVector,
	Pred1Fail,
	Pred2Fail,
	Pred3Fail,
	And,
	FailWithOptional,
	FailWithGroup,
	FailWithTwoGroups,
	FailWithLevelWarning,
	FailWithOneGroupAndLevelWarning,
	FailWithTwoGroupsAndLevelWarning,
	FailWithLevelFatal,
	CheckAndReturnFalse,
	DisplaySuccess,
	DisplayReportAll,
	ModVerifyV,
	FailInOtherThread,
	WxAssert,
	Optional,
	SysError,
	NoText
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
IMPLEMENT_CLASS(DemoWxDialog, wxDialog)
BEGIN_EVENT_TABLE(DemoWxDialog, wxDialog)
	EVT_BUTTON(EqualInt,  DemoWxDialog::OnEqualInt)
	EVT_BUTTON(EqualIntWithData,  DemoWxDialog::OnEqualIntWithData)
	EVT_BUTTON(EqualString,  DemoWxDialog::OnEqualString)
	EVT_BUTTON(EqualStringWithBackslash,  DemoWxDialog::OnEqualStringWithBackslash)
	EVT_BUTTON(EqualArray,  DemoWxDialog::OnEqualArray)
	EVT_BUTTON(EqualArrayAndList,  DemoWxDialog::OnEqualArrayAndList)
	EVT_BUTTON(DiffInt,  DemoWxDialog::OnDiffInt)
	EVT_BUTTON(DiffIntWithData,  DemoWxDialog::OnDiffIntWithData)
	EVT_BUTTON(DiffString,  DemoWxDialog::OnDiffString)
	EVT_BUTTON(DiffStringWithBackslash,  DemoWxDialog::OnDiffStringWithBackslash)
	EVT_BUTTON(DiffArray,  DemoWxDialog::OnDiffArray)
	EVT_BUTTON(DiffArrayAndList,  DemoWxDialog::OnDiffArrayAndList)
	EVT_BUTTON(DiffArrayArray,  DemoWxDialog::OnDiffArrayArray)
	EVT_BUTTON(LessOnVector,  DemoWxDialog::OnLessOnVector)
	EVT_BUTTON(Pred1Fail,  DemoWxDialog::OnPred1Fail)
	EVT_BUTTON(Pred2Fail,  DemoWxDialog::OnPred2Fail)
	EVT_BUTTON(Pred3Fail,  DemoWxDialog::OnPred3Fail)
	EVT_BUTTON(And,  DemoWxDialog::OnAnd)
 	EVT_BUTTON(FailWithOptional,  DemoWxDialog::OnFailWithOptional)
 	EVT_BUTTON(FailWithGroup,  DemoWxDialog::OnFailWithGroup)
 	EVT_BUTTON(FailWithTwoGroups,  DemoWxDialog::OnFailWithTwoGroups)
 	EVT_BUTTON(FailWithLevelWarning,  DemoWxDialog::OnFailWithLevelWarning)
 	EVT_BUTTON(FailWithOneGroupAndLevelWarning,  DemoWxDialog::OnFailWithOneGroupAndLevelWarning)
 	EVT_BUTTON(FailWithTwoGroupsAndLevelWarning,  DemoWxDialog::OnFailWithTwoGroupsAndLevelWarning)
 	EVT_BUTTON(FailWithLevelFatal,  DemoWxDialog::OnFailWithLevelFatal)
	EVT_BUTTON(CheckAndReturnFalse,  DemoWxDialog::OnCheckAndReturnFalse)
	EVT_BUTTON(DisplaySuccess,  DemoWxDialog::OnDisplaySuccess)
	EVT_BUTTON(DisplayReportAll,  DemoWxDialog::OnDisplayReportAll)
	EVT_BUTTON(ModVerifyV,  DemoWxDialog::OnModVerifyV)
 	EVT_BUTTON(FailInOtherThread,  DemoWxDialog::OnFailInOtherThread)
 	EVT_BUTTON(WxAssert,  DemoWxDialog::OnWxAssert)
	EVT_BUTTON(Optional,  DemoWxDialog::OnOptional)
	EVT_BUTTON(SysError,  DemoWxDialog::OnSysError)
	EVT_BUTTON(NoText,  DemoWxDialog::OnNoText)
    EVT_BUTTON(Minimal_Quit,  DemoWxDialog::OnExit)
    EVT_CLOSE(DemoWxDialog::OnQuit)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// main Dialog
// ----------------------------------------------------------------------------

// Dialog constructor
DemoWxDialog::DemoWxDialog(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxDialog((wxDialog *) NULL, -1, title, pos, size)
{
	wxSize buttonSize(120, 25), buttonSize2(140, 25);

	wxStaticBoxSizer *column1 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, "Succeeding Rich Booleans");

	wxGridSizer *grid1 = new wxGridSizer(8, 1, 10, 10);
    grid1->Add(new wxButton(this, EqualInt, _("Equal int"), wxDefaultPosition, buttonSize));
    grid1->Add(new wxButton(this, EqualIntWithData, _("Equal int with data"), wxDefaultPosition, buttonSize));
    grid1->Add(new wxButton(this, EqualString, _("Equal String"), wxDefaultPosition, buttonSize));
    grid1->Add(new wxButton(this, EqualStringWithBackslash, _("Equal String with \\"), wxDefaultPosition, buttonSize));
    grid1->Add(new wxButton(this, EqualArray, _("Equal Array"), wxDefaultPosition, buttonSize));
    grid1->Add(new wxButton(this, EqualArrayAndList, _("Equal Array and List"), wxDefaultPosition, buttonSize));

	column1->Add(grid1, 0, wxALL, 6);
	
	wxGridSizer *grid2 = new wxGridSizer(8, 2, 10, 10);
    grid2->Add(new wxButton(this, DiffInt, _("Diff int"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffIntWithData, _("Diff int with data"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffString, _("Diff String"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffStringWithBackslash, _("Diff String with \\"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffArray, _("Diff Array"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffArrayAndList, _("Diff Array and List"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, DiffArrayArray, _("Diff Array Array"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, LessOnVector, _("Less On Vector"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, Pred1Fail, _("Pred 1 fail"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, Pred2Fail, _("Pred 2 fail"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, Pred3Fail, _("Pred 3 fail"), wxDefaultPosition, buttonSize));
    grid2->Add(new wxButton(this, And, _("And"), wxDefaultPosition, buttonSize));

	wxStaticBoxSizer *column2 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, "Failing Rich Booleans");
	column2->Add(grid2, 0, wxALL, 6);

	wxStaticBoxSizer *column3 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, "ModAssert features");

	wxGridSizer *grid3 = new wxGridSizer(8, 2, 10, 10);
	grid3->Add(new wxButton(this, FailWithGroup, _("1 group"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, FailWithTwoGroups, _("2 Groups"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, FailWithLevelWarning, _("Level Warning"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, FailWithLevelFatal, _("Level Fatal"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, FailWithOneGroupAndLevelWarning, _("1 Group % Level Warning"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, FailWithTwoGroupsAndLevelWarning, _("2 Groups % Level Warning"), wxDefaultPosition, buttonSize2));
    grid3->Add(new wxButton(this, FailInOtherThread, _("Fail in other Thread"), wxDefaultPosition, buttonSize2));
    grid3->Add(new wxButton(this, CheckAndReturnFalse, _("Check and return false"), wxDefaultPosition, buttonSize2));
    grid3->Add(new wxButton(this, DisplaySuccess, _("Display success"), wxDefaultPosition, buttonSize2));
    grid3->Add(new wxButton(this, DisplayReportAll, _("ReportAll"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, ModVerifyV, _("MOD_VERIFY_V"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, WxAssert, _("wxASSERT"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, Optional, _("Optional action"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, SysError, _("SysError"), wxDefaultPosition, buttonSize2));
	grid3->Add(new wxButton(this, NoText, _("No text"), wxDefaultPosition, buttonSize2));

	column3->Add(grid3, 0, wxALL, 6);

	wxFlexGridSizer *grid = new wxFlexGridSizer(1, 4, 10, 10);
	grid->Add(column1);
	grid->Add(column2);
	grid->Add(column3);
    grid->Add(new wxButton(this, Minimal_Quit, _("Quit"), wxDefaultPosition, wxSize(60, 25)));

	wxBoxSizer *wrapper = new wxBoxSizer(wxVERTICAL);
	wrapper->AddSpacer(10);
	wrapper->Add(grid, 0, wxALL, 6);
	wrapper->AddSpacer(10);

	SetSizerAndFit(wrapper);


    // set the Dialog icon
    SetIcon(wxICON(ModAssertWx));

	Fit();
}

// Dialog destructor
DemoWxDialog::~DemoWxDialog()
{
}

WX_DEFINE_ARRAY_INT(int, IntArray);
WX_DECLARE_OBJARRAY(IntArray, IntArrayArray);
WX_DEFINE_OBJARRAY(IntArrayArray);

WX_DEFINE_ARRAY_ITERATOR_P(int, IntArray, IntArrayIterator)
WX_DEFINE_ARRAY_ITERATOR(IntArray, IntArrayArray, IntArrayArrayIterator)

WX_DECLARE_LIST(int, IntList);

WX_DEFINE_LIST(IntList);

WX_DEFINE_LIST_ITERATOR_P(int, IntList, IntListIterator)

// event handlers

void OnSucceedingAssert()
{
#if MOD_ASSERT_REPORTS
	wxMessageBox("Now comes a succeeding assertion,\n"
		"so no debug information will be shown");
#else
	wxMessageBox("Assertions are off,\n"
		"so no debug information will be shown");
#endif
}

void OnFailingAssert(const wxString &extra)
{
#if MOD_ASSERT_REPORTS
	wxString str = "Reporting of assertions is enabled at compile time,\n";
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		str += "and SetupForWxWidgets(testMode) was called\n"
			"so a message will be shown\n"
			"unless this or all assertions are ignored"+extra;
		break;
	case ModAssert::continueSilentlyOnFailure:
		str += "and SetupForWxWidgets(continueSilentlyOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::continueWithWarningOnFailure:
		str += "and SetupForWxWidgets(continueWithWarningOnFailure) was called\n"
			"so the application will continue with a warning, unless the level is too low.";
		break;
	case ModAssert::terminateOnFailure:
		str += "and SetupForWxWidgets(terminateOnFailure) was called\n"
			"so the application will terminate, unless the level is too low.";
		break;
	}
	wxMessageBox(str);
#else
	wxMessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}

void OnFailingCheck(const wxString & IF_MOD_CHECK_REPORTS(extra))
{
#if MOD_CHECK_REPORTS
	wxString str = "Reporting of checks is enabled at compile time,\n";
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		str += "and SetupForWxWidgets(testMode) was called\n"
			"so a message will be shown\n"
			"unless this or all checks are ignored"+extra;
		break;
	case ModAssert::continueSilentlyOnFailure:
		str += "and SetupForWxWidgets(continueSilentlyOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::continueWithWarningOnFailure:
		str += "and SetupForWxWidgets(continueWithWarningOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::terminateOnFailure:
		str += "and SetupForWxWidgets(terminateOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	}
	wxMessageBox(str);
#else
	wxMessageBox("Reporting of checks is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}


#if MOD_ASSERT_REPORTS && !defined(NDEBUG)
static void OnFailingWxAssert(const wxString & extra)
#else
static void OnFailingWxAssert(const wxString &)
#endif
{
#if MOD_ASSERT_REPORTS
#ifdef NDEBUG
	wxMessageBox("wxWidgets assertions are compiled out,\n"
			"so no debug information will be shown");
#else
	wxMessageBox("Now comes a failing assertion,\n"
		"so debug information will be shown\n"
		"unless this or all assertions are ignored"+extra);
#endif
#else
	wxMessageBox("Assertions are off,\n"
		"so no debug information will be shown");
#endif
}


static void OnFailingWxAssert()
{
	OnFailingWxAssert("");
}

void DemoWxDialog::OnEqualInt(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	int a = 0;
	MOD_ASSERT(rbEQUAL(0, a));
}

void DemoWxDialog::OnEqualIntWithData(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	int a=0, b=1, c=2, d=3;
	MOD_ASSERT_P(a << b << c << d, rbEQUAL(a+d, b+c));
}

void DemoWxDialog::OnEqualString(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	wxString str1="abc", str2 = "abc";
	MOD_ASSERT(rbSTRCMP(str1, ==, str2));
}

void DemoWxDialog::OnEqualStringWithBackslash(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	wxString str1="ab\\", str2 = "ab\\";
	MOD_ASSERT(rbSTRCMP(str1, ==, str2));
}

void DemoWxDialog::OnEqualArray(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	IntArray arr1, arr2;
	arr1.Add(1);  arr2.Add(1);
	arr1.Add(2);  arr2.Add(2);
	MOD_ASSERT(rbIN_XCONTAINERS(arr1, arr2, RichBool::AllEqual<>(true)));
}

void DemoWxDialog::OnEqualArrayAndList(wxCommandEvent& WXUNUSED(event))
{
	OnSucceedingAssert();

	IntArray arr;
	IntList list;
	int a=1, b=2;
	arr.Add(a);  list.Append(&a);
	arr.Add(b);  list.Append(&b);
	MOD_ASSERT(rbIN_XCONTAINERS(arr, list, RichBool::AllEqual<>(true)));
}

void DemoWxDialog::OnDiffInt(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	int a = 0;
	MOD_ASSERT(rbEQUAL(1, a));
}

void DemoWxDialog::OnDiffIntWithData(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	int a=0, b=1, c=2, d=3;
	MOD_ASSERT_P(a << b << c << d, rbEQUAL(a+b, c+d));
}

void DemoWxDialog::OnDiffString(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	wxString str1="abc", str2 = "abd";
	MOD_ASSERT(rbSTRCMP(str1, ==, str2));
}

void DemoWxDialog::OnDiffStringWithBackslash(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	wxString str1="abc", str2 = "ab\\";
	MOD_ASSERT(rbSTRCMP(str1, ==, str2));
}

void DemoWxDialog::OnDiffArray(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	IntArray arr1, arr2;
	arr1.Add(1);  arr2.Add(1);
	arr1.Add(2);
	arr1.Add(3);  arr2.Add(3);
	              arr2.Add(4);
	arr1.Add(5);  arr2.Add(5);
	arr1.Add(6);  arr2.Add(7);
	arr1.Add(8);  arr2.Add(8);
	MOD_ASSERT(rbIN_XCONTAINERS(arr1, arr2, RichBool::AllEqual<>(true)));
}

void DemoWxDialog::OnDiffArrayAndList(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	IntArray arr;
	IntList list;
	int a=1, b=3;
	arr.Add(1);  list.Append(&a);
	arr.Add(2);  list.Append(&b);
	MOD_ASSERT(rbIN_XCONTAINERS(arr, list, RichBool::AllEqual<>(true)));
}

void DemoWxDialog::OnDiffArrayArray(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	IntArrayArray arr1, arr2;

	IntArray a, a1, a2, a12;
	a1.Add(1);
	a2.Add(2);
	a12.Add(1);
	a12.Add(2);

	arr1.Add(a);   arr2.Add(a);
	arr1.Add(a1);
	arr1.Add(a2);  arr2.Add(a12);

	MOD_ASSERT(rbIN_XCONTAINERS(arr1, arr2,
		RichBool::Compare<>(true).That(RichBool::XContainersEqual<>(true))));
}

void DemoWxDialog::OnLessOnVector(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	IntArray arr1, arr2;
	
	arr1.Add(1); arr2.Add(2);
	arr1.Add(3); arr2.Add(6);
	arr1.Add(5); arr2.Add(4); // intentional error
	arr1.Add(6); arr2.Add(8);

	MOD_ASSERT(rbIN_XCONTAINERS(arr1, arr2,
		RichBool::Compare<>(true).That(RichBool::Less<>())));
}

struct IsEven
{
	bool operator()(int n) const
	{
		return n%2==0;
	}
};

struct ProductIs12
{
	bool operator()(int a, int b) const
	{
		return a*b==12;
	}
	bool operator()(int a, int b, int c) const
	{
		return a*b*c==12;
	}
};

void DemoWxDialog::OnPred1Fail(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_ASSERT(rb1_PRED(3, IsEven()));
}

void DemoWxDialog::OnPred2Fail(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_ASSERT(rb2_PRED(3, 5, ProductIs12()));
}

void DemoWxDialog::OnPred3Fail(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_ASSERT(rb3_PRED(3, 3, 2, ProductIs12()));
}

void DemoWxDialog::OnAnd(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_ASSERT(rbAND(rbEQUAL(2,1), rbEQUAL(2,3)));
}

static bool TestWithOptional()
{
	MOD_ASSERT_O(return false, "return false", rbEQUAL(3, 2));

	return true;
}

void DemoWxDialog::OnFailWithOptional(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert("\nThis will have an optional action called 'return false'");

	if (!TestWithOptional())
		wxMessageBox("'return false' was chosen");
}

ModAssert::Group<ModAssert::ReportFailure> group1("group 1"), group2("group 2");

void DemoWxDialog::OnFailWithGroup(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G(group1);
}

void DemoWxDialog::OnFailWithTwoGroups(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G(group1 && group2);
}

void DemoWxDialog::OnFailWithLevelWarning(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Warning);
}

void DemoWxDialog::OnFailWithOneGroupAndLevelWarning(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G(group1 % ModAssert::Warning);
}

void DemoWxDialog::OnFailWithTwoGroupsAndLevelWarning(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G((group1&&group2) % ModAssert::Warning);
}

void DemoWxDialog::OnFailWithLevelFatal(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Fatal);
}

static bool TestWithCheck()
{
	MOD_CHECK(rbEQUAL(3, 2), return false);

	return true;
}

void DemoWxDialog::OnCheckAndReturnFalse(wxCommandEvent& WXUNUSED(event))
{
	OnFailingCheck("\nThis will return false.");
	if (!TestWithCheck())
		wxMessageBox("false was returned");
}

void DemoWxDialog::OnDisplaySuccess(wxCommandEvent& WXUNUSED(event))
{
#if MOD_ASSERT_REPORTS
	wxMessageBox("Now comes a succeeding assertion,\n"
		"but ModAssert::IfSuccess is added to the group,\n"
		"so the dialog box will be shown\n"
		"(unless this assertion is turned off)\n");
#else
	wxMessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif

	int a=2;
	MOD_ASSERT_G(ModAssert::IfSuccess, rbEQUAL(a,2));
}

void DemoWxDialog::OnDisplayReportAll(wxCommandEvent& WXUNUSED(event))
{
#if MOD_ASSERT_REPORTS
	wxMessageBox("Now comes a succeeding and a failing assertion,\n"
		"but an object of the type ModAssert::ReportAll\n"
		"is added to the group,\n"
		"so the dialog box will be shown for both\n"
		"(unless this assertion is turned off)\n");
#else
	wxMessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif

	// made static, so that requests to stop displaying it are remembered
	static ModAssert::Group<ModAssert::ReportAll> reportAll("group");

	int a=2;
	MOD_ASSERT_G(reportAll, rbEQUAL(a,2));
	MOD_ASSERT_G(reportAll, rbEQUAL(a,3));
}

void DemoWxDialog::OnModVerifyV(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert();

	int a=2;
	int rv = MOD_VERIFY_V(rbvEQUAL(a,3));
	wxMessageBox(RichBool::ToString(rv)+" was returned");
}


class FailingThread: public wxThread
{
public:
	virtual ExitCode Entry()
	{
		// This function is called in another thread.
		// Because a dialog box can only be shown from the GUI-thread,
		// the assertion dialog box will not be shown here,
		// and the program will automatically break into the debugger.
		int a=6, b=3;
		MOD_ASSERT_P(a << b, rbEQUAL(a+b, 10));
		return 0;
	}
};

void DemoWxDialog::OnFailInOtherThread(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert("\nThis will happen in another thread, so no dialog can be shown\n"
		"but in debug mode it will automatically break and log the information");

	FailingThread *t = new FailingThread;
	t->Create();
	t->Run();
}

void DemoWxDialog::OnWxAssert(wxCommandEvent& WXUNUSED(event))
{
	OnFailingWxAssert();
	//wxASSERT_MSG(false, "A failing wxASSERT_MSG");
	wxASSERT(false);
}

static bool InspectA(int a)
{
	MOD_ASSERT_O(return false, "return false", a==1);
	return true;
}

void DemoWxDialog::OnOptional(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert("\nThis will have an optional action");
	bool b = InspectA(0);
	wxMessageBox(b ? "true was returned" : "false was returned");
}

void DemoWxDialog::OnSysError(wxCommandEvent& WXUNUSED(event))
{
	OnFailingAssert("\nThis will display the return value of\n"
		"wxSysErrorCode and wxSysErrorMsg");
	
	int err = wxSysErrorCode();
	wxFile file("nonexistent.txt");
	err = wxSysErrorCode();
	MOD_FAIL;
}

void DemoWxDialog::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Destroy();
}

void DemoWxDialog::OnQuit(wxCloseEvent& WXUNUSED(event))
{
	Destroy();
}
