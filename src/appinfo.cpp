//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/appinfo.hpp"

namespace InfoProviders
{
	ApplicationInfoProvider::~ApplicationInfoProvider()
	{}

	const RichBool::detail::String& ApplicationInfoProvider::GetType() const
	{
		static const RichBool::detail::String type = "application";
		return type;
	}

	RichBool::detail::String ApplicationInfoProvider::GetInfo() const
	{
		return name;
	}
}
