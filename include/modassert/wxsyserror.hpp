//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MODASSERT_WX_SYSERROR_H__QM
#define MODASSERT_WX_SYSERROR_H__QM

#include "modassert/info.hpp"
#include "modassert/hook.hpp"

namespace InfoProviders
{
	// Important note: this class can't be used without
	// the class ModAssert::WxSysErrorHook, which assigns
	// the return value of wxSysErrorCode() to a variable,
	// that is used later by LastErrorInfoProvider.
	// This is necessary because in ModAssert we usually
	// write to a file before WxSysErrorInfoProvider is called,
	// so the return value of wxSysErrorCode() would always be 0.
	class WxSysErrorInfoProvider: public InfoProvider
	{
	public:
		WxSysErrorInfoProvider(): InfoProvider(volatileInfo) {}

		virtual const wxString& GetType() const;
		virtual bool HasInfo() const;
		virtual wxString GetInfo() const;
	};
}

namespace ModAssert
{
	class WxSysErrorHook: public Hook
	{
	public:
		virtual void OnAssert(const Properties &properties,
	                          const Result &result) const;
	};
}

#endif // #ifndef MODASSERT_WX_SYSERROR_H__QM
