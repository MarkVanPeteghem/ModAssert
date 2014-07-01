//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_LEVEL 1

#include "ModAssertTest.h"
#include "CreateList.h"
#include "modassert/category.hpp"
#include "richbool/richbool.hpp"

MA_TEST(Assert_Success_Displayed)
{
	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());


	EXPECT_ASSERT(true, "true", NULL, CreateParameterList()("1", 1), NULL);
	MOD_ASSERT_PG(1, ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_Success_And_Level_Displayed)
{
	EXPECT_ASSERT_G(true, "true", NULL, NULL, ModAssert::Error, NULL);
	MOD_ASSERT_G(ModAssert::IfSuccess % ModAssert::Error, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Verify_Success_Displayed)
{
	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_VERIFY_G(ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT(true, "true", NULL, CreateParameterList()("1", 1), NULL);
	MOD_VERIFY_PG(1, ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

struct Inc
{
	Inc(int &n_): n(n_) {}
	int &n;
	void operator()()
	{
		++n;
	}
private:
	Inc& operator=(const Inc &)
	{
		return *this;
	}
};

MA_TEST(VerifyV_Success_Displayed)
{
	EXPECT_ASSERT(true, "true", NULL, NULL, NULL);
	MOD_VERIFY_VG(ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT(true, "true", NULL, CreateParameterList()("1", 1), NULL);
	MOD_VERIFY_VPG((1), ModAssert::IfSuccess, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Check_Success_Displayed)
{
	int a=1;

	EXPECT_CHECK(true, "true", NULL, NULL, NULL);
	MOD_CHECK_G(ModAssert::IfSuccess, true, ++a);
	META_ASSERT(rbEQUAL(a,1));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_CHECK(true, "true", NULL, CreateParameterList()("1", 1), NULL);
	MOD_CHECK_PG(1, ModAssert::IfSuccess, true, ++a);
	META_ASSERT(rbEQUAL(a,1));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(CheckV_Success_Displayed)
{
	int a=1;

	Inc inc_a(a);

	EXPECT_CHECK(true, "true", NULL, NULL, NULL);
	MOD_CHECK_VG(ModAssert::IfSuccess, true, inc_a);
	META_ASSERT(rbEQUAL(a,1));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_CHECK(true, "true", NULL, CreateParameterList()("1", 1), NULL);
	MOD_CHECK_VPG((1), ModAssert::IfSuccess, true, inc_a);
	META_ASSERT(rbEQUAL(a,1));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Check_NoPass_Success_Displayed)
{
	int a=1;

	EXPECT_CHECK(false, "a==0", NULL, NULL, NULL);
	MOD_CHECK_G(ModAssert::IfSuccess, a==0, ++a);
	META_ASSERT(rbEQUAL(a,2));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_CHECK(false, "a==0", NULL, CreateParameterList()("1", 1), NULL);
	MOD_CHECK_PG(1, ModAssert::IfSuccess, a==0, ++a);
	META_ASSERT(rbEQUAL(a,3));
	if (MOD_CHECK_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

static ModAssert::Group<ModAssert::ReportNone> off("");
static ModAssert::Group<ModAssert::ReportAll> all("");

MA_TEST(Assert_Success_And_Off_Not_Displayed)
{
	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(ModAssert::IfSuccess(off), true);
	META_ASSERT(!CheckLoggerCalled());

	MOD_ASSERT_PG(1, ModAssert::IfSuccess(off), true);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Verify_Success_And_Off_Not_Displayed)
{
	EXPECT_NO_FAILURE;
	MOD_VERIFY_G(ModAssert::IfSuccess(off), true);
	META_ASSERT(!CheckLoggerCalled());

	MOD_VERIFY_PG(1, ModAssert::IfSuccess(off), true);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Check_Success_And_Off_Not_Displayed)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_CHECK_G(ModAssert::IfSuccess(off), true, ++a);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(!CheckLoggerCalled());

	MOD_CHECK_PG(a, ModAssert::IfSuccess(off), true, ++a);
	META_ASSERT(rbEQUAL(a,1));
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Check_NoPass_Success_And_Off_Not_Displayed)
{
	int a=1;

	EXPECT_NO_FAILURE;
	MOD_CHECK_G(ModAssert::IfSuccess(off), a==0, ++a);
	META_ASSERT(rbEQUAL(a,2));
	META_ASSERT(!CheckLoggerCalled());

	MOD_CHECK_PG(a, ModAssert::IfSuccess(off), a==0, ++a);
	META_ASSERT(rbEQUAL(a,3));
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	ModAssert::MakeGroupList(reportAll % ModAssert::Error);
	EXPECT_ASSERT_G(true, "true", NULL, NULL, reportAll % ModAssert::Error, NULL);
	MOD_ASSERT_G(reportAll, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());

	EXPECT_ASSERT_G(true, "true", NULL, CreateParameterList()("1", 1), reportAll % ModAssert::Error, NULL);
	MOD_ASSERT_PG(1, reportAll, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_And_Level_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	ModAssert::MakeGroupList(reportAll % ModAssert::Error);
	EXPECT_ASSERT_G(true, "true", NULL, NULL, reportAll % ModAssert::Error, NULL);
	MOD_ASSERT_G(reportAll % ModAssert::Error, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

static ModAssert::Category<ModAssert::Assertions> assertions;

MA_TEST(ReportAll_TurnOffDisplayForSuccess)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(1, false);
	META_ASSERT(reportAll.GetDisplay(true)== false);
	META_ASSERT(reportAll.GetDisplay(false)==true );
}

MA_TEST(ReportAll_TurnOffDisplayForAll)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(0, false);
	META_ASSERT(reportAll.GetDisplay(true)== false);
	META_ASSERT(reportAll.GetDisplay(false)==false);
}

MA_TEST(ReportAll_TurnOffDisplayForSuccess_WithIndex)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(1, false);
	META_ASSERT(reportAll.GetDisplay(true)== false);
	META_ASSERT(reportAll.GetDisplay(false)==true );
}

MA_TEST(ReportAll_TurnOffDisplayForAll_WithIndex)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(0, false);
	META_ASSERT(reportAll.GetDisplay(true)== false);
	META_ASSERT(reportAll.GetDisplay(false)==false);
}

MA_TEST(ReportAll_TurnOnDisplayForAll)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(0, false);
	reportAll.SetDisplay(1, true);
	META_ASSERT(reportAll.GetDisplay(true)== true);
	META_ASSERT(reportAll.GetDisplay(false)==true );
}

MA_TEST(ReportAll_TurnOnDisplayForFailure)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetDisplay(0, false);
	reportAll.SetDisplay(0, true);
	META_ASSERT(reportAll.GetDisplay(true)== false);
	META_ASSERT(reportAll.GetDisplay(false)==true);
}

MA_TEST(ReportAll_TurnOffLogForSuccess)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetLog(1, false);
	META_ASSERT(reportAll.GetLog(true)== false);
	META_ASSERT(reportAll.GetLog(false)==true );
}

MA_TEST(ReportAll_TurnOffLogForAll)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetLog(0, false);
	META_ASSERT(reportAll.GetLog(true)== false);
	META_ASSERT(reportAll.GetLog(false)==false);
}

MA_TEST(ReportAll_TurnOnLogForAll)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetLog(0, false);
	reportAll.SetLog(1, true);
	META_ASSERT(reportAll.GetLog(true)== true);
	META_ASSERT(reportAll.GetLog(false)==true );
}

MA_TEST(ReportAll_TurnOnLogForFailure)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	reportAll.SetLog(0, false);
	reportAll.SetLog(0, true);
	META_ASSERT(reportAll.GetLog(true)== false);
	META_ASSERT(reportAll.GetLog(false)==true);
}

MA_TEST(ReportAll_Names)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	META_ASSERT(rbEQUAL(reportAll.GetName(0), "all (nok)"));
	META_ASSERT(rbEQUAL(reportAll.GetName(1), "all (ok)"));
}

MA_TEST(Assert_ReportAll_Displayed_NotLogged)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");
	reportAll.SetLog(1, false);

	EXPECT_ASSERT_G(true, "true", NULL, NULL, reportAll % ModAssert::Error, NULL);
	MOD_ASSERT_G(reportAll, true);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_And_Level_Displayed_NotLogged)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");
	reportAll.SetLog(1, false);

	EXPECT_ASSERT_G(true, "true", NULL, NULL, reportAll % ModAssert::Error, NULL);
	MOD_ASSERT_G(reportAll % ModAssert::Error, true);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_Logged_NotDisplayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");
	reportAll.SetDisplay(1, false);

	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(reportAll, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_And_Level_Logged_NotDisplayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");
	reportAll.SetDisplay(1, false);

	EXPECT_NO_FAILURE;
	MOD_ASSERT_G(reportAll % ModAssert::Error, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_And_IfSuccess_And_Level_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	ModAssert::MakeGroupList((reportAll&&ModAssert::IfSuccess)%ModAssert::Error);
	EXPECT_ASSERT_G(true, "true", NULL, NULL, (reportAll&&ModAssert::IfSuccess)%ModAssert::Error, NULL);
	MOD_ASSERT_G((reportAll&&ModAssert::IfSuccess)%ModAssert::Error, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_ReportAll_And_IfSuccess_And_Level0_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> reportAll("all");

	EXPECT_NO_FAILURE;
	MOD_ASSERT_G((reportAll&&ModAssert::IfSuccess)%ModAssert::Info, true);
	META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_OneReportAll_And_TwoReportFailure_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1"), f2("f2");

	ModAssert::MakeGroupList(all1(f1 && f2));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, all1(f1 && f2), NULL);
	MOD_ASSERT_G(all1(f1 && f2), true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_OneReportAll_And_TwoReportFailure_AndLevel_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1"), f2("f2");

	ModAssert::MakeGroupList(all1(f1 && f2));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, all1(f1 && f2)%ModAssert::Fatal, NULL);
	MOD_ASSERT_G(all1(f1 && f2)%ModAssert::Fatal, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_TwoReportAll_And_OneReportFailure_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1"), all2("all 2");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1");

	ModAssert::MakeGroupList((all1 && all2)(f1));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, (all1 && all2)(f1), NULL);
	MOD_ASSERT_G((all1 && all2)(f1), true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_TwoReportAll_And_OneReportFailure_AndLevel_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1"), all2("all 2");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1");

	ModAssert::MakeGroupList((all1 && all2)(f1));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, (all1 && all2)(f1)%ModAssert::Fatal, NULL);
	MOD_ASSERT_G((all1 && all2)(f1)%ModAssert::Fatal, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_TwoReportAll_And_TwoReportFailure_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1"), all2("all 2");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1"), f2("f2");

	ModAssert::MakeGroupList((all1 && all2)(f1 && f2));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, (all1 && all2)(f1 && f2), NULL);
	MOD_ASSERT_G((all1 && all2)(f1 && f2), true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}

MA_TEST(Assert_TwoReportAll_And_TwoReportFailure_AndLevel_Displayed)
{
	ModAssert::Group<ModAssert::ReportAll> all1("all 1"), all2("all 2");
	ModAssert::Group<ModAssert::ReportFailure> f1("f1"), f2("f2");

	ModAssert::MakeGroupList((all1 && all2)(f1 && f2));
	EXPECT_ASSERT_G(true, "true", NULL, NULL, (all1 && all2)(f1 && f2)%ModAssert::Fatal, NULL);
	MOD_ASSERT_G((all1 && all2)(f1 && f2)%ModAssert::Fatal, true);
	if (MOD_ASSERT_REPORTS)
		META_ASSERT(CheckLoggerCalled());
	else
		META_ASSERT(!CheckLoggerCalled());
}
