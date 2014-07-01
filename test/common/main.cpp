//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "ModAssertTest.h"
#include "modassert/handler.hpp"
#include "stdio.h"

#ifdef RICHBOOL_USE_WX
#include <wx/app.h>
#endif

int RunTests(bool allowDebug)
{
#ifdef RICHBOOL_USE_WX
	::wxInitialize();
#endif

	SetAllowBreakIntoDebugger(allowDebug);

	if (MOD_ASSERT_REPORTS)
	    printf("Assertions are globally on\n");
	else
	    printf("Assertions are globally off\n");

	if (MOD_CHECK_REPORTS)
	    printf("Checks are globally on\n");
	else
	    printf("Checks are globally off\n");

	printf("%d tests\n", ModAssertTest::GetNrTests());


	ModAssert::AutoShutdown modAssertAutoShutdown;

	ModAssertTestHandler::Activate();

	ModAssertTest::RunTests();

	printf("%d meta-assertions\n", ModAssertTestHandler::GetNrMetaAsserts());
	printf("%d errors\n", ModAssertTestHandler::GetNrErrors());

	return ModAssertTestHandler::GetNrErrors();
}


#ifdef RICHBOOL_USE_WX

class TestApp: public wxApp
{
public:
	TestApp(): wxApp()
	{}

	virtual int OnRun()
	{
		return RunTests(false);
	}

#if MOD_ASSERT_REPORTS
	void OnAssertFailure(const wxChar *file, int line,
				  const wxChar *func, const wxChar *cond, const wxChar *msg)
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
			msg ? &parList : NULL,
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
#endif // #if MOD_ASSERT_REPORTS
} app;

IMPLEMENT_APP_NO_MAIN(TestApp)

#endif // #ifdef RICHBOOL_USE_WX

int main(int argc, char* argv[])
{
	bool allowDebug = (argc>1) && (strcmp(argv[1], "-d")==0);
	return RunTests(allowDebug);
}


