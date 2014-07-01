//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef APP_INFO_H__QM
#define APP_INFO_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class ApplicationInfoProvider: public InfoProvider
	{
	public:
		ApplicationInfoProvider(const RichBool::detail::String &name_):
			InfoProvider(application),
			name(name_)
		{}

		virtual ~ApplicationInfoProvider();

		virtual const RichBool::detail::String& GetType() const;
		virtual RichBool::detail::String GetInfo() const;

	private:
		RichBool::detail::String name;
	};
}

#endif // #ifndef APP_INFO_H__QM
