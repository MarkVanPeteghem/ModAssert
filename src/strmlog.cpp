//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/strmlog.hpp"
#include "modassert/infostore.hpp"
#include "modassert/parmlist.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/categorybase.hpp"
#include "modassert/filters.hpp"
#include "modassert/logtype.hpp"
#include "richbool/analysis.hpp"

#ifdef RICHBOOL_USE_WX
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#else
#include <fstream>
#endif

namespace ModAssert
{
	static void StreamData(RichBool::detail::OutStream &stream,
		const InfoProviders::InfoUser &iu,
		const Properties &properties,
		const Result &assertionResult)
	{
		stream << properties.GetContext();

		if (!properties.IsUnconditional())
		{
			stream << ' ' << properties.GetCategory()->GetName() << ' ';
			if (properties.GetCondition())
				stream <<  properties.GetCondition() << " ";
			stream << (assertionResult.Succeeded() ? "succeeded" : "failed");
			if (!properties.GetCondition())
				stream << " (no text of condition available)";
		}
		else
			stream << " unconditional " << properties.GetCategory()->GetName() << " failure";
		RichBool::detail::Endl(stream);

		if (assertionResult.GetAnalysis())
			stream << "analysis: " << *assertionResult.GetAnalysis();
		else
			stream << "no analysis";
		RichBool::detail::Endl(stream);

		const ParameterList *parList = assertionResult.GetParameterList();
		if (parList && parList->GetFirst())
		{
			stream << "data:";
			RichBool::detail::Endl(stream);
			stream << *parList; // ends with newline!
		}

		if (properties.GetGroupList())
			for (size_t idx=0; idx<properties.GetGroupList()->GetSize(); ++idx)
			{
				stream << properties.GetGroupList()->GetName(idx);
				RichBool::detail::Endl(stream);
			}


		for (InfoProviderIterator it=beginInfoProviders(properties, assertionResult, iu); it!=endInfoProviders(); ++it)
		{
			stream << it->GetType() << ": " << it->GetInfo();
			RichBool::detail::Endl(stream);
		}

		RichBool::detail::Endl(stream);

#ifndef RICHBOOL_USE_WX
		stream.flush();
#endif
	}


	/////////////////////////////////////////////////////////////////
	// class StreamLogger

#ifdef RICHBOOL_USE_WX

	StreamLogger::StreamLogger(wxTextOutputStream *stream):
		m_ownStream(false), m_stream(stream)
	{}

	StreamLogger::StreamLogger(wxOutputStream *stream):
		m_ownStream(true), m_stream(new wxTextOutputStream(*stream))
	{}

	StreamLogger::~StreamLogger()
	{
		if (m_ownStream)
			delete m_stream;
	}

#else

	StreamLogger::StreamLogger(RichBool::detail::OutStream *stream):
		m_stream(stream)
	{}

	StreamLogger::~StreamLogger()
	{}

#endif

	void StreamLogger::OnAssert(const Properties &properties,
		const Result &assertionResult) const
	{
		StreamData(*m_stream, *this, properties, assertionResult);
	}

	void StreamLogger::AddMessage(const RichBool::detail::String &msg) const
	{
		*m_stream << msg;
		RichBool::detail::Endl(*m_stream);
	}

	/////////////////////////////////////////////////////////////////
	// class AppendToFileLogger

	AppendToFileLogger::AppendToFileLogger(const RichBool::detail::String &filename_):
		filename(filename_)
	{}

	AppendToFileLogger::~AppendToFileLogger()
	{}

	void AppendToFileLogger::OnAssert(
			const Properties &properties,
			const Result &assertionResult) const
	{
#ifdef RICHBOOL_USE_WX
		wxFile file(filename.c_str(), wxFile::write_append);
		wxFileOutputStream output(file);
		wxTextOutputStream fileStream( output );
#else
		std::ofstream fileStream(filename.c_str(), std::ios_base::out | std::ios_base::app);
#endif
		StreamData(fileStream, *this, properties, assertionResult);
	}

	void AppendToFileLogger::AddMessage(const RichBool::detail::String &msg) const
	{
#ifdef RICHBOOL_USE_WX
		wxFile file(filename.c_str(), wxFile::write_append);
		wxFileOutputStream output(file);
		wxTextOutputStream fileStream( output );
#else
		std::ofstream fileStream(filename.c_str(), std::ios_base::out | std::ios_base::app);
#endif
		fileStream << msg;
		RichBool::detail::Endl(fileStream);
	}
}
