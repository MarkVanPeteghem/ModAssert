//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_CATEGORY_H__QM
#define MOD_ASSERT_CATEGORY_H__QM

#include "modassert/categorybase.hpp"
#include "modassert/report_data.hpp"

namespace ModAssert
{
	template<class C>
	class Category: public CategoryBase
	{
	public:
		virtual bool IsAssertion() const
		{
			return C::IsAssertion;
		}

		virtual bool IsCheck() const
		{
			return C::IsCheck;
		}

		virtual const char* GetName() const
		{
			return C::name;
		}

		virtual bool GetDisplay(const ReportData &reportData) const
		{
			return reportData.GetDisplay(C());
		}

		virtual void SetDisplay(bool b, ReportData &reportData) const
		{
			reportData.SetDisplay(b, C());
		}

		virtual bool GetLog(const ReportData &reportData) const
		{
			return reportData.GetLog(C());
		}

		virtual void SetLog(bool b, ReportData &reportData) const
		{
			reportData.SetLog(b, C());
		}
	};
}

#endif // #ifndef MOD_ASSERT_CATEGORY_H__QM
