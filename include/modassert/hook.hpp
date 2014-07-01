//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef HOOK_H__QM
#define HOOK_H__QM

namespace ModAssert
{
	class Properties;
	class Result;

	// abstract base class for objects that need to perform an action
	// before the assertion is handled
	class Hook
	{
	public:
		virtual ~Hook() {}
		virtual void OnAssert(
			const Properties &properties,
			const Result &assertionResult) const = 0;
	};
}

#endif // #ifndef HOOK_H__QM

