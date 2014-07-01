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


// include this file to use the modular assertions
#include "modassert/assert.hpp"

// include this files to use basic rich booleans
#include "richbool/richbool.hpp"

// include this file to use rich booleans for std::strings
#include "richbool/stdstring.hpp"

// include this file to use rich booleans for containers
#include "richbool/containers.hpp"

// include this file to use rich booleans for MFC exceptions
#include "richbool/mfcexceptions.hpp"


#include <list>



// This is only needed for ModAssert::GetMode(); normally you don't need this
// in source files that don't setup ModAssert.
#include "modassert/handler.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg dialog

CDemoMFCDlg::CDemoMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoMFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoMFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EQUAL_INT, OnEqualInt)
	ON_BN_CLICKED(IDC_DIFF_INT, OnDiffInt)
	ON_BN_CLICKED(IDC_EQUAL_INT_WITH_DATA, OnEqualIntWithData)
	ON_BN_CLICKED(IDC_DIFF_INT_WITH_DATA, OnDiffIntWithData)
	ON_BN_CLICKED(IDC_EQUAL_STRING, OnEqualString)
	ON_BN_CLICKED(IDC_DIFF_STRING, OnDiffString)
	ON_BN_CLICKED(IDC_EQUAL_STRING_WITH_ESCAPE, OnEqualStringWithEscape)
	ON_BN_CLICKED(IDC_DIFF_STRING_WITH_ESCAPE, OnDiffStringWithEscape)
	ON_BN_CLICKED(IDC_EQUAL_VECTOR, OnEqualVector)
	ON_BN_CLICKED(IDC_DIFF_VECTOR, OnDiffVector)
	ON_BN_CLICKED(IDC_EQUAL_VECTOR_AND_LIST, OnEqualVectorAndList)
	ON_BN_CLICKED(IDC_DIFF_VECTOR_AND_LIST, OnDiffVectorAndList)
	ON_BN_CLICKED(IDC_DIFF_VECTOR_VECTOR, OnDiffVectorVector)
	ON_BN_CLICKED(IDC_DIFF_FAIL_LESS_VECTOR, OnDiffFailLessVector)
	ON_BN_CLICKED(IDC_DIFF_FAIL_PRED_1, OnDiffFailPred1)
	ON_BN_CLICKED(IDC_DIFF_FAIL_PRED_2, OnDiffFailPred2)
	ON_BN_CLICKED(IDC_DIFF_FAIL_PRED_3, OnDiffFailPred3)
	ON_BN_CLICKED(IDC_FAIL_WITH_OPTIONAL, OnFailWithOptional)
	ON_BN_CLICKED(IDC_AND, OnAnd)
	ON_BN_CLICKED(IDC_FAIL_WITH_GROUP, OnFailWithGroup)
	ON_BN_CLICKED(IDC_FAIL_WITH_TWO_GROUPS, OnFailWithTwoGroups)
	ON_BN_CLICKED(IDC_FAIL_WITH_LEVEL_WARNING, OnFailWithLevelWarning)
	ON_BN_CLICKED(IDC_FAIL_LEVEL_FATAL, OnFailWithLevelFatal)
	ON_BN_CLICKED(IDC_FAIL_WITH_ONE_GROUP_AND_LEVEL_WARNING ,OnFailWithGroupAndWarning)
	ON_BN_CLICKED(IDC_FAIL_TWO_GROUPS_AND_LEVEL_WARNING, OnFailWithTwoGroupsAndWarning)
	ON_BN_CLICKED(IDC_FAIL_IN_OTHER_THREAD, OnFailInOtherThread)
	ON_BN_CLICKED(IDC_CHECK_AND_THROW, OnCheckAndThrow)
	ON_BN_CLICKED(IDC_SUCCESS, OnSuccess)
	ON_BN_CLICKED(IDC_REPORT_ALL, OnReportAll)
	ON_BN_CLICKED(IDC_GETLASTERROR, OnGetlasterror)
	ON_BN_CLICKED(IDC_FAIL_IN_OTHER_FILE, OnFailInOtherFile)
	ON_BN_CLICKED(IDC_MOD_VERIFY_V, OnVerifyV)
	ON_BN_CLICKED(IDC_MFC_EXCEPTION, OnMFCException)
	ON_BN_CLICKED(IDC_NO_TEXT, OnNoText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg message handlers

BOOL CDemoMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CDemoMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoMFCDlg::OnSucceedingAssert()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding assertion,\n"
		"so no message will be shown");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown");
#endif
}

void CDemoMFCDlg::OnFailingAssert(const CString &extra)
{
#if MOD_ASSERT_REPORTS
	CString str = "Reporting of assertions is enabled at compile time,\n";
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		str += "and SetupForWin32(testMode) was called\n"
			"so a message will be shown\n"
			"unless this or all assertions are ignored"+extra;
		break;
	case ModAssert::continueSilentlyOnFailure:
		str += "and SetupForWin32(continueSilentlyOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::continueWithWarningOnFailure:
		str += "and SetupForWin32(continueWithWarningOnFailure) was called\n"
			"so the application will continue with a warning, unless the level is too low.";
		break;
	case ModAssert::terminateOnFailure:
		str += "and SetupForWin32(terminateOnFailure) was called\n"
			"so the application will terminate, unless the level is too low.";
		break;
	}
	MessageBox(str);
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}

void CDemoMFCDlg::OnFailingCheck(const CString &extra)
{
#if MOD_CHECK_REPORTS
	CString str = "Reporting of checks is enabled at compile time,\n";
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		str += "and SetupForWin32(testMode) was called\n"
			"so a message will be shown\n"
			"unless this or all checks are ignored"+extra;
		break;
	case ModAssert::continueSilentlyOnFailure:
		str += "and SetupForWin32(continueSilentlyOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::continueWithWarningOnFailure:
		str += "and SetupForWin32(continueWithWarningOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	case ModAssert::terminateOnFailure:
		str += "and SetupForWin32(terminateOnFailure) was called\n"
			"so the application will silently continue.";
		break;
	}
	MessageBox(str);
#else
	MessageBox("Reporting of checks is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}

void CDemoMFCDlg::OnEqualInt() 
{
	OnSucceedingAssert();

	int a=1, b=1;
	MOD_ASSERT(rbEQUAL(a, b));
}

void CDemoMFCDlg::OnDiffInt() 
{
	OnFailingAssert();

	int a=1, b=2;
	MOD_ASSERT(rbEQUAL(a, b));
}

void CDemoMFCDlg::OnEqualIntWithData() 
{
	OnSucceedingAssert();

	int a=3, b=2, c=4, d=3;
	MOD_ASSERT_P(a<<b<<c<<d, rbEQUAL(a+d, b+c));
}

void CDemoMFCDlg::OnDiffIntWithData() 
{
	OnFailingAssert();

	int a=3, b=2, c=5, d=1;
	MOD_ASSERT_P(a<<b<<c<<d, rbEQUAL(a+b, c+d));
}

void CDemoMFCDlg::OnEqualString() 
{
	OnSucceedingAssert();

	MOD_ASSERT(rbSTRCMP("abcde", ==, "abcde"));
}

void CDemoMFCDlg::OnDiffString() 
{
	OnFailingAssert();

	MOD_ASSERT(rbSTRCMP("abcde", ==, "abce"));
}

void CDemoMFCDlg::OnEqualStringWithEscape() 
{
	OnSucceedingAssert();

	MOD_ASSERT(rbSTRCMP("a\\bc\r", ==, "a\\bc\r"));
}

void CDemoMFCDlg::OnDiffStringWithEscape() 
{
	OnFailingAssert();

	MOD_ASSERT(rbSTRCMP("a\\bc\r", ==, "a\\bc\n"));
}

void CDemoMFCDlg::OnEqualVector() 
{
	OnSucceedingAssert();

	std::vector<int> vec1, vec2;

	vec1.push_back(1);   vec2.push_back(1);
	vec1.push_back(3);   vec2.push_back(3);
	vec1.push_back(100); vec2.push_back(100);

	MOD_ASSERT(rbIN_CONTAINERS(vec1, vec2, RichBool::AllEqual<>(true)));
}

void CDemoMFCDlg::OnDiffVector() 
{
	OnFailingAssert();

	std::vector<int> vec1, vec2;

	vec1.push_back(1);   vec2.push_back(1);
	vec1.push_back(5); 
	vec1.push_back(3);   vec2.push_back(3);
	vec1.push_back(6);   vec2.push_back(8);
	vec1.push_back(100); vec2.push_back(100);
	                     vec2.push_back(1);

	MOD_ASSERT(rbIN_CONTAINERS(vec1, vec2, RichBool::AllEqual<>(true)));
}

void CDemoMFCDlg::OnEqualVectorAndList() 
{
	OnSucceedingAssert();

	std::vector<int> vec;
	std::list<int> list;

	vec.push_back(1);   list.push_back(1);
	vec.push_back(3);   list.push_back(3);
	vec.push_back(100); list.push_back(100);

	MOD_ASSERT(rbIN_CONTAINERS(vec, list, RichBool::AllEqual<>(true)));
}

void CDemoMFCDlg::OnDiffVectorAndList() 
{
	OnFailingAssert();

	std::vector<int> vec;
	std::list<int> list;

	vec.push_back(1);   list.push_back(1);
	vec.push_back(5); 
	vec.push_back(3);   list.push_back(3);
	vec.push_back(6);   list.push_back(8);
	vec.push_back(100); list.push_back(100);
	                    list.push_back(1);

	MOD_ASSERT(rbIN_CONTAINERS(vec, list, RichBool::AllEqual<>(true)));
}

void CDemoMFCDlg::OnDiffVectorVector() 
{
	OnFailingAssert();

	std::vector<std::vector<int> > arr1, arr2;

	std::vector<int> a, a1, a2, a12;
	a1.push_back(1);
	a2.push_back(2);
	a12.push_back(1);
	a12.push_back(2);

	arr1.push_back(a);   arr2.push_back(a);
	arr1.push_back(a1);
	arr1.push_back(a2);  arr2.push_back(a12);

	MOD_ASSERT(
		rbIN_CONTAINERS(arr1, arr2,
			RichBool::Compare<>(true).That(RichBool::ContainersEqual<>(true)))
	);
}

void CDemoMFCDlg::OnDiffFailLessVector() 
{
	OnFailingAssert();

	std::vector<int> vec1, vec2;
	
	vec1.push_back(1); vec2.push_back(2);
	vec1.push_back(3); vec2.push_back(6);
	vec1.push_back(5); vec2.push_back(4); // intentional error
	vec1.push_back(6); vec2.push_back(8);

	MOD_ASSERT(
		rbIN_CONTAINERS(vec1, vec2,
			RichBool::Compare<>(true).That(RichBool::Less<>()))
	);
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
public:
	bool operator()(int a, int b) const
	{
		return a*b==12;
	}
	bool operator()(int a, int b, int c) const
	{
		return a*b*c==12;
	}
};

void CDemoMFCDlg::OnDiffFailPred1() 
{
	OnFailingAssert();

	MOD_ASSERT(rb1_PRED(3, IsEven()));
}

void CDemoMFCDlg::OnDiffFailPred2() 
{
	OnFailingAssert();

	MOD_ASSERT(rb2_PRED(3, 5, ProductIs12()));
}

void CDemoMFCDlg::OnDiffFailPred3() 
{
	OnFailingAssert();

	MOD_ASSERT(rb3_PRED(3, 3, 2, ProductIs12()));
}

void CDemoMFCDlg::OnFailWithOptional() 
{
	OnFailingAssert("\nThis will have an optional action called Throw");

	try
	{
		int a = 5;
		MOD_ASSERT_O(throw 1, "Throw", rbEQUAL(10, a));
		MessageBox("No exception thrown");
	}
	catch (int)
	{
		MessageBox("Exception was thrown");
	}
}

void CDemoMFCDlg::OnCheckAndThrow() 
{
	OnFailingCheck("\nThis will throw an exception");

	try
	{
		int a = 5;
		MOD_CHECK(rbEQUAL(10, a), throw 1);
		MessageBox("Error: no exception thrown!!");
	}
	catch (int)
	{
		MessageBox("Exception was thrown");
	}
}

void CDemoMFCDlg::OnAnd() 
{
	OnFailingAssert();

	MOD_ASSERT(rbAND(rbEQUAL(2,1), rbEQUAL(2,3)));
}

ModAssert::Group<ModAssert::ReportFailure> group1("group 1"), group2("group 2");

void CDemoMFCDlg::OnFailWithGroup()
{
	OnFailingAssert();

	MOD_FAIL_G(group1);
}

void CDemoMFCDlg::OnFailWithTwoGroups()
{
	OnFailingAssert();

	MOD_FAIL_G(group1 && group2);
}

void CDemoMFCDlg::OnFailWithLevelWarning()
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Warning);
}

void CDemoMFCDlg::OnFailWithLevelFatal()
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Fatal);
}

void CDemoMFCDlg::OnFailWithGroupAndWarning()
{
	OnFailingAssert();

	MOD_FAIL_G(group1 % ModAssert::Warning);
}

void CDemoMFCDlg::OnVerifyV()
{
	OnFailingAssert();

	MOD_VERIFY_V(rbvEQUAL(1+2,4));
}

void CDemoMFCDlg::OnFailWithTwoGroupsAndWarning()
{
	OnFailingAssert();

	MOD_FAIL_G( (group1 && group2) % ModAssert::Warning);
}

static DWORD WINAPI FailingFunction(LPVOID /*lpParameter*/)
{
	// This function is called in another thread.
	// Because a dialog box can only be shown from the GUI-thread,
	// the assertion dialog box will not be shown here,
	// and the program will automatically break into the debugger.
	int a=6, b=3;
	MOD_ASSERT_P(a << b, rbEQUAL(a+b, 10));
	return 0;
}

void CDemoMFCDlg::OnFailInOtherThread() 
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a failing assertion,\n"
		"but this will occur in another thread,\n"
		"so no dialog box will be shown.\n"
		"Instead the program will directly break into the debugger\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif
	CreateThread(0, 0, FailingFunction, 0, 0, 0);
}

void CDemoMFCDlg::OnSuccess() 
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding assertion,\n"
		"but ModAssert::IfSuccess is added to the group,\n"
		"so the dialog box will be shown\n"
		"(unless this assertion is turned off)\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif
	
	int a=1;
	MOD_ASSERT_G(ModAssert::IfSuccess, rbEQUAL(a,1));
}

void CDemoMFCDlg::OnReportAll() 
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding and a failing assertion,\n"
		"but an object of the type ModAssert::ReportAll\n"
		"is added to the group,\n"
		"so the dialog box will be shown for both\n"
		"(unless this assertion is turned off)\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif

	// made static, so that requests to stop displaying it are remembered:
	static ModAssert::Group<ModAssert::ReportAll> reportAll("group");

	int a=2;
	MOD_ASSERT_G(reportAll, rbEQUAL(a,2));
	MOD_ASSERT_G(reportAll, rbEQUAL(a,3));
}

void CDemoMFCDlg::OnGetlasterror() 
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a failing assertion,\n"
		"that will show the return value of GetLastError,\n"
		"unless this or all assertions are disabled.");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif

	CFile file;
	file.Open("nofile.ext", CFile::modeRead);

	MOD_FAIL;
}

extern void FailInOtherFile();

void CDemoMFCDlg::OnFailInOtherFile()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a failing assertion, that is in another file,\n"
		"unless this or all assertions are disabled.\n"
		"Use this to test the feature 'Stop displaying assertions -> In this file'.");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\nso no message will be shown");
#endif
	FailInOtherFile();
}

void CDemoMFCDlg::OnMFCException()
{
	try
	{
		AfxThrowMemoryException();
	}
	catch (CMemoryException *exc)
	{
		MOD_ASSERT(rbEXCEPTION(*exc));
	}
}
