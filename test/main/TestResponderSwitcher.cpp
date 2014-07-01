//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "modassert/responder_switcher.hpp"
#include "richbool/richbool.hpp"
#include "modassert/filters.hpp"


MA_TEST(Default)
{
	ModAssert::ResponderSwitcher ar;

	ModAssert::Response response =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response, 0));
}

MA_TEST(Default_HasResponse)
{
	ModAssert::ResponderSwitcher ar;

	META_ASSERT(ar.HasDefaultResponse());
	META_ASSERT(rbEQUAL(ar.GetDefaultResponse(), ModAssert::Response(0)));
	META_ASSERT(!ar.HasDefaultResponder());
}

MA_TEST(RespondExit)
{
	ModAssert::ResponderSwitcher ar;
	ar.SetDefaultResponse(ModAssert::Exit);

	ModAssert::Response response =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response, ModAssert::Exit));
}

MA_TEST(Responder_RespondExit)
{
	ModAssert::ResponderSwitcher ar, ar2;

	ar2.SetDefaultResponse(ModAssert::Exit);
	ar.SetDefaultResponder(&ar2);

	ModAssert::Response response =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response, ModAssert::Exit));
}

MA_TEST(Responder_RespondExit_HasResponder)
{
	ModAssert::ResponderSwitcher ar, ar2;

	ar2.SetDefaultResponse(ModAssert::Exit);
	ar.SetDefaultResponder(&ar2);

	META_ASSERT(ar.HasDefaultResponder());
	META_ASSERT(ar.GetDefaultResponder()==&ar2);
	META_ASSERT(!ar.HasDefaultResponse());
}

MA_TEST(OneFilter_WithConstResponse)
{
	ModAssert::FilterIfFailed ifFailed;

	ModAssert::ResponderSwitcher ar;
	ar.SetDefaultResponse(ModAssert::Exit);
	ar.AddFilter(&ifFailed, ModAssert::Optional);

	ModAssert::Response response1 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response1, ModAssert::Optional));

	ModAssert::Response response2 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(true, 0, 0), false);
	META_ASSERT(rbEQUAL(response2, ModAssert::Exit));
}

MA_TEST(TwoFilters_WithConstResponse)
{
	ModAssert::FilterIfFailed ifFailed;
	ModAssert::FilterMinimumLevel minLevel(ModAssert::Error);

	ModAssert::ResponderSwitcher ar;
	ar.SetDefaultResponse(ModAssert::Exit);
	ar.AddFilter(&ifFailed, ModAssert::Optional);
	ar.AddFilter(&minLevel, ModAssert::StopDisplayingThis);

	ModAssert::Response response1 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response1, ModAssert::Optional));

	ModAssert::Response response2 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(true, 0, 0), false);
	META_ASSERT(rbEQUAL(response2, ModAssert::Exit));

	const ModAssert::GroupList &groupListError = ModAssert::MakeGroupList(ModAssert::Error);

	ModAssert::Response response3 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, &groupListError, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response3, ModAssert::Optional));

	ModAssert::Response response4 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, &groupListError, 0),
			ModAssert::Result(true, 0, 0), false);
	META_ASSERT(rbEQUAL(response4, ModAssert::StopDisplayingThis));
}

struct StubResponder: public ModAssert::Responder
{
	StubResponder(ModAssert::Response r): response(r) {}

	ModAssert::Response response;

	virtual ModAssert::Response OnAssert(
		const ModAssert::Properties &,
		const ModAssert::Result &,
		bool ) const
	{
		return response;
	}
};

MA_TEST(OneFilter_WithResponder)
{
	ModAssert::FilterIfFailed ifFailed;

	StubResponder sr(ModAssert::Optional);

	ModAssert::ResponderSwitcher ar;
	ar.SetDefaultResponse(ModAssert::Exit);
	ar.AddFilter(&ifFailed, &sr);

	ModAssert::Response response1 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(false, 0, 0), false);
	META_ASSERT(rbEQUAL(response1, ModAssert::Optional));

	ModAssert::Response response2 =
		ar.OnAssert(ModAssert::Properties(0, MOD_ASSERT_CONTEXT, 0, 0, 0),
			ModAssert::Result(true, 0, 0), false);
	META_ASSERT(rbEQUAL(response2, ModAssert::Exit));
}
