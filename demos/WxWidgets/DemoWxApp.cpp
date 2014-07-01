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

#include "DemoWxApp.h"
#include "DemoWxDlg.h"
#include "modassert/wxhandler.hpp"
#include "modassert/wxdisplayer.hpp"
#include "modassert/assert.hpp"
#include "modassert/handler.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/appinfo.hpp"
#include "modassert/infostore.hpp"


IMPLEMENT_APP(DemoWxApp)

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

DemoWxApp::DemoWxApp()
{
}

DemoWxApp::~DemoWxApp()
{
}

struct MyException
{};

void ThrowException()
{
	throw MyException();
}

void SetupModAssert()
{
	// Optionally add those two lines to have the name of the
	// application logged to all loggers.
	// Do this before calling ModAssert::SetupForWxWidgets(), so that
	// the loggers can use this infoprovider.
	// Note that it is static, because OnInit returns as soon as the dialog is shown.
	static InfoProviders::ApplicationInfoProvider appInfo("wxDemo");
	ModAssert::AddInfoProvider(&appInfo);

	// This has to be called to make sure that assertions are shown
	// in a dialog (in debug versions) and logged with wxLogDebug.
	// Do this before adding your own loggers, so that the infoproviders
	// are used when a beginmessage is logged to those loggers.
	// In release versions the application will terminate if an
	// assertion fails (not if it is a check), if MOD_ASSERT_REPORT
	// is defined (as is the case for this demo).
	ModAssert::SetupForWxWidgets();

	// Alternatively you can call one of the following,
	// to specify what ModAssert should do if an assertion fails
	// (this makes it independent of whether it is a debug or release version)

	// ask for response if an assertion or check fails:
	//ModAssert::SetupForWxWidgets(ModAssert::testMode);

	// continue silently if an assertion fails:
	//ModAssert::SetupForWxWidgets(ModAssert::continueSilentlyOnFailure);

	// continue with a warning if an assertion fails:
	//ModAssert::SetupForWxWidgets(ModAssert::continueWithWarningOnFailure);

	// terminate if an assertion fails (checks are ignored):
	//ModAssert::SetupForWxWidgets(ModAssert::terminateOnFailure);

	// If you called ModAssert::SetupForWxWidgets(ModAssert::terminateOnFailure)
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

	// Optionally you can add those two lines, to have the assertion
	// data logged to a file. Note that logger is static, because
	// OnInit returns as soon as the dialog is shown.
	static ModAssert::AppendToFileLogger logger("demo.log");
	ModAssert::AddLogger(&logger);

	// Optionally you can add those two lines, to let the user log the
	// assertion data to the file extra.log if he/she chooses to:
	static ModAssert::AppendToFileLogger optionalLogger("extra.log");
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

bool DemoWxApp::OnInit()
{
	SetupModAssert();

    DemoWxDialog *dialog = new DemoWxDialog(_("ModAssert Demo for WxWidgets"),
                                 wxPoint(50, 50), wxSize(430, 285));

    dialog->Show(TRUE);
	SetTopWindow(dialog);

    return TRUE;
}

int DemoWxApp::OnExit()
{
	// Add this line to make sure that ModAssert exits
	// gracefully when the application ends.
	// This will actually be done from the destructor of this object.
	ModAssert::AutoShutdown modAssertAutoShutdown;

	return wxApp::OnExit();
}


// overriding this method reroutes wxWidgets assertions to ModAssert:
// (in older versions of wxWidgets you need 
//  OnAssert(const wxChar *file, int line, const wxChar *cond, const wxChar *msg) )

void DemoWxApp::OnAssertFailure(const wxChar *file, int line, const char *func,
						 const wxChar *cond, const wxChar *msg)
{
	ModAssert::ParameterList parList;
	if (msg)
		parList.AddMessage(msg);
	ModAssert::Response response = ModAssert::HandleAssert(
		false, // wxASSERT a.o. only call the handler if they fail
		false, // here we have to make a guess for isCheck!!
		ModAssert::Context(file, line, func),
		cond,
		NULL, // no analysis
		&parList,
		ModAssert::MakeGroupList(ModAssert::Error),
		NULL, // no optional action
		NULL  // no displayThis
		);

	if (response&ModAssert::BreakIntoDebugger)
	{
		// move back three calls in the call stack
		// to see the assertion that failed
		MOD_ASSERT_BREAK_HERE;
	}
	if (response&ModAssert::Exit)
		exit(1);
}
