//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

// DemoWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#include "commctrl.h"
#include "Examples.h"
#include "resource.h"
#include "modassert/Win32Handler.hpp"
#include "modassert/Win32Displayer.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/handler.hpp"
#include "modassert/appinfo.hpp"
#include "modassert/infostore.hpp"

static HINSTANCE hAppInstance = 0;

BOOL CALLBACK MainDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM )
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			// set icon
			LPCSTR szIcon = MAKEINTRESOURCE(IDR_MAINFRAME);
			HICON hIcon = LoadIcon(hAppInstance, szIcon);
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		return FALSE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hDlg, TRUE);
			break;
		case IDC_EQUAL_INT:
			OnEqualInt();
			break;
		case IDC_DIFF_INT:
			OnDiffInt();
			break;
		case IDC_EQUAL_INT_WITH_DATA:
			OnEqualIntWithData();
			break;
		case IDC_DIFF_INT_WITH_DATA:
			OnDiffIntWithData();
			break;
		case IDC_EQUAL_STRING:
			OnEqualString();
			break;
		case IDC_DIFF_STRING:
			OnDiffString();
			break;
		case IDC_EQUAL_STRING_WITH_ESCAPE:
			OnEqualStringWithEscape();
			break;
		case IDC_DIFF_STRING_WITH_ESCAPE:
			OnDiffStringWithEscape();
			break;
		case IDC_EQUAL_VECTOR:
			OnEqualVector();
			break;
		case IDC_DIFF_VECTOR:
			OnDiffVector();
			break;
		case IDC_EQUAL_VECTOR_AND_LIST:
			OnEqualVectorAndList();
			break;
		case IDC_DIFF_VECTOR_AND_LIST:
			OnDiffVectorAndList();
			break;
		case IDC_DIFF_VECTOR_VECTOR:
			OnDiffVectorVector();
			break;
		case IDC_DIFF_FAIL_LESS_VECTOR:
			OnDiffFailLessVector();
			break;
		case IDC_DIFF_FAIL_PRED_1:
			OnDiffFailPred1();
			break;
		case IDC_DIFF_FAIL_PRED_2:
			OnDiffFailPred2();
			break;
		case IDC_DIFF_FAIL_PRED_3:
			OnDiffFailPred3();
			break;
		case IDC_FAIL_WITH_OPTIONAL:
			OnFailWithOptional();
			break;
		case IDC_AND:
			OnAnd();
			break;
		case IDC_FAIL_WITH_GROUP:
			OnFailWithGroup();
			break;
		case IDC_FAIL_WITH_TWO_GROUPS:
			OnFailWithTwoGroups();
			break;
		case IDC_FAIL_WITH_LEVEL_WARNING:
			OnFailWithLevelWarning();
			break;
		case IDC_FAIL_LEVEL_FATAL:
			OnFailWithLevelFatal();
			break;
		case IDC_FAIL_WITH_ONE_GROUP_AND_LEVEL_WARNING:
			OnFailWithOneGroupAndLevelWarning();
			break;
		case IDC_FAIL_TWO_GROUPS_AND_LEVEL_WARNING:
			OnFailWithTwoGroupsAndLevelWarning();
			break;
		case IDC_FAIL_IN_OTHER_THREAD:
			OnFailInOtherThread();
			break;
		case IDC_CHECK_AND_THROW:
			OnCheckAndThrow();
			break;
		case IDC_SUCCESS:
			OnSuccess();
			break;
		case IDC_REPORT_ALL:
			OnReportAll();
			break;
		case IDC_GETLASTERROR:
			OnGetlasterror();
			break;
		case IDC_FAIL_IN_OTHER_FILE:
			OnFailInOtherFile();
			break;
		case IDC_VERIFY_V:
			OnVerifyV();
			break;
		case IDC_NO_TEXT:
			OnNoText();
			break;
		default:
			return FALSE;
		};
		return TRUE;
	case WM_QUIT:
	case WM_CLOSE:
		EndDialog(hDlg, TRUE);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return MainDlg(hDlg, msg, wParam, lParam);
}

struct MyException
{};

void ThrowException()
{
	throw MyException();
}

// Define these objects before the ModAssert::AutoShutdown
// object is created.
// Here this is assured by making them global.
ModAssert::AppendToFileLogger logger("demo.log");
ModAssert::AppendToFileLogger optionalLogger("extra.log");
InfoProviders::ApplicationInfoProvider appInfo("DemoWin32");

void SetupModAssert(HINSTANCE hInstance)
{
	// Optionally you can add this line, to have the name of the application
	// included in the loggers. Do this before calling ModAssert::SetupForWin32
	// or adding a logger, so it is used in all the loggers.
	ModAssert::AddInfoProvider(&appInfo);

	// When an assertion or check is reported, the amount of free
	// disk space on all local drives is added. And the begin of
	// logfiles will have more useful information about the local drives.
	// Uncomment next line if you also want info about remote drives.
	// It should be called before ModAssert::SetupForWin32.
	// Note that this may slow down your application.
	ModAssert::SetUseRemoteDrives(true);

	// This has to be called to make sure that assertions are shown
	// in a dialog (in debug versions) and streamed to the output window.
	// In release versions the application will
	// only log failed assertions and checks, not show them.
	//ModAssert::SetupForWin32(hInstance);

	// Alternatively you can call one of the following,
	// to specify what ModAssert should do if an assertion fails
	// (this makes it independent of whether it is a debug or release version).

	// ask for response if an assertion or check fails:
	ModAssert::SetupForWin32(hInstance, ModAssert::testMode);

	// continue if silently an assertion fails:
	//ModAssert::SetupForWin32(hInstance, ModAssert::continueSilentlyOnFailure);

	// continue with a warning if an assertion fails (checks are ignored):
	//ModAssert::SetupForWin32(hInstance, ModAssert::continueWithWarningOnFailure);

	// terminate if an assertion fails (checks are ignored):
	//ModAssert::SetupForWin32(hInstance, ModAssert::terminateOnFailure);

	// If you called ModAssert::SetupForWin32(ModAssert::terminateOnFailure)
	// the application will terminate
	// if an assertion fails of level Fatal or higher
	// and reporting of assertions is enabled.
	// Optionally uncomment next line to have the application
	// terminated also if the level is Error.
	ModAssert::SetMinimumTerminateLevel(ModAssert::Error);

	// Optionally you can set the text of the warning message and
	// terminate message:
	if (ModAssert::GetWarningMessage())
		ModAssert::GetWarningMessage()->SetText(
		"An error occurred. Save your work and exit the application.\n"
		"Please send the file demo.log back to us");
	if (ModAssert::GetTerminateMessage())
		ModAssert::GetTerminateMessage()->SetText(
			"Application will terminate due to an error\n"
			"Please send the file demo.log back to us");

	// Optionally you can add this line, to have the assertion
	// data logged to a file:
	ModAssert::AddLogger(&logger);

	// Optionally you can add this line, to let the user log the
	// assertion data to the file extra.log if he/she chooses to:
	ModAssert::SetOptionalLogger(&optionalLogger, "Add to extra.log");

	// Optionally set this global optional action:
	ModAssert::SetGlobalOptionalAction(ThrowException, "Throw exception");

	// Optionally uncomment one or more of these lines to disallow
	// the Debug, Optional, GlobalOptional and Exit action in the assertion dialog:
	//ModAssert::SetAllowBreakIntoDebugger(false);
	//ModAssert::SetAllowOptional(false);
	//ModAssert::SetAllowGlobalOptional(false);
	//ModAssert::SetAllowExit(false);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE ,
                     LPSTR     ,
                     int       )
{
	// some necessary stuff to use listcontrol in Windows XP:
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);


	// Add this line before adding a logger or setting a responder,
	// to make sure that ModAssert exits gracefully when the application ends.
	ModAssert::AutoShutdown modAssertAutoShutdown;

	// This function sets up ModAssert:
	SetupModAssert(hInstance);


	hAppInstance = hInstance;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MOD_ASSERTDEMOWIN32_DIALOG),
		(HWND)NULL, MainDlg);

	return 0;
}
