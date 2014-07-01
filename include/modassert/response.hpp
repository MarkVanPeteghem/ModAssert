//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RESPONSE_H__QM
#define RESPONSE_H__QM

namespace ModAssert
{
	typedef unsigned short Response;

	const Response
		Exit                  = 0x0001,
		Optional              = 0x0002,
		GlobalOptional        = 0x0004,
		BreakIntoDebugger     = 0x0008,
		StopDisplayingThis    = 0x0010,
		StopDisplayingFile    = 0x0020,
		StopDisplayingAll     = 0x0040,
		StopDisplayingCustom1 = 0x0080,
		StopDisplayingCustom2 = 0x0100,
		StopDisplayingCustom3 = 0x0200,
		StopDisplayingCustom4 = 0x0400,
		StopDisplayingCustom5 = 0x0800,
		StopDisplayingCustom6 = 0x1000,
		StopDisplayingCustom7 = 0x2000,
		StopDisplayingCustom8 = 0x4000;
	const int maxNrCustomResponses = 8;
}

#endif // #ifndef RESPONSE_H__QM












