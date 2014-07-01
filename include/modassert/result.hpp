//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef ASSERTION_RESULT_H__QM
#define ASSERTION_RESULT_H__QM

#include "richbool/analysis.hpp"
#include "modassert/parmlist.hpp"

namespace ModAssert
{
	class Result
	{
	public:
		Result(bool success,
			const RichBool::SharedAnalysis &analysis,
			const ParameterList *parList):

			m_success(success),
			m_analysis(analysis),
			m_parList(parList)

		{}

		bool Succeeded() const { return m_success; }
		const RichBool::SharedAnalysis GetAnalysis() const { return m_analysis; }
		const ParameterList* GetParameterList() const { return m_parList; }

		bool operator==(const Result &assertionResult) const
		{
			return (m_success==assertionResult.m_success)
				&& (*m_analysis==*assertionResult.m_analysis)
				&& (*m_parList==*assertionResult.m_parList);
		}

	private:
		bool m_success;
		const RichBool::SharedAnalysis m_analysis;
		const ParameterList *m_parList;

		Result& operator=(const Result&)
		{
			return *this;
		}
	};
}

#endif // #ifndef ASSERTION_RESULT_H__QM
