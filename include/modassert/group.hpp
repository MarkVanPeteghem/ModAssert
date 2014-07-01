//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_GROUP_H__QM
#define MOD_ASSERT_GROUP_H__QM

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/portability.hpp"
#include "modassert/combine_groups.hpp"
#include "modassert/categorybase.hpp"
#include "modassert/levels.hpp"

namespace ModAssert
{
	template<class G>
	class GroupHolder
	{
		G *g;
	public:
		GroupHolder(G &g_): g(&g_) {}

		enum { ifSuccess = G::ifSuccess, enabled = G::enabled };
		enum { hasLevel = false };
		enum { level = 2 };
		enum { size = G::size };

		bool GetDisplay(size_t idx) const
		{ return g->GetDisplay(idx); }
		bool GetLog(size_t idx) const
		{ return g->GetLog(idx); }

		// these are const, because GroupHolder is not the owner of g.
		void SetDisplay(size_t idx, bool b) const
		{
			g->SetDisplay(idx, b);
		}
		void SetLog(size_t idx, bool b) const
		{
			g->SetLog(idx, b);
		}

		void SetDisplay(bool b) const { g->SetDisplay(b); }
		bool GetDisplay(bool ma_success) const { return g->GetDisplay(ma_success); }
		void SetLog(bool b) const { g->SetLog(b); }
		bool GetLog(bool ma_success) const { return g->GetLog(ma_success); }

		size_t GetSize() const { return size; }
		const RichBool::detail::String& GetName(size_t idx) const
		{ return idx==GetSize() ? GetLevelName(2) : g->GetName(idx); }

		bool Has(const char *groupName) const
		{
			return g->Has(groupName);
		}
	};

	template<class GC>
	struct FinalCombinationHolder
	{
		FinalCombinationHolder(const GC &t): type(t) {}

		GC type;

		// 4 enums, necessary to be able to exclude assertions at compile time
		enum { size = GC::size };
		enum { level = 2 };
		enum { ifSuccess = GC::ifSuccess };
		enum { enabled = GC::enabled };
		enum { hasLevel = false };

		bool GetDisplay(size_t idx) const
		{
			return type.GetDisplay(idx);
		}
		bool GetLog(size_t idx) const
		{
			return type.GetLog(idx);
		}

		// these are const, because type is a combination of
		// GroupHolder objects that are not the owners of g.
		void SetDisplay(size_t idx, bool b) const
		{
			type.SetDisplay(idx, b);
		}
		void SetLog(size_t idx, bool b) const
		{
			type.SetLog(idx, b);
		}

		bool GetDisplay(bool success) const
		{
			return type.GetDisplay(success);
		}

		bool GetLog(bool success) const
		{
			return type.GetLog(success);
		}

		size_t GetSize() const { return type.GetSize(); }

		const RichBool::detail::String& GetName(size_t idx) const
		{
			return idx==GetSize() ? GetLevelName(2) : type.GetName(idx);
		}

		bool Has(const char *groupName) const
		{
			return type.Has(groupName);
		}
	};

	template<class T>
	class Group
	{
	public:
		typedef T Type;

		Group() {}

		explicit Group(const Type &t): type(t) {}
		explicit Group(const char *name): type(name) {}

		template<typename Arg1, typename Arg2>
		Group(const Arg1 &arg1, const Arg2 &arg2): type(arg1, arg2) {}

		Type type;

		enum { ifSuccess = T::ifSuccess };
		enum { enabled = T::enabled };
		enum { hasLevel = false };
		enum { level = 2 };
		enum { size = T::size };

		bool GetDisplay(bool ma_success) const
		{ return type.GetDisplay(ma_success); }
		bool GetDisplay(size_t idx) const
		{ return type.GetDisplay(idx); }
		void SetDisplay(size_t idx, bool b)
		{
			type.SetDisplay(idx, b);
		}

		bool GetLog(bool ma_success) const
		{ return type.GetLog(ma_success); }
		bool GetLog(size_t idx) const
		{ return type.GetLog(idx); }
		void SetLog(size_t idx, bool b)
		{
			type.SetLog(idx, b);
		}

		void SetDisplay(bool b) { type.SetDisplay(b); }
		void SetLog(bool b) { type.SetLog(b); }

		size_t GetSize() const { return size; }
		const RichBool::detail::String& GetName(size_t idx) const
		{ return type.GetName(idx); }

		template<class OtherType>
		FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, GroupHolder<OtherType> > >
		operator()(Group<OtherType> &other)
		{
			return FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, GroupHolder<OtherType> > >
				(detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, GroupHolder<OtherType> >
					(GroupHolder<T>(type), GroupHolder<OtherType>(other.type)));
		}
		template<class OtherType>
		FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, FinalCombinationHolder<OtherType> > >
		operator()(const FinalCombinationHolder<OtherType> &other)
		{
			return FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, FinalCombinationHolder<OtherType> > >
				(detail::GroupsAnd_FirstIfSuccess<GroupHolder<T>, FinalCombinationHolder<OtherType> >
					(GroupHolder<T>(type), FinalCombinationHolder<OtherType>(other.type)));
		}

		bool Has(const char *groupName) const
		{
			return type.Has(groupName);
		}
	};

	template<class GC>
	struct CombinationHolder: public FinalCombinationHolder<GC>
	{
		CombinationHolder(const GC &t): FinalCombinationHolder<GC>(t) {}

		template<class OtherType>
		FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GC, GroupHolder<OtherType> > >
		operator()(Group<OtherType> &other) const
		{
			return FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GC, GroupHolder<OtherType> > >
				(detail::GroupsAnd_FirstIfSuccess<GC, GroupHolder<OtherType> >(FinalCombinationHolder<GC>::type, GroupHolder<OtherType>(other.type)));
		}
		template<class OtherType>
		FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GC, CombinationHolder<OtherType> > >
		operator()(const CombinationHolder<OtherType> &other) const
		{
			return FinalCombinationHolder<detail::GroupsAnd_FirstIfSuccess<GC, CombinationHolder<OtherType> > >
				(detail::GroupsAnd_FirstIfSuccess<GC, CombinationHolder<OtherType> >
					(FinalCombinationHolder<GC>::type, other.type));
		}

	private:
		CombinationHolder& operator=(const CombinationHolder &)
		{}
	};

	template<class T, class L>
	class GroupWithLevel
	{
	public:
		typedef T Type;

		GroupWithLevel(const Type &t): type(t) {}

		Type type;

		enum { enabled = T::enabled, ifSuccess = T::ifSuccess };
		enum { hasLevel = true };
		enum { level = L::level };
		enum { size = T::size };

		bool GetDisplay(bool success, const CategoryBase &cat) const
		{ return type.GetDisplay(success) && (success || Level<L>::GetDisplay(cat)); }
		bool GetDisplay(size_t idx, const CategoryBase &cat) const
		{ return (idx==size) ? Level<L>::GetDisplay(cat) : type.GetDisplay(idx); }

		bool GetLog(bool success, const CategoryBase &cat) const
		{ return type.GetLog(success) && (success || Level<L>::GetLog(cat)); }
		bool GetLog(size_t idx, const CategoryBase &cat) const
		{ return (idx==size) ? Level<L>::GetLog(cat) : type.GetLog(idx); }

		// these are const, because type is a combination of
		// GroupHolder objects that are not the owners of g
		// and we call only static methods of Level<L>.
		void SetDisplay(size_t idx, bool b, const CategoryBase &cat) const
		{
			if (idx==size)
				Level<L>::SetDisplay(b, cat);
			else
				type.SetDisplay(idx, b);
		}
		void SetLog(size_t idx, bool b, const CategoryBase &cat) const
		{
			if (idx==size)
				Level<L>::SetLog(b, cat);
			else
				type.SetLog(idx, b);
		}

		size_t GetSize() const { return size+1; }
		const RichBool::detail::String& GetName(size_t idx) const
		{ return (idx==size) ? Level<L>::GetName(size_t(0)) : type.GetName(idx); }

		bool Has(const char *groupName) const
		{
			return type.Has(groupName);
		}

	private:
		GroupWithLevel& operator=(const GroupWithLevel&)
		{ return *this; }
	};
}

#endif // #ifndef MOD_ASSERT_GROUP_H__QM
