//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#pragma warning(disable: 4189)
#endif

#include "stdafx.h"
#include "Examples.h"

// include this file to use the modular assertions
#include "modassert/assert.hpp"

// include this files to use basic rich booleans
#include "richbool/richbool.hpp"

// include this file to use rich booleans for std::strings
#include "richbool/stdstring.hpp"

// include this file to use rich booleans for containers
#include "richbool/containers.hpp"

#include <string>
#include <list>



// This is only needed for ModAssert::GetMode(); normally you don't need this
// in source files that don't setup ModAssert.
#include "modassert/handler.hpp"

struct A
{
	A()
	{
		// uncomment to cause assertion failure before main(...) is entered:
		//MOD_FAIL;
	}
} instance_of_A;

static HWND hWnd = 0;

void SetHWnd(HWND hWnd_)
{
	hWnd = hWnd_;
}

void MessageBox(const std::string &msg)
{
	MessageBox(hWnd, msg.c_str(), "ModAssert Demo", MB_OK);
}

void OnSucceedingAssert()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding assertion,\n"
		"so no message will be shown");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown");
#endif
}

void OnFailingAssert(const std::string &extra="")
{
#if MOD_ASSERT_REPORTS
	std::string str = "Reporting of assertions is enabled at compile time,\n";
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
	MessageBox(str.c_str());
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}

void OnFailingCheck(const std::string &extra="")
{
#if MOD_CHECK_REPORTS
	std::string str = "Reporting of checks is enabled at compile time,\n";
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
	MessageBox(str.c_str());
#else
	MessageBox("Reporting of checks is disabled at compile time,\n"
		"so no message will be shown.");
#endif
}

void OnEqualInt()
{
	OnSucceedingAssert();

	int a=1, b=1;
	MOD_ASSERT(rbEQUAL(a, b));
}

void OnDiffInt()
{
	OnFailingAssert();

	int a=1, b=2;
	MOD_ASSERT(rbEQUAL(a, b));
}

void OnEqualIntWithData()
{
	OnSucceedingAssert();

	int a=3, b=2, c=4, d=3;
	MOD_ASSERT_P(a<<b<<c<<d, rbEQUAL(a+d, b+c));
}

void OnDiffIntWithData()
{
	OnFailingAssert();

	int a=3, b=2, c=5, d=1;
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
		MessageBox("No exception thrown");
	}
	catch (int)
	{
		MessageBox("Exception was thrown");
	}
}

void OnCheckAndThrow()
{
#if MOD_CHECK_REPORTS
	MessageBox("Now comes a failing check,\n"
		"so a message will be shown\n"
		"unless this or all checks are ignored\n"
		"This will throw an exception");
#else
	MessageBox("Reporting of checks is disabled at compile time,\n"
		"so no message will be shown");
#endif

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

void OnAnd()
{
	OnFailingAssert();

	MOD_ASSERT(rbAND(rbEQUAL(2,1), rbEQUAL(2,3)));
}

ModAssert::Group<ModAssert::ReportFailure> group1("group 1"), group2("group 2");

void OnFailWithGroup()
{
	OnFailingAssert();

	MOD_FAIL_G(group1);
}

void OnFailWithTwoGroups()
{
	OnFailingAssert();

	MOD_FAIL_G(group1 && group2);
}

void OnFailWithLevelWarning()
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Warning);
}

void OnFailWithLevelFatal()
{
	OnFailingAssert();

	MOD_FAIL_G(ModAssert::Fatal);
}

void OnFailWithOneGroupAndLevelWarning()
{
	OnFailingAssert();

	MOD_FAIL_G(group1%ModAssert::Warning);
}

void OnFailWithTwoGroupsAndLevelWarning()
{
	OnFailingAssert();

	MOD_FAIL_G((group1&&group2)%ModAssert::Warning);
}

void OnVerifyV()
{
	OnFailingAssert();

	int n = MOD_VERIFY_V(rbvEQUAL(1+2,4));

	MessageBox((RichBool::ToString(n)+" was returned").c_str());
}


static DWORD WINAPI FailingFunction(LPVOID )
{
	// This function is called in another thread.
	// Because a dialog box can only be shown from the GUI-thread,
	// the assertion dialog box will not be shown here,
	// and the program will automatically break into the debugger.
	int a=6, b=3;
	MOD_ASSERT_P(a << b, rbEQUAL(a+b, 10));
	return 0;
}

void OnFailInOtherThread()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a failing assertion,\n"
		"but this will occur in another thread,\n"
		"so no dialog box will be shown.\n"
		"Instead the program will directly break into the debugger\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown");
#endif
	CreateThread(0, 0, FailingFunction, 0, 0, 0);
}

void OnSuccess()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding assertion,\n"
		"but ModAssert::IfSuccess is added to the group,\n"
		"so the dialog box will be shown\n"
		"(unless this assertion is turned off)\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown");
#endif

	int a=1;
	MOD_ASSERT_G(ModAssert::IfSuccess, rbEQUAL(a,1));
}

void OnReportAll()
{
#if MOD_ASSERT_REPORTS
	MessageBox("Now comes a succeeding and a failing assertion,\n"
		"but an object of the type ModAssert::ReportAll\n"
		"is added to the group,\n"
		"so the dialog box will be shown for both\n"
		"(unless this assertion is turned off)\n");
#else
	MessageBox("Reporting of assertions is disabled at compile time,\n"
		"so no message will be shown");
#endif

	// made static, so that requests to stop displaying it are remembered
	static ModAssert::Group<ModAssert::ReportAll> reportAll("group");

	int a=2;
	MOD_ASSERT_G(reportAll, rbEQUAL(a,2));
	MOD_ASSERT_G(reportAll, rbEQUAL(a,3));
}

void FailingAssert()
{
	MOD_ASSERT(rbEQUAL(1,2));
}

void OnGetlasterror()
{
	OFSTRUCT of;
	OpenFile("nofile.ext", &of, OF_READ);

	MOD_FAIL;
}

extern void FailInOtherFile();

void OnFailInOtherFile()
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

void Files()
{
	MOD_ASSERT(rbFILE("nofile.txt", RichBool::IsReadable()&RichBool::IsWritable()));
	MOD_ASSERT(rbDOES_NOT_EXIST("nofile.txt"));
	MOD_ASSERT(rbDOES_NOT_EXIST("nofile2.txt"));
	MOD_VERIFY_V(rbvDOES_NOT_EXIST((const char *)"nofile.txt"));
	MOD_VERIFY_V(rbvDOES_NOT_EXIST((const char *)"nofile2.txt"));
}
