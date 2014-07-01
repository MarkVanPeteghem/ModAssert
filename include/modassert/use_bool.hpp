//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_USE_BOOL_H__QM
#define MOD_ASSERT_USE_BOOL_H__QM

#include "modassert/context.hpp"

namespace ModAssert
{
	// wrapper for boolean with transfer semantics,
	// that checks in the destructor if the value has been used
	class UseBool
	{
	private:
		mutable unsigned char bits;
		Context m_context;

		enum {
			value = 1<<0,
			used = 1<<1,
			owned = 1<<2
		};

		bool getValue() const
		{
			return (bits&value)!=0;
		}
		bool isUsed() const
		{
			return (bits&used)!=0;
		}
		bool isOwned() const
		{
			return (bits&owned)!=0;
		}

		static bool check;

	public:
		UseBool(bool b, const Context &context);

		// Although this copy constructor does a move instead of a copy,
        // we can't use non-const reference here, because it may be
		// the return value of a function call, which is a temporary.
		// This is why bits is mutable.
		UseBool(const UseBool &ub);

		~UseBool();

		operator bool() const;

		static void SetCheck(bool b);
	};
}

#endif // #ifndef MOD_ASSERT_USE_BOOL_H__QM
