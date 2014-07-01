//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "modassert/consoledisplayer.hpp"
#include "modassert/result.hpp"
#include "modassert/category.hpp"
#include "modassert/handler.hpp"
#include "richbool/richbool.hpp"
#include "richbool/string.hpp"
#include "GetStreamString.h"
#include "StubLogger.h"
#include <iostream>

#ifdef RICHBOOL_USE_WX
#include "richbool/wxstring.hpp"
static RichBool::WxStringCmp Strcmp;
#else
#include "richbool/stdstring.hpp"
static RichBool::StringCompare Strcmp;
#endif

// some data that are the same for every test:
static const ModAssert::Context context("file", 1, "void foo()");
static ModAssert::TemplateGroupListWithLevel<ModAssert::Level<ModAssert::detail::L_<2> > > lError(ModAssert::Error);
static const RichBool::SharedAnalysis analysis = 0;
static const ModAssert::Result result(false, analysis, 0);
static const ModAssert::Category<ModAssert::Assertions> category;
static const ModAssert::Properties prop(&category, context, "condition", &lError, 0);
static const ModAssert::Properties propWithOptional(&category, context, "condition", &lError, "abc");


// tests to check the output

MA_TEST(OutputWhenNoneDisallowed)
{
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"S: Stop displaying this            "
		"F: Stop displaying this file       "+NewLine()+
		"A: Stop displaying all             "
		"1: Stop displaying Level: Error    "+NewLine()+
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));
}

MA_TEST(OutputWhenDebugDisallowed)
{
	ModAssert::SetAllowBreakIntoDebugger(false);

	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetAllowBreakIntoDebugger(true);
}

MA_TEST(OutputWhenDebugNotPossible)
{
	ModAssert::SetAllowBreakIntoDebugger(true);

	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(false);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetAllowBreakIntoDebugger(true);
}

MA_TEST(OutputWhenExitDisallowed)
{
	ModAssert::SetAllowExit(false);

	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"S: Stop displaying this            "
		"F: Stop displaying this file       "+NewLine()+
		"A: Stop displaying all             "
		"1: Stop displaying Level: Error    "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetAllowExit(true);
}

MA_TEST(OutputWhenNoneDisallowed_WithOptional)
{
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(propWithOptional);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"O: Optional action abc             "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));
}

MA_TEST(OutputWhenOptionalDisallowed_WithOptional)
{
	ModAssert::SetAllowOptional(false);

	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(propWithOptional);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"S: Stop displaying this            "
		"F: Stop displaying this file       "+NewLine()+
		"A: Stop displaying all             "
		"1: Stop displaying Level: Error    "+NewLine()+
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetAllowOptional(true);
}

void dummy()
{
}

MA_TEST(OutputWithGlobalOptionalAction)
{
	MemOutStream memOut;

	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"G: dummy                           "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(OutputWithGlobalOptionalAction_OtherSymbol)
{
	MemOutStream memOut;

	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);
	displayer.SetGlobalOptionalActionSymbol('Z');

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"Z: dummy                           "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(OutputWithGlobalOptionalAction_GlobalOptionalDisallowed)
{
	ModAssert::SetAllowGlobalOptional(false);

	MemOutStream memOut;

	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"S: Stop displaying this            "
		"F: Stop displaying this file       "+NewLine()+
		"A: Stop displaying all             "
		"1: Stop displaying Level: Error    "+NewLine()+
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetGlobalOptionalAction(NULL, NULL);

	ModAssert::SetAllowGlobalOptional(true);
}

MA_TEST(OutputWithOptionalLogger)
{
	StubLogger logger;
	ModAssert::SetOptionalLogger(&logger, "optional logger");

	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(NULL, &memOut);
	displayer.SetIsDebugPossible(true);

	displayer.DisplayChoices(prop);

	RichBool::detail::String str = NewLine()+
		"I: Ignore                          "
		"D: Debug                           "+NewLine()+
		"L: optional logger                 "
		"S: Stop displaying this            "+NewLine()+
		"F: Stop displaying this file       "
		"A: Stop displaying all             "+NewLine()+
		"1: Stop displaying Level: Error    "
		"X: Exit                            "+NewLine()+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memOut), Strcmp));

	ModAssert::SetOptionalLogger(NULL, NULL);
}


// tests to check the return value

void CheckThatKnows(ModAssert::ConsoleDisplayer &displayer,
					char ch,
					const ModAssert::Properties &properties,
					ModAssert::Response expectedResponse)
{
	ModAssert::Response response = 0;
	bool wrong = true;
	displayer.ProcessCharacter(ch, properties, result, response, wrong);
	META_ASSERT_P(ch, !wrong);
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}

void CheckThatDoesntKnow(ModAssert::ConsoleDisplayer &displayer,
						 char ch,
						 const ModAssert::Properties &properties)
{
	ModAssert::Response response = 0;
	bool wrong = false;
	displayer.ProcessCharacter(ch, properties, result, response, wrong);
	META_ASSERT_P(ch, wrong);
	META_ASSERT(rbEQUAL_BITWISE(ModAssert::Response(0), response));
}

MA_TEST(ProcessDefault)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatDoesntKnow(displayer, 'G', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);
}

MA_TEST(Process_ExitDisallowed)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::SetAllowExit(false);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'X', prop);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatDoesntKnow(displayer, 'G', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetAllowExit(true);
}

MA_TEST(Process_DebugDisallowed)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(false);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatDoesntKnow(displayer, 'G', prop);
	CheckThatDoesntKnow(displayer, 'D', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);
}

MA_TEST(Process_DebugNotPossible)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(false);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatDoesntKnow(displayer, 'G', prop);
	CheckThatDoesntKnow(displayer, 'D', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);
}

MA_TEST(ProcessWithOptional)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', propWithOptional, 0);
	CheckThatKnows(displayer, 'S', propWithOptional, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', propWithOptional, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', propWithOptional, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', propWithOptional, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', propWithOptional, ModAssert::Exit);
	CheckThatKnows(displayer, 'O', propWithOptional, ModAssert::Optional);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'L', propWithOptional);
	CheckThatDoesntKnow(displayer, '0', propWithOptional);
	CheckThatDoesntKnow(displayer, '2', propWithOptional);
	CheckThatDoesntKnow(displayer, 'G', propWithOptional);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);
}

MA_TEST(ProcessWithOptional_Disallowed)
{
	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::SetAllowOptional(false);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', propWithOptional, 0);
	CheckThatKnows(displayer, 'S', propWithOptional, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', propWithOptional, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', propWithOptional, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', propWithOptional, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', propWithOptional, ModAssert::Exit);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'O', propWithOptional);
	CheckThatDoesntKnow(displayer, 'L', propWithOptional);
	CheckThatDoesntKnow(displayer, '0', propWithOptional);
	CheckThatDoesntKnow(displayer, '2', propWithOptional);
	CheckThatDoesntKnow(displayer, 'G', propWithOptional);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetAllowOptional(true);
}

MA_TEST(ProcessWithGlobalOptional)
{
	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatKnows(displayer, 'G', prop, ModAssert::GlobalOptional);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(ProcessWithGlobalOptional_Disallowed)
{
	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	ModAssert::SetAllowGlobalOptional(false);

	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatDoesntKnow(displayer, 'G', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetAllowGlobalOptional(true);

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(ProcessWithGlobalOptional_OtherSymbol)
{
	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);
	displayer.SetGlobalOptionalActionSymbol('Z');

	CheckThatKnows(displayer, 'I', prop, 0);
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	CheckThatDoesntKnow(displayer, 'O', prop);
	CheckThatDoesntKnow(displayer, 'L', prop);
	CheckThatDoesntKnow(displayer, '0', prop);
	CheckThatDoesntKnow(displayer, '2', prop);
	CheckThatKnows(displayer, 'Z', prop, ModAssert::GlobalOptional);
	CheckThatDoesntKnow(displayer, 'G', prop);

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(ProcessOptionalLogger)
{
	StubLogger logger;
	ModAssert::SetOptionalLogger(&logger, "optional logger");

	bool bDebug = ModAssert::GetAllowBreakIntoDebugger();
	ModAssert::SetAllowBreakIntoDebugger(true);

	ModAssert::ConsoleDisplayer displayer;
	displayer.SetIsDebugPossible(true);

	CheckThatKnows(displayer, 'I', prop, 0);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'S', prop, ModAssert::StopDisplayingThis);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'F', prop, ModAssert::StopDisplayingFile);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'A', prop, ModAssert::StopDisplayingAll);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, '1', prop, ModAssert::StopDisplayingCustom1);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'X', prop, ModAssert::Exit);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'D', prop, ModAssert::BreakIntoDebugger);
	META_ASSERT(!logger.CheckCalled());
	CheckThatDoesntKnow(displayer, 'O', prop);
	META_ASSERT(!logger.CheckCalled());
	CheckThatKnows(displayer, 'L', prop, 0);
	META_ASSERT(logger.CheckCalled());
	CheckThatDoesntKnow(displayer, '0', prop);
	META_ASSERT(!logger.CheckCalled());
	CheckThatDoesntKnow(displayer, '2', prop);
	META_ASSERT(!logger.CheckCalled());
	CheckThatDoesntKnow(displayer, 'G', prop);
	META_ASSERT(!logger.CheckCalled());

	ModAssert::SetAllowBreakIntoDebugger(bDebug);

	ModAssert::SetOptionalLogger(NULL, NULL);
}


MA_TEST(AskIgnore)
{
	RichBool::detail::String strInput = "i";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(prop, result);

	ModAssert::Response expectedResponse = 0;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}

MA_TEST(AskExit)
{
	RichBool::detail::String strInput = "x";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(prop, result);

	ModAssert::Response expectedResponse = ModAssert::Exit;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}

MA_TEST(AskOptionalAndExit)
{
	RichBool::detail::String strInput = "ox";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(propWithOptional, result);

	ModAssert::Response expectedResponse = ModAssert::Optional|ModAssert::Exit;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}

MA_TEST(AskMany)
{
	RichBool::detail::String strInput = "ox1asfg";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::SetGlobalOptionalAction(dummy, "dummy");

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(propWithOptional, result);

	ModAssert::Response expectedResponse =
		ModAssert::Optional|ModAssert::GlobalOptional|ModAssert::Exit|ModAssert::StopDisplayingCustom1
			|ModAssert::StopDisplayingAll|ModAssert::StopDisplayingFile
			|ModAssert::StopDisplayingThis;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));

	ModAssert::SetGlobalOptionalAction(NULL, NULL);
}

MA_TEST(WrongInputThenIgnore)
{
	RichBool::detail::String strInput = "sza\ni";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(prop, result);

	ModAssert::Response expectedResponse = 0;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}

MA_TEST(WrongInputThenExit)
{
	RichBool::detail::String strInput = "sza\nx";
	MemInStream memIn(strInput);
	MemOutStream memOut;

	ModAssert::ConsoleDisplayer displayer(&memIn, &memOut);

	ModAssert::Response response = displayer.AskResponse(prop, result);

	ModAssert::Response expectedResponse = ModAssert::Exit;
	META_ASSERT(rbEQUAL_BITWISE(expectedResponse, response));
}
