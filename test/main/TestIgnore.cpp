//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "richbool/richbool.hpp"
#include "modassert/handler.hpp"
#include "modassert/category.hpp"
#include "modassert/categories.hpp"
#include "CreateList.h"
#include "ScopedSetReturnValue.h"

static ModAssert::Category<ModAssert::Assertions> as_h;
static ModAssert::Category<ModAssert::Checks> ch_h;

static ModAssert::Group<ModAssert::ReportFailure> group1("group1"), group2("group2");

ModAssert::Response CustomResponse[8] =
{
	ModAssert::StopDisplayingCustom1,
	ModAssert::StopDisplayingCustom2,
	ModAssert::StopDisplayingCustom3,
	ModAssert::StopDisplayingCustom4,
	ModAssert::StopDisplayingCustom5,
	ModAssert::StopDisplayingCustom6,
	ModAssert::StopDisplayingCustom7,
	ModAssert::StopDisplayingCustom8
};

template <class Type, class Category>
void SetDisplay(ModAssert::Group<Type> &type,
	size_t idx,
	bool b,
	Category )
{
	type.SetDisplay(idx, b);
}

template <class Type, class Category>
void SetDisplay(ModAssert::CombinationHolder<Type> &type,
	size_t idx,
	bool b,
	Category )
{
	type.SetDisplay(idx, b);
}

template <class Type, class Category>
void SetDisplay(ModAssert::Level<Type> &,
	size_t idx,
	bool b,
	Category cat)
{
	ModAssert::Level<Type>::SetDisplay(idx, b, cat);
}

template <class Type, class Category, class L>
void SetDisplay(ModAssert::GroupWithLevel<Type, L> &type,
	size_t idx,
	bool b,
	Category cat)
{
	type.SetDisplay(idx, b, cat);
}


template <class Type, class Category>
bool GetDisplay(ModAssert::Group<Type> &type,
	size_t idx,
	Category )
{
	return type.GetDisplay(idx);
}

template <class Type, class Category>
bool GetDisplay(ModAssert::CombinationHolder<Type> &type,
	size_t idx,
	Category )
{
	return type.GetDisplay(idx);
}

template <class Type, class Category>
bool GetDisplay(ModAssert::Level<Type> &,
	size_t idx,
	Category cat)
{
	return ModAssert::Level<Type>::GetDisplay(idx, cat);
}

template <class Type, class Category, class L>
bool GetDisplay(ModAssert::GroupWithLevel<Type, L> &type,
	size_t idx,
	Category cat)
{
	return type.GetDisplay(idx, cat);
}


template<class Type>
void TestIgnoreAssert(const Type &type_, size_t idx)
{
	// gives warnings with MSVC++ if it is a pure level
	// (probably because these are empty objects)
	Type &type = const_cast<Type&>(type_);

	const bool isLevel = type.hasLevel && ((idx+1)==type.GetSize());

	ScopedSetReturnValue s(CustomResponse[idx]);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, NULL);
	MOD_ASSERT_G(type, false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, as_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, ch_h));
		else
			META_ASSERT(GetDisplay(type, idx, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, as_h));
		META_ASSERT(GetDisplay(type, idx, ch_h));
	}

	SetDisplay(type, idx, true, as_h);

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_ASSERT_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, as_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, ch_h));
		else
			META_ASSERT(GetDisplay(type, idx, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, as_h));
		META_ASSERT(GetDisplay(type, idx, ch_h));
	}

	SetDisplay(type, idx, true, as_h);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, "");
	MOD_ASSERT_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, as_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, ch_h));
		else
			META_ASSERT(GetDisplay(type, idx, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, as_h));
		META_ASSERT(GetDisplay(type, idx, ch_h));
	}

	SetDisplay(type, idx, true, as_h);

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_ASSERT_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, as_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, ch_h));
		else
			META_ASSERT(GetDisplay(type, idx, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, as_h));
		META_ASSERT(GetDisplay(type, idx, ch_h));
	}

	SetDisplay(type, idx, true, as_h);
}

MA_TEST(IgnoreAssertLevel)
{
	TestIgnoreAssert(ModAssert::Warning, 0);
	TestIgnoreAssert(ModAssert::Error, 0);
	TestIgnoreAssert(ModAssert::Fatal, 0);
	TestIgnoreAssert(group1, 0);
	TestIgnoreAssert(group1%ModAssert::Warning, 0);
	TestIgnoreAssert(group1%ModAssert::Warning, 1);
	TestIgnoreAssert(group1&&group2, 0);
	TestIgnoreAssert(group1&&group2, 1);
	TestIgnoreAssert((group1&&group2)%ModAssert::Warning, 0);
	TestIgnoreAssert((group1&&group2)%ModAssert::Warning, 1);
	TestIgnoreAssert((group1&&group2)%ModAssert::Warning, 2);
}

template<class Type>
void TestIgnoreAssertManually(const Type &type_, size_t idx)
{
	// will give false warnings with MSVC++ if it is a pure level
	// (probably because these are empty objects)
	Type &type = const_cast<Type&>(type_);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, NULL);
	MOD_ASSERT_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_ASSERT_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, "");
	MOD_ASSERT_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_ASSERT_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	SetDisplay(type, idx, false, as_h);

	EXPECT_NO_FAILURE;

	// we don't expect failures to be reported now,
	// but the logger should still be called

	MOD_ASSERT_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_ASSERT_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_ASSERT_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_ASSERT_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	SetDisplay(type, idx, true, as_h);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, NULL);
	MOD_ASSERT_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_ASSERT_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, "");
	MOD_ASSERT_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_ASSERT_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(IgnoreAssertLevelManually)
{
	TestIgnoreAssertManually(ModAssert::Warning, 0);
	TestIgnoreAssertManually(ModAssert::Error, 0);
	TestIgnoreAssertManually(ModAssert::Fatal, 0);
	TestIgnoreAssertManually(group1, 0);
	TestIgnoreAssertManually(group1%ModAssert::Warning, 0);
	TestIgnoreAssertManually(group1%ModAssert::Warning, 1);
	TestIgnoreAssertManually(group1&&group2, 0);
	TestIgnoreAssertManually(group1&&group2, 1);
	TestIgnoreAssertManually((group1&&group2)%ModAssert::Warning, 0);
	TestIgnoreAssertManually((group1&&group2)%ModAssert::Warning, 1);
	TestIgnoreAssertManually((group1&&group2)%ModAssert::Warning, 2);
}

template<class Type>
void TestIgnoreVerifyManually(const Type &type_)
{
	// will give warnings with MSVC++ if it is a pure level
	// (probably because these are empty objects)
	Type &type = const_cast<Type&>(type_);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, NULL);
	MOD_VERIFY_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_VERIFY_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, "");
	MOD_VERIFY_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_VERIFY_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	SetDisplay(type, 0, false, as_h);

	EXPECT_NO_FAILURE;

	MOD_VERIFY_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_VERIFY_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_VERIFY_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	MOD_VERIFY_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	SetDisplay(type, 0, true, as_h);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, NULL);
	MOD_VERIFY_G(type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_VERIFY_PG(1, type, false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, NULL, type, "");
	MOD_VERIFY_GO(type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_VERIFY_PGO(1, type, 0, "", false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(IgnoreVerifyLevel)
{
	TestIgnoreVerifyManually(ModAssert::Warning);
	TestIgnoreVerifyManually(ModAssert::Error);
	TestIgnoreVerifyManually(ModAssert::Fatal);
}

template<class Type>
void TestIgnoreCheck(const Type &type_, size_t idx)
{
	// will give false warnings with MSVC++ if it is a pure level
	// (probably because these are empty objects)
	Type &type = const_cast<Type&>(type_);

	const bool isLevel = type.hasLevel && ((idx+1)==type.GetSize());

	META_ASSERT(GetDisplay(type, false, ch_h));
	META_ASSERT(GetDisplay(type, false, as_h));

	ScopedSetReturnValue s(CustomResponse[idx]);

	EXPECT_CHECK_G(false, "false", NULL, NULL, type, NULL);
	MOD_CHECK_G(type, false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, ch_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, as_h));
		else
			META_ASSERT(GetDisplay(type, idx, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, ch_h));
		META_ASSERT(GetDisplay(type, idx, as_h));
	}

	SetDisplay(type, idx, true, ch_h);

	EXPECT_CHECK_G(false, "false", NULL, CreateParameterList()("1", 1), type, NULL);
	MOD_CHECK_PG(1, type, false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, ch_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, as_h));
		else
			META_ASSERT(GetDisplay(type, idx, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, ch_h));
		META_ASSERT(GetDisplay(type, idx, as_h));
	}

	SetDisplay(type, idx, true, ch_h);

	EXPECT_CHECK_G(false, "false", NULL, NULL, type, "");
	MOD_CHECK_GO(type, 0, "", false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, ch_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, as_h));
		else
			META_ASSERT(GetDisplay(type, idx, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, ch_h));
		META_ASSERT(GetDisplay(type, idx, as_h));
	}

	SetDisplay(type, idx, true, ch_h);

	EXPECT_CHECK_G(false, "false", NULL, CreateParameterList()("1", 1), type, "");
	MOD_CHECK_PGO(1, type, 0, "", false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!GetDisplay(type, idx, ch_h));

		if (!isLevel)
			META_ASSERT(!GetDisplay(type, idx, as_h));
		else
			META_ASSERT(GetDisplay(type, idx, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(GetDisplay(type, idx, ch_h));
		META_ASSERT(GetDisplay(type, idx, as_h));
	}

	SetDisplay(type, idx, true, ch_h);
}

MA_TEST(IgnoreCheckLevel_Warning)
{
	TestIgnoreCheck(ModAssert::Warning, 0);
}

MA_TEST(IgnoreCheckLevel_Error)
{
	TestIgnoreCheck(ModAssert::Error, 0);
}

MA_TEST(IgnoreCheckLevel_Fatal)
{
	TestIgnoreCheck(ModAssert::Fatal, 0);
}

MA_TEST(IgnoreCheckLevel_OneGroup)
{
	TestIgnoreCheck(group1, 0);
}

MA_TEST(IgnoreCheckLevel_GroupAndWarning1)
{
	TestIgnoreCheck(group1%ModAssert::Warning, 0);
}

MA_TEST(IgnoreCheckLevel_GroupAndWarning2)
{
	TestIgnoreCheck(group1%ModAssert::Warning, 1);
}

MA_TEST(IgnoreCheckLevel_TwoGroups1)
{
	TestIgnoreCheck(group1&&group2, 0);
}

MA_TEST(IgnoreCheckLevel_TwoGroups2)
{
	TestIgnoreCheck(group1&&group2, 1);
}

MA_TEST(IgnoreCheckLevel_TwoGroupsAndWarning1)
{
	TestIgnoreCheck((group1&&group2)%ModAssert::Warning, 0);
}

MA_TEST(IgnoreCheckLevel_TwoGroupsAndWarning2)
{
	TestIgnoreCheck((group1&&group2)%ModAssert::Warning, 1);
}

MA_TEST(IgnoreCheckLevel_TwoGroupsAndWarning3)
{
	TestIgnoreCheck((group1&&group2)%ModAssert::Warning, 2);
}

MA_TEST(StopDisplayingAssertionsInFile)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingFile);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!ModAssert::GetDisplayInFile(__FILE__, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(ModAssert::GetDisplayInFile(__FILE__, as_h));
	}

	EXPECT_NO_FAILURE;
	MOD_ASSERT(false);

	ModAssert::SetDisplayInFile(__FILE__, true, as_h);
}

MA_TEST(ManuallyStopDisplayingAssertionsInFile)
{
	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetDisplayInFile(__FILE__, false, as_h);

	EXPECT_NO_FAILURE;
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetDisplayInFile(__FILE__, true, as_h);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingChecksInFile)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingFile);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!ModAssert::GetDisplayInFile(__FILE__, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(ModAssert::GetDisplayInFile(__FILE__, ch_h));
	}

	EXPECT_NO_FAILURE;
	MOD_CHECK(false, 0);

	ModAssert::SetDisplayInFile(__FILE__, true, ch_h);
}

MA_TEST(ManuallyStopDisplayingChecksInFile)
{
	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetDisplayInFile(__FILE__, false, ch_h);

	EXPECT_NO_FAILURE;
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetDisplayInFile(__FILE__, true, ch_h);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingAssertionsAndChecksInFile)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingFile);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!ModAssert::GetDisplayInFile(__FILE__, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(ModAssert::GetDisplayInFile(__FILE__, as_h));
	}

	EXPECT_NO_FAILURE;
	MOD_ASSERT(false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!ModAssert::GetDisplayInFile(__FILE__, as_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(ModAssert::GetDisplayInFile(__FILE__, as_h));
	}

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!ModAssert::GetDisplayInFile(__FILE__, ch_h));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(ModAssert::GetDisplayInFile(__FILE__, ch_h));
	}

	EXPECT_NO_FAILURE;
	MOD_CHECK(false, 0);

	ModAssert::SetDisplayInFile(__FILE__, true, as_h);
	ModAssert::SetDisplayInFile(__FILE__, true, ch_h);
}

MA_TEST(ManuallyDontLogAssertionsFile)
{
	ModAssert::SetLogInFile(__FILE__, false, as_h);
	META_ASSERT(!ModAssert::GetLogInFile(__FILE__, as_h));

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;
	META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetLogInFile(__FILE__, true, as_h);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(ManuallyDontLogChecksInFile)
{
	ModAssert::SetLogInFile(__FILE__, false, ch_h);
	META_ASSERT(!ModAssert::GetLogInFile(__FILE__, ch_h));

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetLogInFile(__FILE__, true, ch_h);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingThis_Assert)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	int a=0;
	for (int i=0; i<4; ++i)
	{
		if (i==0)
			EXPECT_ASSERT(false, "++a==0", NULL, NULL, NULL);
		else
			EXPECT_NO_FAILURE;

		MOD_ASSERT(++a==0); // fails every time, but only reported first time

		if (MOD_ASSERT_REPORTS)
			META_ASSERT(CheckLoggerCalled());
		else
			META_ASSERT(!CheckLoggerCalled());
	}
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(a,4)); // MOD_ASSERT should still evaluate its argument if it is ignored
}

MA_TEST(StopDisplayingThis_Verify)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	int a=0;
	for (int i=0; i<4; ++i)
	{
		if (i==0)
			EXPECT_ASSERT(false, "++a==0", NULL, NULL, NULL);
		else
			EXPECT_NO_FAILURE;

		MOD_VERIFY(++a==0); // fails every time, but only reported first time
		if (MOD_ASSERT_REPORTS)
			META_ASSERT(CheckLoggerCalled());
		else
			META_ASSERT(!CheckLoggerCalled());
	}
	META_ASSERT(rbEQUAL(a,4)); // MOD_VERIFY should still evaluate its argument if it is ignored
}

MA_TEST(StopDisplayingThis_Fail)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	for (int i=0; i<4; ++i)
	{
		if (i==0)
			EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
		else
			EXPECT_NO_FAILURE;

		MOD_FAIL; // fails every time, but only reported first time
		if (MOD_ASSERT_REPORTS)
			META_ASSERT(CheckLoggerCalled());
		else
			META_ASSERT(!CheckLoggerCalled());
	}

	EXPECT_NO_FAILURE;
}


MA_TEST(StopDisplayingThis_AssertWithExpressions)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	int a=0;
	EXPECT_ASSERT(false, "++a==0", NULL, CreateParameterList()("a", "1"), NULL);
	for (int i=0; i<4; ++i)
		MOD_ASSERT_P(a, ++a==0); // fails every time, but only reported first time
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(rbEQUAL(a,4)); // MOD_ASSERT should still evaluate its argument if it is ignored
}


MA_TEST(StopDisplayingThis_VerifyWithExpressions)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	int a=0;
	EXPECT_ASSERT(false, "++a==0", NULL, CreateParameterList()("a", "1"), NULL);
	for (int i=0; i<4; ++i)
		MOD_VERIFY_P(a, ++a==0); // fails every time, but only reported first time
	META_ASSERT(rbEQUAL(a,4)); // MOD_VERIFY should still evaluate its argument if it is ignored
}


MA_TEST(StopDisplayingThisWithExpressions)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingThis);

	IF_MOD_ASSERT_REPORTS(int a=0;)
	EXPECT_FAIL(false, NULL, NULL, CreateParameterList()("a", "0"), NULL);
	for (int i=0; i<4; ++i)
		MOD_FAIL_P(a); // fails every time, but only reported first time

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingAllAssertions)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingAll);

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	for (int i=0; i<4; ++i)
		MOD_FAIL; // fails every time, but only reported first time

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Assertions>()));

	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Assertions>());

	EXPECT_NO_FAILURE;
}

MA_TEST(ManuallyStopDisplayingAllAssertions)
{
	ModAssert::SetDisplayAll(false, ModAssert::Category<ModAssert::Assertions>());
	META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Assertions>()));

	EXPECT_NO_FAILURE;
	for (int i=0; i<4; ++i)
		MOD_FAIL; // fails every time, but not reported

	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Assertions>());

	EXPECT_NO_FAILURE;
}

MA_TEST(ManuallyDontLogAllAssertions)
{
	ModAssert::SetLogAll(false, ModAssert::Category<ModAssert::Assertions>());
	META_ASSERT(!ModAssert::GetLogAll(ModAssert::Category<ModAssert::Assertions>()));

	EXPECT_FAIL(false, NULL, NULL, NULL, NULL);
	MOD_FAIL;
	META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetLogAll(true, ModAssert::Category<ModAssert::Assertions>());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingAllChecks)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingAll);

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	for (int i=0; i<4; ++i)
		MOD_CHECK(false, 0); // fails every time, but only reported first time

	if (MOD_CHECK_REPORTS)
		META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Checks>()));

	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Checks>());

	EXPECT_NO_FAILURE;
}

MA_TEST(ManuallyStopDisplayingAllChecks)
{
	ModAssert::SetDisplayAll(false, ModAssert::Category<ModAssert::Checks>());
	META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Checks>()));

	EXPECT_NO_FAILURE;
	for (int i=0; i<4; ++i)
		MOD_CHECK(false, 0); // fails every time, but not reported

	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Checks>());

	EXPECT_NO_FAILURE;
}

MA_TEST(ManuallyDontLogAllChecks)
{
	ModAssert::SetLogAll(false, ModAssert::Category<ModAssert::Checks>());
	META_ASSERT(!ModAssert::GetLogAll(ModAssert::Category<ModAssert::Checks>()));

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	MOD_CHECK(false, 0);
	META_ASSERT(!CheckLoggerCalled());

	ModAssert::SetLogAll(true, ModAssert::Category<ModAssert::Checks>());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingAllAssertionsAndChecks)
{
	ScopedSetReturnValue s(ModAssert::StopDisplayingAll);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	for (int i=0; i<4; ++i)
		MOD_ASSERT(false); // fails every time, but only reported first time

	if (MOD_ASSERT_REPORTS)
		META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Assertions>()));

	EXPECT_CHECK(false, "false", NULL, NULL, NULL);
	for (int c=0; c<4; ++c)
		MOD_CHECK(false, 0); // fails every time, but only reported first time

	if (MOD_CHECK_REPORTS)
		META_ASSERT(!ModAssert::GetDisplayAll(ModAssert::Category<ModAssert::Checks>()));

	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Assertions>());
	ModAssert::SetDisplayAll(true, ModAssert::Category<ModAssert::Checks>());

	EXPECT_NO_FAILURE;
}

MA_TEST(StopDisplayingGroup)
{
	ModAssert::Group<ModAssert::ReportFailure> G1("group 1");

	ScopedSetReturnValue s(ModAssert::StopDisplayingCustom1);

	EXPECT_ASSERT_G(false, "false", NULL, NULL, G1, NULL);
	MOD_ASSERT_G(G1, false);
	if (MOD_ASSERT_REPORTS)
	{
		META_ASSERT(CheckLoggerCalled());
		META_ASSERT(!G1.GetDisplay(false));
	}
	else
	{
		META_ASSERT(!CheckLoggerCalled());
		META_ASSERT(G1.GetDisplay(false));
	}

	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(G1, false);
	MOD_CHECK_G(G1, false, 0);

	G1.SetDisplay(0, true);
}
