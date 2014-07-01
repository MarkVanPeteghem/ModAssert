//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef INFO_H__QM
#define INFO_H__QM

#include "richbool/portability.hpp"

namespace InfoProviders
{
	enum Granularity { volatileInfo, thread, process,
        application, machine, customGranularity };

	// abstract base class for objects that provide relevant information
	class InfoProvider
	{
	public:
		InfoProvider(enum Granularity granularity);

		virtual ~InfoProvider() {}

		virtual const RichBool::detail::String& GetType() const = 0;
		virtual RichBool::detail::String GetInfo() const = 0;
		virtual bool HasInfo() const;

		Granularity GetGranularity() const
		{
			return granularity;
		}

	private:
		Granularity granularity;
	};
}

#endif // #ifndef INFO_H__QM
