//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#define MOD_ASSERT_DEFAULT_GROUP EnabledAssert
#define MOD_CHECK_DEFAULT_GROUP EnabledCheck

#include "ModAssertTest.h"

static ModAssert::Group<ModAssert::ReportFailure> EnabledAssert("enabled assert"),
	EnabledCheck("enabled check");

MA_TEST(ModAssertDefaultGroup)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL, EnabledAssert, NULL);
	MOD_ASSERT(false);
}

MA_TEST(ModVerifyVDefaultGroup)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL, EnabledAssert, NULL);
	MOD_VERIFY_V(false);
}

MA_TEST(ModVerifyBDefaultGroup)
{
	EXPECT_ASSERT_G(false, "false", NULL, NULL, EnabledAssert, NULL);
	bool rv=MOD_VERIFY_B(false);
	rv = !rv; // to avoid warning
}

MA_TEST(ModCheckDefaultGroup)
{
	EXPECT_CHECK_G(false, "false", NULL, NULL, EnabledCheck, NULL);
	MOD_CHECK(false, 0);
}

MA_TEST(ModCheckVDefaultGroup)
{
	EXPECT_CHECK_G(false, "false", NULL, NULL, EnabledCheck, NULL);
	MOD_CHECK_V(false, ModAssert::Nop);
}
