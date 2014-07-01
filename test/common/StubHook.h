//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef STUB_HOOK_H__QM
#define STUB_HOOK_H__QM

#include "modassert/hook.hpp"

class StubHook: public ModAssert::Hook
{
public:
	StubHook(): called(false)
	{}

	virtual void OnAssert(const ModAssert::Properties &,
			const ModAssert::Result &) const
	{
		called = true;
	}

	bool CheckCalled()
	{
		bool rv = called;
		called = false;
		return rv;
	}

	void Clear()
	{
		called = false;
	}

protected:
	mutable bool called;
};

#endif // #ifndef STUB_HOOK_H__QM














