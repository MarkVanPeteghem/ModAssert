//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/portability.hpp"
#include "modassert/responder_switcher.hpp"
#include "modassert/filters.hpp"

namespace ModAssert
{
#if defined(RICHBOOL_USE_WX)
	#define push_back Add
	#define size GetCount
#endif

	ResponderSwitcher::~ResponderSwitcher()
	{
		for (size_t i=0; i<RichBool::detail::array_size(responseFilterArray); ++i)
			delete responseFilterArray[i];
		delete defaultResponse;
	}

	Response ResponderSwitcher::OnAssert(
		const Properties &properties,
		const Result &result,
		bool display) const
	{
		for (size_t idx=0; idx<RichBool::detail::array_size(responseFilterArray); ++idx)
		{
			if (responseFilterArray[idx]->filter->Accept(properties, result))
				return responseFilterArray[idx]->getResponse->OnAssert(properties, result, display);
		}
		return defaultResponse->OnAssert(properties, result, display);
	}

	void ResponderSwitcher::SetDefaultResponse(Response response)
	{
		delete defaultResponse;
		defaultResponse = new detail::ConstResponse(response);
	}

	void ResponderSwitcher::SetDefaultResponder(const Responder *responder)
	{
		delete defaultResponse;
		defaultResponse = new detail::CallResponder(responder);
	}

	bool ResponderSwitcher::HasDefaultResponse() const
	{
		return defaultResponse && defaultResponse->GetType()==detail::GetResponse::eConst;
	}

	bool ResponderSwitcher::HasDefaultResponder() const
	{
		return defaultResponse && defaultResponse->GetType()==detail::GetResponse::eResponder;
	}

	Response ResponderSwitcher::GetDefaultResponse() const
	{
		return ((detail::ConstResponse*)defaultResponse)->response;
	}

	const Responder* ResponderSwitcher::GetDefaultResponder() const
	{
		return ((detail::CallResponder*)defaultResponse)->responder;
	}

	void ResponderSwitcher::AddFilter(Filter *filter, Response response)
	{
		responseFilterArray.push_back(new detail::ResponseFilter(filter, new detail::ConstResponse(response)));
	}

	void ResponderSwitcher::AddFilter(Filter *filter, const Responder *responder)
	{
		responseFilterArray.push_back(new detail::ResponseFilter(filter, new detail::CallResponder(responder)));
	}
}
