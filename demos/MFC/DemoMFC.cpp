//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

// DemoMFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DemoMFC.h"
#include "DemoMFCDlg.h"

#include "modassert/handler.hpp"
#include "modassert/Win32Handler.hpp"
#include "modassert/Win32Displayer.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/appinfo.hpp"
#include "modassert/infostore.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCApp

BEGIN_MESSAGE_MAP(CDemoMFCApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoMFCApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CDemoMFCApp::CDemoMFCApp()
{
}

CDemoMFCApp theApp;


struct MyException
{};

void ThrowException()
{
	throw MyException();
}

// These objects have to be defined before the ModAssert::AutoShutdown object.
// Here this is assured by making them global.
ModAssert::AppendToFileLogger logger("demo.log");
ModAssert::AppendToFileLogger optionalLogger("extra.log");
InfoProviders::ApplicationInfoProvider appInfo("DemoMFC");

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
	//ModAssert::SetUseRemoteDrives(true);

	// This has to be called to make sure that assertions are shown
	// in a dialog (in debug versions) and streamed to the output window.
	// In release versions the application will
	// only log failed assertions and checks, not show them.
	ModAssert::SetupForWin32(hInstance);

	// Alternatively you can call one of the following,
	// to specify what ModAssert should do if an assertion fails
	// (this makes it independent of whether it is a debug or release version).

	// ask for response if an assertion or check fails:
	//ModAssert::SetupForWin32(hInstance, ModAssert::testMode);

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
	//ModAssert::SetMinimumTerminateLevel(ModAssert::Error);

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

BOOL CDemoMFCApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	// Add this line preferably before adding a logger or setting a responder,
	// but definitely after creating the loggers, responder and infoproviders,
	// to make sure that ModAssert exits gracefully when the application ends.
	ModAssert::AutoShutdown modAssertAutoShutdown;

	// This function sets up ModAssert:
	SetupModAssert(m_hInstance);

	CDemoMFCDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
