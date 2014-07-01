//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_HANDLER_CONSOLE_H__QM
#define MOD_ASSERT_HANDLER_CONSOLE_H__QM

#include "modassert/linkcore.hpp"

#define BOOST_LIB_NAME modassertConsole
#include "modassert/version.hpp"
#include "richbool/auto_link.hpp"


namespace InfoProviders
{
	class InfoProvider;
}

namespace ModAssert
{
	void SetupForConsole();
	void SetupForConsole(Mode mode);

	// deprecated alternative of SetupForConsole
	void SetConsoleHandler();

	class Responder;
	class Logger;

	Responder& GetConsoleDisplayer();
	Logger& GetScreenLogger();
	const InfoProviders::InfoProvider& GetConsoleTimeInfoProvider();
}

#endif //#ifndef MOD_ASSERT_HANDLER_CONSOLE_H__QM
