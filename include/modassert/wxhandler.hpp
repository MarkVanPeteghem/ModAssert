//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_HANDLER_WX_H__QM
#define MOD_ASSERT_HANDLER_WX_H__QM

#include "modassert/handler.hpp"

#include "modassert/linkcore.hpp"

#define BOOST_LIB_NAME modassertGui
#include "modassert/version.hpp"
#include "richbool/auto_link.hpp"

namespace InfoProviders
{
	class InfoProvider;
}

namespace ModAssert
{
	void SetupForWxWidgets();
	void SetupForWxWidgets(Mode mode);
	
	// deprecated alternative for SetupForWxWidgets:
	void SetWxHandler();

	class Responder;
	class Logger;

	Responder& GetWxDisplayer();
	Logger& GetWxLogger();
	InfoProviders::InfoProvider& GetWxThreadIdInfoProvider();
	InfoProviders::InfoProvider& GetWxTimeInfoProvider();
	InfoProviders::InfoProvider& GetWxProcessIdInfoProvider();
	InfoProviders::InfoProvider& GetWxOsVersionInfoProvider();
	InfoProviders::InfoProvider& GetWxCurrentDirectoryInfoProvider();
	InfoProviders::InfoProvider& GetWxFreeMemoryInfoProvider();
	InfoProviders::InfoProvider& GetWxSysErrorInfoProvider();
}

#endif //#ifndef MOD_ASSERT_HANDLER_WX_H__QM
