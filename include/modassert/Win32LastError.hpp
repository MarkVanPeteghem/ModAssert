//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_LAST_ERROR_H__QM
#define MOD_ASSERT_LAST_ERROR_H__QM

#include "modassert/info.hpp"
#include "modassert/hook.hpp"

namespace InfoProviders
{
	// Important note: this class can't be used without
	// the class ModAssert::LastErrorHook, which assigns
	// the return value of GetLastError() to a variable,
	// that is used later by LastErrorInfoProvider.
	// This is necessary because in ModAssert we usually
	// write to a file before LastErrorInfoProvider is called,
	// so the return value of GetLastError() would always be 0.
	class LastErrorInfoProvider: public InfoProvider
	{
	public:
		LastErrorInfoProvider(): InfoProvider(volatileInfo) {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;
		virtual bool HasInfo() const;
	};
}

namespace ModAssert
{
	class LastErrorHook: public Hook
	{
	public:
		virtual void OnAssert(const Properties &properties,
	                          const Result &result) const;
	};
}

#endif // #ifndef MOD_ASSERT_LAST_ERROR_H__QM














