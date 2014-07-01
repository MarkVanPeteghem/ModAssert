//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MODASSERT_IF_SUCCESS_H__QM
#define MODASSERT_IF_SUCCESS_H__QM

#include "modassert/group.hpp"

namespace ModAssert
{
	namespace detail
	{
		struct IfSuccess
		{
			enum { enabled = true, ifSuccess = true };
			enum { level = 2 };
			enum { size = 0 };

			bool GetDisplay(bool ) const { return true; }
			bool GetDisplay(size_t ) const { return true; }
			void SetDisplay(size_t , bool ) { }

			bool GetLog(bool ) const { return true; }
			bool GetLog(size_t ) const { return true; }
			void SetLog(size_t , bool ) { }

			size_t GetSize() const { return 0; }

			const RichBool::detail::String& GetName(size_t ) const { return noName; }

			bool Has(const char *) const
			{
				// this is an anonymous group
				return false;
			}

		private:
			static const RichBool::detail::String noName;
		};
	}

	extern Group<detail::IfSuccess> IfSuccess;
}

#endif // #ifndef MODASSERT_IF_SUCCESS_H__QM
