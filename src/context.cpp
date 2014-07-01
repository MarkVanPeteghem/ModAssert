//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/context.hpp"

namespace ModAssert
{
	Context::Context(const Context &context):
		file_(context.file_), line_(context.line_), func_(context.func_)
	{}

	Context& Context::operator=(const Context &context)
	{
		file_ = context.file_;
		line_ = context.line_;
		func_ = context.func_;
		return *this;
	}

	void Context::streamout(RichBool::detail::OutStream &stream) const
	{
	#ifdef _MSC_VER
		stream << file_ << '(' << line_ << "):";
	#else
		stream << file_ << ':' << line_ << ':';
	#endif
        if (func_ && *func_)
                stream << " in " << func_;
	}

	RB_CONVERSION_HEADER(Context)
	{
		val.streamout(str);
		return str;
	}
}















