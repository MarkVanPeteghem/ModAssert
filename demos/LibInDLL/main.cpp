//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/assert.hpp"
#include "modassert/handler.hpp"
#include "richbool/richbool.hpp"
#include "richbool/stdstring.hpp"
#include "richbool/containers.hpp"

#include "export.hpp"


int main(int argc, char *argv[])
{
	// If the argument -d is given as an argument,
	// we allow breaking into the debugger. We then provide this argument
	// whenever we launch this application with a debugger, without otherwise.
	bool debugAllowed=false;
	for (int arg=1; arg<argc; ++arg)
	{
		if (strcmp(argv[arg], "-d")==0)
	{
			debugAllowed = true;
			break;
		}
	}

	SetupModAssert(debugAllowed);

	ModAssert::SetState(GetModAssertStateInDll());

	MOD_ASSERT(rbEQUAL(1, 2));

	return 0;
}
