//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifndef CONTEXT_H__QM
#define CONTEXT_H__QM

#include "richbool/portability.hpp"


// next method is taken and modified from
// the file current_function.hpp in the Boost library

namespace ModAssert
{
	inline void current_function_helper()
	{
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))

# define MOD_ASSERT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define MOD_ASSERT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define MOD_ASSERT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define MOD_ASSERT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define MOD_ASSERT_FUNCTION __func__

#else

# define MOD_ASSERT_FUNCTION (const char*)0

#endif
	}

	class Context
	{
	public:
		Context(const char *file, int line, const char *func):
			file_(file), line_(line), func_(func) {}
		Context(const Context &context);
		Context& operator=(const Context &context);

		virtual ~Context() {}

		const char *file_;
		int line_;
		const char *func_;

		virtual void streamout(RichBool::detail::OutStream &stream) const;
	};

	RB_CONVERSION_HEADER(Context);
}

#define MOD_ASSERT_CONTEXT \
	ModAssert::Context(__FILE__, __LINE__, MOD_ASSERT_FUNCTION)

#endif // #ifndef CONTEXT_H__QM















