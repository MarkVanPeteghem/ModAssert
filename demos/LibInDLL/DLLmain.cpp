//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include <windows.h>

#include "export.hpp"
#include "modassert/assert.hpp"
#include "modassert/handler.hpp"
#include "richbool/richbool.hpp"

#include "modassert/consolehandler.hpp"
#include "modassert/consoledisplayer.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/appinfo.hpp"
#include "modassert/infostore.hpp"

struct MyException
{};

void ThrowException()
{
	throw MyException();
}

// These three objects should be defined
// before the ModAssert::AutoShutdown object.
// Here this is assured by making them global.
ModAssert::AppendToFileLogger logger("demo.log");
ModAssert::AppendToFileLogger optionalLogger("extra.log");
InfoProviders::ApplicationInfoProvider appInfo("DemoConsole");

DLL_API void SetupModAssert(bool debugAllowed)
{
	ModAssert::SetAllowBreakIntoDebugger(debugAllowed);

	// Optionally you can add this line, to have the name of the application
	// included in the loggers. Do this before calling ModAssert::SetupForConsole
	// or adding a logger, so it is used in all the loggers.
	ModAssert::AddInfoProvider(&appInfo);

	// This has to be called to make sure that assertions are logged to cerr,
	// and that a response is requested in debug versions.
	// In release versions the application will simply continue:
	ModAssert::SetupForConsole();

	// Alternatively you can call one of the following,
	// to specify what ModAssert should do if an assertion fails
	// (this makes it independent of whether it is a debug or release version)

	// ask for response if an assertion or check fails:
	//ModAssert::SetupForConsole(ModAssert::testMode);

	// continue silently if an assertion fails:
	//ModAssert::SetupForConsole(ModAssert::continueSilentlyOnFailure);

	// continue with a warning if an assertion fails:
	//ModAssert::SetupForConsole(ModAssert::continueWithWarningOnFailure);

	// terminate if an assertion fails (checks are ignored):
	//ModAssert::SetupForConsole(ModAssert::terminateOnFailure);

	// If you called ModAssert::SetupForConsole(ModAssert::terminateOnFailure)
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

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	// This function sets up ModAssert:
	//SetupModAssert(false);

	return TRUE;
}

DLL_API ModAssert::State *GetModAssertStateInDll()
{
	return ModAssert::GetState();
}
