//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_CATEGORY_BASE_H__QM
#define MOD_ASSERT_CATEGORY_BASE_H__QM

namespace ModAssert
{
	struct ReportData;

	class CategoryBase
	{
	public:
		virtual ~CategoryBase() {}

		virtual bool IsAssertion() const = 0;
		virtual bool IsCheck() const = 0;
		virtual const char* GetName() const = 0;

		virtual bool GetDisplay(const ReportData &reportData) const = 0;
		virtual void SetDisplay(bool b, ReportData &reportData) const = 0;

		virtual bool GetLog(const ReportData &reportData) const = 0;
		virtual void SetLog(bool b, ReportData &reportData) const = 0;
	};
}

#endif // #ifndef MOD_ASSERT_CATEGORY_BASE_H__QM












