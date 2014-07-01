//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef GET_STREAM_STRING_H__QM
#define GET_STREAM_STRING_H__QM

#include "modassert/strmlog.hpp"

inline RichBool::detail::String NewLine()
{
	static RichBool::detail::String newLine;
	if (newLine.empty())
	{
#ifdef RICHBOOL_USE_WX
		wxMemoryOutputStream memStream;
		wxTextOutputStream stream(memStream);
		endl(stream);
		wxFileOffset len = memStream.TellO();
		memStream.CopyTo(newLine.GetWriteBuf(len), len);
		newLine.UngetWriteBuf();
#else
		std::ostringstream strstr;
		RichBool::detail::Endl(strstr);
		newLine = strstr.str();
#endif
	}
	return newLine;
}

#ifdef RICHBOOL_USE_WX
	typedef wxMemoryOutputStream MemOutStream;
	class MemInStream: public wxMemoryInputStream
	{
	public:
		MemInStream(const wxString &str): wxMemoryInputStream(str.c_str(), str.size())
		{}
	};

	inline wxString GetStreamString(wxMemoryOutputStream &memStream)
	{
		wxString str;
		const wxFileOffset len = memStream.TellO();
		if (len!=0)
		{
			memStream.CopyTo(str.GetWriteBuf(len), len);
			str.UngetWriteBuf();
		}
		return str;
	}
#else
	#include <iostream>
	typedef std::ostringstream MemOutStream;
	typedef std::istringstream MemInStream;
	inline std::string GetStreamString(std::ostringstream &memStream)
	{
		return memStream.str();
	}

#endif

#endif // #ifndef GET_STREAM_STRING_H__QM
