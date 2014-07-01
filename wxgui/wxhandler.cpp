//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/handler.hpp"
#include "modassert/infostore.hpp"
#include "modassert/timeinfo.hpp"

#include "modassert/wxhandler.hpp"
#include "modassert/wxdisplayer.hpp"
#include "modassert/wxlog.hpp"
#include "modassert/wxthreadid.hpp"
#include "modassert/wxprocessid.hpp"
#include "modassert/wxosversion.hpp"
#include "modassert/wxcurrentdirectory.hpp"
#include "modassert/wxfreememory.hpp"
#include "modassert/wxsyserror.hpp"
#include "modassert/wxterminatemessage.hpp"
#include "modassert/wxwarningmessage.hpp"

namespace ModAssert
{
	static WxDisplayer s_wxResponder;
	static WxLog s_modAssertWxLog;
	static WxTerminateMessage s_terminateMessage;
	static WxWarningMessage s_warningMessage;
	
	static InfoProviders::WxThreadIdInfoProvider s_threadIdInfoProvider;
	static InfoProviders::TimeInfoProvider s_timeInfoProvider;
	static InfoProviders::WxProcessIdInfoProvider s_processIdInfoProvider;
	static InfoProviders::WxOsVersionInfoProvider s_osVersionInfoProvider;
	static InfoProviders::WxCurrentDirectoryInfoProvider s_currentDirectoryInfoProvider;
	static InfoProviders::WxFreeMemoryInfoProvider s_freeMemoryInfoProvider;
	static InfoProviders::WxSysErrorInfoProvider s_sysErrorInfoProvider;
	static WxSysErrorHook s_sysErrorHook;

	void SetupForWxWidgets()
	{
		SetWxHandler();
		Setup(&s_wxResponder);
	}

	void SetupForWxWidgets(Mode mode)
	{
		SetWxHandler();
		Setup(mode, &s_wxResponder, &s_warningMessage, &s_terminateMessage);
	}

	void SetWxHandler()
	{
		AddInfoProvider(&s_sysErrorInfoProvider);
		AddHook(&s_sysErrorHook);
		AddInfoProvider(&s_timeInfoProvider);
		AddInfoProvider(&s_threadIdInfoProvider);
		AddInfoProvider(&s_processIdInfoProvider);
		AddInfoProvider(&s_osVersionInfoProvider);
		AddInfoProvider(&s_currentDirectoryInfoProvider);
		AddInfoProvider(&s_freeMemoryInfoProvider);

		// add logger after infoproviders, so the information in them
		// is logged to it
		AddLogger(&s_modAssertWxLog);
	}

	Responder& GetWxDisplayer()
	{
		return  s_wxResponder;
	}

	Logger& GetWxLogger()
	{
		return  s_modAssertWxLog;
	}

	InfoProviders::InfoProvider& GetWxThreadIdInfoProvider()
	{
		return  s_threadIdInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxTimeInfoProvider()
	{
		return  s_timeInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxProcessIdInfoProvider()
	{
		return  s_processIdInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxOsVersionInfoProvider()
	{
		return  s_osVersionInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxCurrentDirectoryInfoProvider()
	{
		return  s_currentDirectoryInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxFreeMemoryInfoProvider()
	{
		return  s_freeMemoryInfoProvider;
	}

	InfoProviders::InfoProvider& GetWxSysErrorInfoProvider()
	{
		return  s_sysErrorInfoProvider;
	}
}
