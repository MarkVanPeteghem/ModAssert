//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RESPONDER_SWITCHER_H__QM
#define RESPONDER_SWITCHER_H__QM

#include "modassert/responder.hpp"

#if defined(RICHBOOL_USE_WX)
	#include "wx/dynarray.h"
#else
	#include <vector>
#endif

namespace ModAssert
{
	class Filter;

	namespace detail
	{
		struct GetResponse
		{
			virtual ~GetResponse() {}
			enum Type { eConst, eResponder };
			virtual Response OnAssert(
				const Properties &properties,
				const Result &assertionResult,
				bool display) const = 0;
			virtual Type GetType() const =0;
		};

		struct ConstResponse: public GetResponse
		{
			ConstResponse(Response response_): response(response_)
			{}
			Response response;

			virtual Response OnAssert(
				const Properties &,
				const Result &,
				bool ) const
			{
				return response;
			}
			virtual Type GetType() const
			{
				return eConst;
			}
		};

		struct CallResponder: public GetResponse
		{
			CallResponder(const Responder *responder_):
				responder(responder_)
			{}
			const Responder *responder;

			virtual Response OnAssert(
				const Properties &properties,
				const Result &assertionResult,
				bool display) const
			{
				return responder->OnAssert(properties, assertionResult, display);
			}
			virtual Type GetType() const
			{
				return eResponder;
			}
		};

		struct ResponseFilter
		{
			ResponseFilter(): filter(0), getResponse(0) {}
			ResponseFilter(Filter *filter_, GetResponse *getResponse_):
				filter(filter_), getResponse(getResponse_) {}
			~ResponseFilter() { delete getResponse; }

			Filter *filter;
			GetResponse *getResponse;
		};

	#if defined(RICHBOOL_USE_WX)
		WX_DEFINE_ARRAY_PTR(ResponseFilter*, ResponseFilterArray);
	#else
		typedef std::vector<ResponseFilter*> ResponseFilterArray;
	#endif
	}

	class ResponderSwitcher: public Responder
	{
		detail::ResponseFilterArray responseFilterArray;
		detail::GetResponse *defaultResponse;

	public:
		ResponderSwitcher(): defaultResponse(0)
		{
			SetDefaultResponse(0);
		}
		ResponderSwitcher(const Responder *responder): defaultResponse(0)
		{
			SetDefaultResponder(responder);
		}
		ResponderSwitcher(Response response): defaultResponse(0)
		{
			SetDefaultResponse(response);
		}
		virtual ~ResponderSwitcher();

		virtual Response OnAssert(
			const Properties &properties,
			const Result &assertionResult,
			bool display) const;

		void SetDefaultResponse(Response response);
		void SetDefaultResponder(const Responder *responder);

		bool HasDefaultResponse() const;
		bool HasDefaultResponder() const;
		Response GetDefaultResponse() const;
		const Responder* GetDefaultResponder() const;

		void AddFilter(Filter *filter, Response response);
		void AddFilter(Filter *filter, const Responder *responder);

		size_t size() const
		{
			return RichBool::detail::array_size(responseFilterArray);
		}
	};
}

#endif // #ifndef RESPONDER_SWITCHER_H__QM
