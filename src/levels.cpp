//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/levels.hpp"

namespace ModAssert
{
	Level<detail::L_<0> > Info;
	Level<detail::L_<1> > Warning;
	Level<detail::L_<2> > Error;
	Level<detail::L_<3> > Fatal;

	static const RichBool::detail::String
		InfoName = "Level: Info",
		WarningName = "Level: Warning",
		ErrorName = "Level: Error",
		FatalName = "Level: Fatal",
		OtherName = "Level X";

	const RichBool::detail::String& GetLevelName(int level)
	{
		switch (level)
		{
		case 0: return InfoName;
		case 1: return WarningName;
		case 2: return ErrorName;
		case 3: return FatalName;
		default: return OtherName;
		}
	}
}














