//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "ScopedSetReturnValue.h"
#include "modassert/handler.hpp"
#include "CreateList.h"

// The assertions in this file are either genuine wxWidgets assertions
// or redefined to be ModAssert assertions, depending on whether
// RICHBOOL_USE_WX is defined. By running the test in both configurations,
// we know for sure that the redefinitions in modassert/wxassert.hpp
// work as expected.

#ifdef RICHBOOL_USE_WX
#include "wx/debug.h"
#else
#include "modassert/wxassert.hpp"
#endif

MA_TEST(wxASSERT_Pass)
{
	EXPECT_NO_FAILURE;
	wxASSERT(1==1);
}

MA_TEST(wxASSERT_Fail)
{
	EXPECT_ASSERT(false, "1==2", NULL, NULL, NULL);
	wxASSERT(1==2);
}

MA_TEST(wxASSERT_MSG_Pass)
{
	EXPECT_NO_FAILURE;
	wxASSERT_MSG(1==1, "failure");
}

MA_TEST(wxASSERT_MSG_Fail)
{
	EXPECT_ASSERT(false, "1==2", NULL, ModAssert::CreateParameterList()("failure"), NULL);
	wxASSERT_MSG(1==2, "failure");
}

MA_TEST(wxFAIL)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "wxAssertFailure", NULL, NULL, NULL);
#else
	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
#endif
	wxFAIL;
}

MA_TEST(wxFAIL_MSG)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "wxAssertFailure", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#else
	EXPECT_FAIL(false, NULL, NULL, ModAssert::CreateParameterList()("failure"), NULL);
#endif
	wxFAIL_MSG("failure");
}

bool FuncWithWxCheck(int val)
{
	wxCHECK(val==1, false);
	return true;
}

MA_TEST(wxCHECK_Pass)
{
	EXPECT_NO_FAILURE;
	bool b = FuncWithWxCheck(1);
	META_ASSERT(b);
}

MA_TEST(wxCHECK_Fail)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "val==1", NULL, NULL, NULL);
#else
	EXPECT_CHECK(false, "val==1", NULL, NULL, NULL);
#endif
	bool b = FuncWithWxCheck(2);
	META_ASSERT(!b);
}

bool FuncWithWxCheckMsg(int val)
{
	wxCHECK_MSG(val==1, false, "failure");
	return true;
}

MA_TEST(wxCHECK_MSG_Pass)
{
	EXPECT_NO_FAILURE;
	bool b = FuncWithWxCheckMsg(1);
	META_ASSERT(b);
}

MA_TEST(wxCHECK_MSG_Fail)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#else
	EXPECT_CHECK(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#endif
	bool b = FuncWithWxCheckMsg(2);
	META_ASSERT(!b);
}

bool FuncWithWxCheck2(int val)
{
	wxCHECK2(val==1, return false);
	return true;
}

MA_TEST(wxCHECK2_Pass)
{
	EXPECT_NO_FAILURE;
	bool b = FuncWithWxCheck2(1);
	META_ASSERT(b);
}

MA_TEST(wxCHECK2_Fail)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "val==1", NULL, NULL, NULL);
#else
	EXPECT_CHECK(false, "val==1", NULL, NULL, NULL);
#endif
	bool b = FuncWithWxCheck2(2);
	META_ASSERT(!b);
}

bool FuncWithWxCheck2Msg(int val)
{
	wxCHECK2_MSG(val==1, return false, "failure");
	return true;
}

MA_TEST(wxCHECK2_MSG_Pass)
{
	EXPECT_NO_FAILURE;
	bool b = FuncWithWxCheck2Msg(1);
	META_ASSERT(b);
}

MA_TEST(wxCHECK2_MSG_Fail)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#else
	EXPECT_CHECK(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#endif
	bool b = FuncWithWxCheck2Msg(2);
	META_ASSERT(!b);
}

void FuncWithWxCheckRet(int val, bool &result)
{
	result = false;
	wxCHECK_RET(val==1, "failure");
	result = true;
}

MA_TEST(wxCHECK_RET_Pass)
{
	EXPECT_NO_FAILURE;
	bool b = false;
	FuncWithWxCheckRet(1, b);
	META_ASSERT(b);
}

MA_TEST(wxCHECK_RET_Fail)
{
#ifdef RICHBOOL_USE_WX
	EXPECT_ASSERT(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#else
	EXPECT_CHECK(false, "val==1", NULL, ModAssert::CreateParameterList()("failure"), NULL);
#endif
	bool b = false;
	FuncWithWxCheckRet(2, b);
	META_ASSERT(!b);
}
