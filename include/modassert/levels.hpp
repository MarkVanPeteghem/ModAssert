//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_LEVELS_H__QM
#define MOD_ASSERT_LEVELS_H__QM

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/portability.hpp"
#include "modassert/report_data.hpp"
#include "modassert/categorybase.hpp"

namespace ModAssert
{
	const RichBool::detail::String& GetLevelName(int level);

	namespace detail
	{
		template<int level_>
		struct L_
		{
			enum { level = level_ };

			static ReportData reportData;

			static const RichBool::detail::String& GetName() { return GetLevelName(level); }
		};

		template<int level_> ReportData L_<level_>::reportData;
	}

	template<class L>
	struct Level
	{
		enum { enabled = true, hasLevel = true, ifSuccess = false };
		enum { level = L::level };

		// these 4 functions are meant to be called directly:
		static bool GetDisplay(const CategoryBase &cat)
		{ return cat.GetDisplay(L::reportData); }
		static void SetDisplay(bool b, const CategoryBase &cat)
		{ cat.SetDisplay(b, L::reportData); }

		static bool GetLog(const CategoryBase &cat)
		{ return cat.GetLog(L::reportData); }
		static void SetLog(bool b, const CategoryBase &cat)
		{ cat.SetLog(b, L::reportData); }

		// these 4 functions are meant to be called from TemplateGroupList:
		static bool GetDisplay(size_t , const CategoryBase &cat)
		{ return cat.GetDisplay(L::reportData); }
		static void SetDisplay(size_t , bool b, const CategoryBase &cat)
		{ cat.SetDisplay(b, L::reportData); }
		static bool GetLog(size_t , const CategoryBase &cat)
		{ return cat.GetLog(L::reportData); }
		static void SetLog(size_t , bool b, const CategoryBase &cat)
		{ cat.SetLog(b, L::reportData); }

		// TemplateGroupList will add one for the level, whether it is explicitly
		// given or not
		static size_t GetSize() { return 1; }

		static const RichBool::detail::String& GetName(size_t ) { return L::GetName(); }

		bool Has(const char *) const { return false; }
	};


	// some predefined levels
	extern Level<detail::L_<0> > Info;
	extern Level<detail::L_<1> > Warning;
	extern Level<detail::L_<2> > Error;
	extern Level<detail::L_<3> > Fatal;
}

#endif // #ifndef MOD_ASSERT_LEVELS_H__QM
