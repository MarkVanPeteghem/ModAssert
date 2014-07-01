//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/handler.hpp"
#include "modassert/strmlog.hpp"
#include "modassert/timeinfo.hpp"
#include "modassert/infostore.hpp"
#include "modassert/filters.hpp"

#include "modassert/consolehandler.hpp"
#include "modassert/consoledisplayer.hpp"
#include "modassert/consoleterminate.hpp"
#include "modassert/consolewarning.hpp"

#ifdef RICHBOOL_USE_WX
#include <wx/wfstream.h>
#else
#include <iostream>
#endif

namespace ModAssert
{
#ifdef RICHBOOL_USE_WX
	static wxFFileOutputStream output(stdout);
	static wxTextOutputStream out(output);

	static wxFFileOutputStream erroutput(stderr);
	static wxTextOutputStream errout(erroutput);

	static wxFFileInputStream input(stdin);
	static wxTextInputStream in(input);

	static ConsoleDisplayer s_displayer(&in, &out);
	static StreamLogger s_logger(&errout);

	static ConsoleTerminateMessage s_terminateWarning(&out, &input);
	static ConsoleWarningMessage s_warningMessage(&out, &input);
#else
	static ConsoleDisplayer s_displayer(&std::cin, &std::cout);
	static StreamLogger s_logger(&std::cerr);
	static ConsoleTerminateMessage s_terminateWarning(&std::cout, &std::cin);
	static ConsoleWarningMessage s_warningMessage(&std::cout, &std::cin);
#endif

	static InfoProviders::TimeInfoProvider s_timeInfoProvider;
	static FilterLogType
		s_filterShowOnlyAssertions(true, false, false, false);

	static void AddConsoleSpecific()
	{
		AddInfoProvider(&s_timeInfoProvider);
		AddLogger(&s_logger, &s_filterShowOnlyAssertions);
	}

	void SetupForConsole()
	{
		AddConsoleSpecific();
		Setup(&s_displayer);
	}

	void SetupForConsole(Mode mode)
	{
		AddConsoleSpecific();
		Setup(mode, &s_displayer, &s_warningMessage, &s_terminateWarning);
	}

	void SetConsoleHandler()
	{
		AddInfoProvider(&s_timeInfoProvider);

		SetResponder(&s_displayer);
		AddLogger(&s_logger);
	}

	Responder& GetConsoleDisplayer()
	{
		return s_displayer;
	}

	Logger& GetScreenLogger()
	{
		return s_logger;
	}

	const InfoProviders::InfoProvider& GetConsoleTimeInfoProvider()
	{
		return s_timeInfoProvider;
	}
}
