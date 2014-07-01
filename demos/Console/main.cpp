//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "modassert/assert.hpp"
#include "modassert/handler.hpp"
#include "richbool/richbool.hpp"
#include "richbool/stdstring.hpp"
#include "richbool/containers.hpp"

#include "modassert/consolehandler.hpp"
#include "modassert/consoledisplayer.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/appinfo.hpp"
#include "modassert/infostore.hpp"



#include <iostream>
#include <vector>
#include <list>

void OnSucceedingAssert()
{
#if MOD_ASSERT_REPORTS
	std::cout
		<< "Now comes a succeeding assertion," << std::endl
		<< "so no message will be shown" << std::endl
		<< std::endl;
#else
	std::cout
		<< "Assertions are off," << std::endl
		<< "so no message will be shown" << std::endl
		<< std::endl;
#endif
}

void OnFailingAssert(const std::string &extra="")
{
#if MOD_ASSERT_REPORTS
	std::cout << "Reporting of assertions is enabled at compile time," << std::endl;
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		std::cout << "and SetUpForConsole(testMode) was called" << std::endl
			<< "so a message will be shown" << std::endl
			<< "unless this or all assertions are ignored"+extra << std::endl;
		break;
	case ModAssert::continueSilentlyOnFailure:
		std::cout << "and SetUpForConsole(continueSilentlyOnFailure) was called" << std::endl
			<< "so the application will silently continue." << std::endl;
		break;
	case ModAssert::continueWithWarningOnFailure:
		std::cout << "and SetUpForConsole(continueWithWarningOnFailure) was called" << std::endl
			<< "so the application will continue with a warning, unless the level is too low." << std::endl;
		break;
	case ModAssert::terminateOnFailure:
		std::cout << "and SetUpForConsole(terminateOnFailure) was called" << std::endl
			<< "so the application will terminate, unless the level is too low." << std::endl;
		break;
	}
	std::cout << std::endl;
#else
	std::cout
		<< "Reporting of assertions is disabled at compile time," << std::endl
		<< "so no message will be shown" << std::endl
		<< std::endl;
#endif
}

void OnFailingCheck(const std::string &extra="")
{
#if MOD_CHECK_REPORTS
	std::cout << "Reporting of checks is enabled at compile time," << std::endl;
	switch (ModAssert::GetMode())
	{
	case ModAssert::testMode:
		std::cout << "and SetUpForConsole(testMode) was called" << std::endl
			<< "so a message will be shown" << std::endl
			<< "unless this or all checks are ignored"+extra << std::endl;
		break;
	case ModAssert::continueSilentlyOnFailure:
		std::cout << "and SetUpForConsole(continueSilentlyOnFailure) was called" << std::endl
			<< "so the application will silently continue." << std::endl;
		break;
	case ModAssert::continueWithWarningOnFailure:
		std::cout << "and SetUpForConsole(continueWithWarningOnFailure) was called" << std::endl
			<< "so the application will silently continue." << std::endl;
		break;
	case ModAssert::terminateOnFailure:
		std::cout << "and SetUpForConsole(terminateOnFailure) was called" << std::endl
			<< "so the application will silently continue." << std::endl;
		break;
	}
	std::cout << std::endl;
#else
	std::cout
		<< "Reporting of checks is disabled at compile time," << std::endl
		<< "so no message will be shown" << std::endl
		<< std::endl;
#endif
}

ModAssert::Group<ModAssert::ReportFailure> modAssertGroup1("group 1"),
	modAssertGroup2("group 2");

void OnEqualInt()
{
	OnSucceedingAssert();

	int a = 5;
	MOD_ASSERT(rbEQUAL(5, a));
}

void OnDiffInt()
{
	OnFailingAssert();

	int a = 3;
	MOD_ASSERT(rbEQUAL(5, a));
}

void OnEqualIntWithData()
{
	OnSucceedingAssert();

	int a=0, b=1, c=2, d=3;
	MOD_ASSERT_P(a<<b<<c<<d, rbEQUAL(a+d, b+c));
}

void OnDiffIntWithData()
{
	OnFailingAssert();

	int a=0, b=1, c=2, d=3;
	MOD_ASSERT_P(a<<b<<c<<d, rbEQUAL(a+b, c+d));
}

void OnEqualString()
{
	OnSucceedingAssert();

	MOD_ASSERT(rbSTRCMP("abcde", ==, "abcde"));
}

void OnDiffString()
{
	OnFailingAssert();

	MOD_ASSERT(rbSTRCMP("abcde", ==, "abce"));
}

void OnEqualStringWithEscape()
{
	OnSucceedingAssert();

	MOD_ASSERT(rbSTRCMP("a\\bc\r", ==, "a\\bc\r"));
}

void OnDiffStringWithEscape()
{
	OnFailingAssert();

	MOD_ASSERT(rbSTRCMP("a\\bc\r", ==, "a\\bc\n"));
}

void OnEqualVector()
{
	OnSucceedingAssert();

	std::vector<int> vec1, vec2;

	vec1.push_back(1);   vec2.push_back(1);
	vec1.push_back(3);   vec2.push_back(3);
	vec1.push_back(100); vec2.push_back(100);

	MOD_ASSERT(rbIN_CONTAINERS(vec1, vec2, RichBool::AllEqual<>(true)));
}

void OnDiffVector()
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

void OnEqualVectorAndList()
{
	OnSucceedingAssert();

	std::vector<int> vec;
	std::list<int> list;

	vec.push_back(1);   list.push_back(1);
	vec.push_back(3);   list.push_back(3);
	vec.push_back(100); list.push_back(100);

	MOD_ASSERT(rbIN_CONTAINERS(vec, list, RichBool::AllEqual<>(true)));
}

void OnDiffVectorAndList()
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

void OnDiffVectorVector()
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

void OnDiffFailLessVector()
{
	OnFailingAssert();

	std::vector<int> vec1, vec2;

	vec1.push_back(1); vec2.push_back(2);
	vec1.push_back(3); vec2.push_back(6);
	vec1.push_back(5); vec2.push_back(4); // intentional error
	vec1.push_back(6); vec2.push_back(8);

	MOD_ASSERT(
		rbIN_CONTAINERS(vec1, vec2, RichBool::Compare<>(true).That(RichBool::Less<>()))
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
	bool operator()(int a, int b) const
	{
		return a*b==12;
	}
	bool operator()(int a, int b, int c) const
	{
		return a*b*c==12;
	}
};

void OnDiffFailPred1()
{
	OnFailingAssert();

	MOD_ASSERT(rb1_PRED(3, IsEven()));
}

void OnDiffFailPred2()
{
	OnFailingAssert();

	MOD_ASSERT(rb2_PRED(3, 5, ProductIs12()));
}

void OnDiffFailPred3()
{
	OnFailingAssert();

	MOD_ASSERT(rb3_PRED(3, 3, 2, ProductIs12()));
}

void OnFailWithOptional()
{
	OnFailingAssert("\nThis will have an optional action called Throw");

	try
	{
		int a = 5;
		MOD_ASSERT_O(throw 1, "Throw", rbEQUAL(10, a));
		std::cout << "No exception thrown" << std::endl;
	}
	catch (int)
	{
		std::cout << "Exception was thrown" << std::endl;
	}
}

void OnCheckAndThrow()
{
	OnFailingCheck("\nThis will throw an exception");

	try
	{
		int a = 5;
		MOD_CHECK(rbEQUAL(10, a), throw 1);
		std::cout << "Error: no exception thrown!!" << std::endl;
	}
	catch (int)
	{
		std::cout << "Exception was thrown" << std::endl;
	}
}

void OnAnd()
{
	OnFailingAssert();

	MOD_ASSERT(rbAND(rbEQUAL(2,1), rbEQUAL(2,3)));
}

void OnFailLevelWarning()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G(ModAssert::Warning, rbEQUAL(10, a));
}

void OnFailLevelFatal()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G(ModAssert::Fatal, rbEQUAL(10, a));
}

void OnFailGroup1()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G(modAssertGroup1, rbEQUAL(10, a));
}

void OnFailGroup1AndGroup2()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G(modAssertGroup1&&modAssertGroup2, rbEQUAL(10, a));
}

void OnFailWith1GroupAndWarning()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G(modAssertGroup1%ModAssert::Warning, rbEQUAL(10, a));
}

void OnFailWith2GroupsAndWarning()
{
	OnFailingAssert();

	int a = 5;
	MOD_ASSERT_G((modAssertGroup1&&modAssertGroup2)%ModAssert::Warning, rbEQUAL(10, a));
}

void OnDisplaySuccess()
{
#if MOD_ASSERT_REPORTS
	std::cout
		<< "Now comes a succeeding assertion," << std::endl
		<< "with ModAssert::IfSuccess in its group," << std::endl
		<< "so a message will be shown" << std::endl
		<< "unless this or all assertions are ignored" << std::endl
		<< std::endl;
#else
	std::cout
		<< "Assertions are off," << std::endl
		<< "so no message will be shown" << std::endl
		<< std::endl;
#endif

	int a = 5;
	MOD_ASSERT_G(ModAssert::IfSuccess, rbEQUAL(5, a));
}

void OnVerifyV()
{
#if MOD_ASSERT_REPORTS
	std::cout
		<< "Now comes a verify macro that returns a value" << std::endl
		<< std::endl;
#else
	std::cout
		<< "Assertions are off," << std::endl
		<< "so no message will be shown for this verify macro," << std::endl
		<< "but the return will still be calculated," << std::endl
		<< std::endl;
#endif

	int a = 5;
	int b = MOD_VERIFY_V(rbvEQUAL(a+2,8));
	std::cout << b << " was returned" << std::endl << std::endl;
}

void OnFailInOtherFile(); // defined in otherfile.cpp
void OnNoText(); // defined in NoText.cpp


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

void SetupModAssert(bool debugAllowed)
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

int main(int argc, char* argv[])
{
	// If the argument -d is given as an argument,
	// we allow breaking into the debugger. We then provide this argument
	// whenever we launch this application with a debugger, without otherwise.
	bool debugAllowed=false;
	for (int arg=1; arg<argc; ++arg)
	{
		if (strcmp(argv[arg], "-d")==0)
		{
			debugAllowed = true;
			break;
		}
	}

	// Add this line preferably before adding a logger or setting a responder,
	// but definitely after creating the loggers, responder and infoproviders,
	// to make sure that ModAssert exits gracefully when the application ends.
	ModAssert::AutoShutdown modAssertAutoShutdown;

	// This function sets up ModAssert:
	SetupModAssert(debugAllowed);

	int choice = 0;
	do
	{
		std::cout
			<< " 1. equal int                    11. equal vector and list" << std::endl
			<< " 2. different int                12. different vector and list" << std::endl
			<< " 3. equal int with data          13. different vectors of vectors" << std::endl
			<< " 4. different int with data      14. less on vectors" << std::endl
			<< " 5. equal strings                15. failing predicate, one argument" << std::endl
			<< " 6. different strings            16. failing predicate, two arguments" << std::endl
			<< " 7. equal escaped strings        17. failing predicate, three arguments" << std::endl
			<< " 8. different escaped strings    18. and" << std::endl
			<< " 9. equal vectors                19. fail with optional action" << std::endl
			<< "10. different vectors            20. check and throw" << std::endl
			<< std::endl
			<< "21. fail level Warning           31. verify and return value" << std::endl
			<< "22. fail level Fatal" << std::endl
			<< "23. fail 1 group" << std::endl
			<< "24. fail 2 groups" << std::endl
			<< "25. fail with 1 group % Fatal" << std::endl
			<< "26. fail with 2 groups % Fatal" << std::endl
			<< "27. fail other file" << std::endl
			<< "28. no text" << std::endl
			<< "30. display success" << std::endl
			<< std::endl
			<< " 0. exit" << std::endl
			<< std::endl;

		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1: OnEqualInt(); break;
		case 2: OnDiffInt(); break;
		case 3: OnEqualIntWithData(); break;
		case 4: OnDiffIntWithData(); break;
		case 5: OnEqualString(); break;
		case 6: OnDiffString(); break;
		case 7: OnEqualStringWithEscape(); break;
		case 8: OnDiffStringWithEscape(); break;
		case 9: OnEqualVector(); break;
		case 10: OnDiffVector(); break;
		case 11: OnEqualVectorAndList(); break;
		case 12: OnDiffVectorAndList(); break;
		case 13: OnDiffVectorVector(); break;
		case 14: OnDiffFailLessVector(); break;
		case 15: OnDiffFailPred1(); break;
		case 16: OnDiffFailPred2(); break;
		case 17: OnDiffFailPred3(); break;
		case 18: OnAnd(); break;
		case 19: OnFailWithOptional(); break;
		case 20: OnCheckAndThrow(); break;
		case 21: OnFailLevelWarning(); break;
		case 22: OnFailLevelFatal(); break;
		case 23: OnFailGroup1(); break;
		case 24: OnFailGroup1AndGroup2(); break;
		case 25: OnFailWith1GroupAndWarning(); break;
		case 26: OnFailWith2GroupsAndWarning(); break;
		case 27: OnFailInOtherFile(); break;
		case 28: OnNoText(); break;
		case 30: OnDisplaySuccess(); break;
		case 31: OnVerifyV(); break;
		}

		std::cout << std::endl;

	} while (choice!=0);
	return 0;
}
