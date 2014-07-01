//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MODASSERT_WIN32_RESPONDER_H__QM
#define MODASSERT_WIN32_RESPONDER_H__QM

#include "modassert/responder.hpp"
#include <windows.h>

namespace ModAssert
{
	class Win32Displayer: public Responder
	{
	public:
		Win32Displayer();

		static HINSTANCE GetInstance() { return hInstance; }
		static void SetInstance(HINSTANCE hInstance_)
		{
			hInstance = hInstance_;
		};

	protected:
		virtual Response OnAssert(
			const Properties &properties,
			const Result &result,
			bool display) const;

		static HINSTANCE hInstance;
	};
}

#endif // #ifndef MODASSERT_WIN32_RESPONDER_H__QM
