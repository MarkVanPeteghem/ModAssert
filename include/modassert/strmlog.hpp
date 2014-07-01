//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef STREAM_LOGGER_H__QM
#define STREAM_LOGGER_H__QM

#include "modassert/logger.hpp"

namespace ModAssert
{
	class StreamLogger: public Logger
	{
	public:
		StreamLogger(RichBool::detail::OutStream *stream);
		virtual ~StreamLogger();

#ifdef RICHBOOL_USE_WX
	public:
		StreamLogger(wxOutputStream *stream);
	protected:
		bool m_ownStream;
#endif

	public:
		virtual void OnAssert(
			const Properties &properties,
			const Result &assertionResult) const;

		virtual void AddMessage(const RichBool::detail::String &msg) const;
	protected:
		RichBool::detail::OutStream *m_stream;
	};


	class AppendToFileLogger: public Logger
	{
		RichBool::detail::String filename;
	public:
		AppendToFileLogger(const RichBool::detail::String &filename_);

		virtual ~AppendToFileLogger();

		virtual void OnAssert(
			const Properties &properties,
			const Result &assertionResult) const;

		virtual void AddMessage(const RichBool::detail::String &msg) const;
	};
}

#endif // #ifndef STREAM_LOGGER_H__QM















