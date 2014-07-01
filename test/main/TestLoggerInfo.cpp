//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "GetStreamString.h"
#include "StubLogger.h"

#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/filters.hpp"
#include "modassert/logtype.hpp"
#include "richbool/richbool.hpp"


class StubInfo: public InfoProviders::InfoProvider
{
	RichBool::detail::String name;
public:
	StubInfo(const RichBool::detail::String& name_, InfoProviders::Granularity type):
		InfoProviders::InfoProvider(type),
		name(name_)
	{}
	virtual const RichBool::detail::String& GetType() const
	{
		return name;
	}
	virtual RichBool::detail::String GetInfo() const
	{
		return "info";
	}
};

class VolatileInfo: public StubInfo
{
public:
	VolatileInfo(const RichBool::detail::String& name_):
		StubInfo(name_, InfoProviders::volatileInfo)
	{}
};

class ProcessSpecificInfo: public StubInfo
{
public:
	ProcessSpecificInfo(const RichBool::detail::String& name_):
		StubInfo(name_, InfoProviders::process)
	{}
};

class ApplicationSpecificInfo: public StubInfo
{
public:
	ApplicationSpecificInfo(const RichBool::detail::String& name_):
		StubInfo(name_, InfoProviders::application)
	{}
};

class ThreadSpecificInfo: public StubInfo
{
public:
	ThreadSpecificInfo(const RichBool::detail::String& name_):
		StubInfo(name_, InfoProviders::thread)
	{}
};

class MachineSpecificInfo: public StubInfo
{
public:
	MachineSpecificInfo(const RichBool::detail::String& name_):
		StubInfo(name_, InfoProviders::machine)
	{}
};

static VolatileInfo volatileInfo1("volatileinfo1"), volatileInfo2("volatileinfo2");
static ThreadSpecificInfo threadSpecificInfo("threadinfo");
static ProcessSpecificInfo processSpecificInfo("processinfo");
static ApplicationSpecificInfo applicationSpecificInfo("appinfo");
static MachineSpecificInfo machineSpecificInfo("machineinfo");

MA_TEST(DefaultInfoUser_HasOnlyThreadSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	META_ASSERT( memLogger.HasGranularity(InfoProviders::thread));
	META_ASSERT(!memLogger.HasGranularity(InfoProviders::application));
	META_ASSERT(!memLogger.HasGranularity(InfoProviders::process));
	META_ASSERT(!memLogger.HasGranularity(InfoProviders::machine));
}

MA_TEST(InfoUser_AddGranularity)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.AddGranularity(InfoProviders::process);

	META_ASSERT(memLogger.HasGranularity(InfoProviders::process));
}

MA_TEST(InfoUser_AddAndRemoveGranularity)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.AddGranularity(InfoProviders::process);
	memLogger.RemoveGranularity(InfoProviders::process);

	META_ASSERT(!memLogger.HasGranularity(InfoProviders::process));
}

MA_TEST(DefaultInfoUser_With_VolatileInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(DefaultInfoUser_With_ThreadSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	// this is different from other info: by default, threadSpecificInfo specific info is used
	META_ASSERT( memLogger.ShouldUseInfo(threadSpecificInfo, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(threadSpecificInfo, InfoProviders::Always));
}

MA_TEST(DefaultInfoUser_With_AppSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(DefaultInfoUser_With_ProcessSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	META_ASSERT( memLogger.ShouldUseInfo(processSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(processSpecificInfo, InfoProviders::Always));
}

MA_TEST(DefaultInfoUser_With_MachineSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	META_ASSERT( memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiAppInfoUser_With_VolatileInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::application);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(MultiAppInfoUser_With_AppSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::application);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiAppInfoUser_With_MachineSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::application);

	META_ASSERT( memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiProcessInfoUser_With_VolatileInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::process);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(MultiProcessInfoUser_With_AppSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::process);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiProcessInfoUser_With_ProcessSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::process);

	META_ASSERT( memLogger.ShouldUseInfo(processSpecificInfo, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(processSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiMachineInfoUser_With_VolatileInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::machine);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(MultiMachineInfoUser_With_AppSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::machine);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(MultiMachineInfoUser_With_MachineSpecificInfo)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	memLogger.AddGranularity(InfoProviders::machine);

	META_ASSERT( memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(machineSpecificInfo, InfoProviders::Always));
}

MA_TEST(InfoProviderIncludedOnce)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(volatileInfo1, InfoProviders::Once);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(InfoProviderExcluded)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(volatileInfo1, InfoProviders::Never);

	META_ASSERT(!memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(InfoProviderIncluded)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(volatileInfo1, InfoProviders::Always);

	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(volatileInfo1, InfoProviders::Always));
}

MA_TEST(AppInfoProviderIncluded)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(applicationSpecificInfo, InfoProviders::Always);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(AppInfoProviderIncludedOnce)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(applicationSpecificInfo, InfoProviders::Once);

	META_ASSERT( memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(AppInfoProviderExcluded)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);

	memLogger.UseInfo(applicationSpecificInfo, InfoProviders::Never);

	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Once));
	META_ASSERT(!memLogger.ShouldUseInfo(applicationSpecificInfo, InfoProviders::Always));
}

MA_TEST(StreamLoggerWithInfoProvider)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&volatileInfo1);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+"volatileinfo1: info"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderNotShown)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&applicationSpecificInfo);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&applicationSpecificInfo);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithTwoInfoProviders)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&volatileInfo1);
	ModAssert::AddInfoProvider(&volatileInfo2);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);
	ModAssert::RemoveInfoProvider(&volatileInfo2);

	ModAssert::Context context(__FILE__, __LINE__-6, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+"volatileinfo1: info"+NewLine()+"volatileinfo2: info"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithTwoInfoProviders_FirstNotShown)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&applicationSpecificInfo);
	ModAssert::AddInfoProvider(&volatileInfo1);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);
	ModAssert::RemoveInfoProvider(&applicationSpecificInfo);

	ModAssert::Context context(__FILE__, __LINE__-6, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+"volatileinfo1: info"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithTwoInfoProviders_SecondNotShown)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&volatileInfo1);
	ModAssert::AddInfoProvider(&applicationSpecificInfo);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);
	ModAssert::RemoveInfoProvider(&applicationSpecificInfo);

	ModAssert::Context context(__FILE__, __LINE__-6, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+"volatileinfo1: info"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderWithFilterAccept)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&volatileInfo1, &ModAssert::filterIfAssertion);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+"volatileinfo1: info"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderWithFilterReject)
{
	MemOutStream memStream;
	ModAssert::StreamLogger memLogger(&memStream);
	NoMessagesLogger logger(memLogger);
	ModAssert::AddLogger(&logger);

	ModAssert::AddInfoProvider(&volatileInfo1, &ModAssert::filterIfCheck);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);
	RichBool::detail::String str;

	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}

	EXPECT_NO_FAILURE;
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderAtBeginAndEnd)
{
	ModAssert::AddInfoProvider(&volatileInfo1);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderAtBegin)
{
	ModAssert::AddInfoProvider(&applicationSpecificInfo);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&applicationSpecificInfo);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"appinfo: info"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderExcludeNone)
{
	ModAssert::AddInfoProvider(&applicationSpecificInfo);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	logger.UseInfo(applicationSpecificInfo, InfoProviders::Always);
	ModAssert::AddLogger(&logger);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&applicationSpecificInfo);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"appinfo: info"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"appinfo: info"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderExcludeAtEnd)
{
	ModAssert::AddInfoProvider(&volatileInfo1);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	logger.UseInfo(volatileInfo1, InfoProviders::Once);
	ModAssert::AddLogger(&logger);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderFilterOutAtBegin)
{
	ModAssert::FilterLogType filter(true, false, true, true);
	ModAssert::AddInfoProvider(&volatileInfo1, &filter);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+NewLine();
	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+
			"volatileinfo1: info"+NewLine()+NewLine();
	}
	str += "ModAssert stops logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderFilterOutAtEnd)
{
	ModAssert::FilterLogType filter(true, true, false, true);
	ModAssert::AddInfoProvider(&volatileInfo1, &filter);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+NewLine();
	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+
			"volatileinfo1: info"+NewLine()+NewLine();
	}
	str += "ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLoggerWithInfoProviderFilterOutOnAssert)
{
	ModAssert::AddInfoProvider(&volatileInfo1, &ModAssert::filterMessages);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);
	ModAssert::RemoveInfoProvider(&volatileInfo1);

	ModAssert::Context context(__FILE__, __LINE__-5, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+NewLine();
	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}
	str += "ModAssert stops logging here"+NewLine()+
		"volatileinfo1: info"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLogger_FilterOutOnBegin)
{
	ModAssert::FilterLogType filter(true, false, true, true);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger, &filter);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-4, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str;
	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}
	str += "ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLogger_FilterOutOnEnd)
{
	ModAssert::FilterLogType filter(true, true, false, true);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger, &filter);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-4, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"using the filter assertions, at begin, not at end, in between"+NewLine()+NewLine();
	if (MOD_ASSERT_REPORTS)
	{
		str += RichBool::ToString(context);
		str += " assertion false failed"+NewLine()+"no analysis"+NewLine()+
			"Level: Error"+NewLine()+NewLine();
	}
	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}

MA_TEST(StreamLogger_FilterOutOnAssert)
{
	ModAssert::FilterLogType filter(false, true, true, true);

	MemOutStream memStream;
	ModAssert::StreamLogger logger(&memStream);
	ModAssert::AddLogger(&logger, &filter);

	EXPECT_ASSERT(false, "false", NULL, NULL, NULL);
	MOD_ASSERT(false);

	ModAssert::RemoveLogger(&logger);

	ModAssert::Context context(__FILE__, __LINE__-4, MOD_ASSERT_FUNCTION);

	RichBool::detail::String str = "************************************************************"+NewLine()+
		"ModAssert starts logging here"+NewLine()+
		"using the filter no assertions, at begin, at end, in between"+NewLine()+NewLine()+
		"ModAssert stops logging here"+NewLine()+
		"------------------------------------------------------------"+NewLine();

	META_ASSERT(rbSTRING(str, ==, GetStreamString(memStream), STRINGCMP));
}
