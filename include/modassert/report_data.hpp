//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_REPORT_DATA_H__QM
#define MOD_ASSERT_REPORT_DATA_H__QM

#include "modassert/categories.hpp"

namespace ModAssert
{
	struct ReportData
	{
		struct Data
		{
			Data(): display(true), log(true) {}
			bool display, log;
		};

		Data& GetData(Assertions ) { return assertionsData; }
		const Data& GetData(Assertions ) const { return assertionsData; }

		Data& GetData(Checks ) { return checksData; }
		const Data& GetData(Checks ) const { return checksData; }

		Data assertionsData, checksData;

		template <class Category_>
		void SetDisplay(bool b, Category_ cat)
		{
			GetData(cat).display = b;
		}

		template <class Category_>
		bool GetDisplay(Category_ cat) const
		{
			return GetData(cat).display;
		}

		template <class Category_>
		void SetLog(bool b, Category_ cat)
		{
			GetData(cat).log = b;
		}

		template <class Category_>
		bool GetLog(Category_ cat) const
		{
			return GetData(cat).log;
		}
	};
}

#endif // #ifndef MOD_ASSERT_REPORT_DATA_H__QM












