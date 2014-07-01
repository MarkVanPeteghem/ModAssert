//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_REPORT_TYPE_H__QM
#define MOD_ASSERT_REPORT_TYPE_H__QM

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "modassert/group.hpp"
#include "modassert/grouplst.hpp"
#include "modassert/levels.hpp"

namespace ModAssert
{
	namespace detail
	{
		// base class for classes that decide whether and when assertions
		// should be reported
		class ReportBase
		{
		public:
			ReportBase(const RichBool::detail::String &name_):
				name(name_)
			{}

			enum { level = 2 };

			size_t GetSize() const { return 1; }

			const RichBool::detail::String& GetName(size_t ) const
			{
				return name;
			}

			bool Has(const char *groupName) const
			{
				return groupName==name;
			}

		private:
			RichBool::detail::String name;
		};
	}

	// template class to convert an object of the type Group<...> or
	// CombinationOfGroups<...> to the abstract type GroupList
	template<class TheType>
	class TemplateGroupList: public GroupList
	{
		typedef Level<detail::L_<2> > DefaultLevel;
	public:
		TemplateGroupList(const TheType &t): theType(t) {}

		TheType theType;

		virtual bool GetDisplay(bool ma_success, const CategoryBase &cat) const
		{ return theType.GetDisplay(ma_success) && DefaultLevel::GetDisplay(cat); }

		virtual bool GetDisplay(size_t idx, const CategoryBase &cat) const
		{ return (idx==theType.GetSize()) ?
			DefaultLevel::GetDisplay(cat) : theType.GetDisplay(idx); }

		virtual void SetDisplay(size_t idx, bool b, const CategoryBase &cat) const
		{
			if (idx==theType.GetSize())
				DefaultLevel::SetDisplay(b, cat);
			else
				theType.SetDisplay(idx, b);
		}


		virtual bool GetLog(bool ma_success, const CategoryBase &cat) const
		{ return theType.GetLog(ma_success) && DefaultLevel::GetLog(cat); }

		virtual bool GetLog(size_t idx, const CategoryBase &cat) const
		{ return (idx==theType.GetSize()) ?
			DefaultLevel::GetLog(cat) : theType.GetLog(idx); }

		virtual void SetLog(size_t idx, bool b, const CategoryBase &cat) const
		{
			if (idx==theType.GetSize())
				DefaultLevel::SetLog(b, cat);
			else
				theType.SetLog(idx, b);
		}


		virtual size_t GetSize() const
		// add one for the default level
		{ return theType.GetSize()+1; }

		virtual const RichBool::detail::String& GetName(size_t idx) const
		{ return (idx==theType.GetSize()) ?
			DefaultLevel::GetName(0) : theType.GetName(idx); }

		virtual bool HasLevel() const
		{ return false; }

		virtual int GetLevel() const
		{ return DefaultLevel::level; }

		virtual bool IfSuccess() const
		{ return TheType::ifSuccess; }

		virtual bool Has(const char *groupName) const
		{ return theType.Has(groupName); }

	private:
		// no assignment allowed, because of member that is a reference
		TemplateGroupList& operator=(const TemplateGroupList &)
		{}
	};

	// template class to convert an object of the type
	// GroupWithLevel<...> or Level<...> to the abstract type GroupList
	template<class TheType>
	class TemplateGroupListWithLevel: public GroupList
	{
	public:
		TemplateGroupListWithLevel(const TheType &t): theType(t) {}

		TheType theType;

		virtual bool GetDisplay(bool ma_success, const CategoryBase &cat) const
		{ return theType.GetDisplay(ma_success, cat); }

		virtual bool GetDisplay(size_t idx, const CategoryBase &cat) const
		{ return theType.GetDisplay(idx, cat); }

		virtual void SetDisplay(size_t idx, bool b, const CategoryBase &cat) const
		{ theType.SetDisplay(idx, b, cat); }


		virtual bool GetLog(bool ma_success, const CategoryBase &cat) const
		{ return theType.GetLog(ma_success, cat); }

		virtual bool GetLog(size_t idx, const CategoryBase &cat) const
		{ return theType.GetLog(idx, cat); }

		virtual void SetLog(size_t idx, bool b, const CategoryBase &cat) const
		{ theType.SetLog(idx, b, cat); }


		virtual size_t GetSize() const
		{ return theType.GetSize(); }

		virtual const RichBool::detail::String& GetName(size_t idx) const
		{ return theType.GetName(idx); }

		virtual bool HasLevel() const
		{ return TheType::hasLevel; }

		virtual int GetLevel() const
		{ return TheType::level; }

		virtual bool IfSuccess() const
		{ return TheType::ifSuccess; }

		virtual bool Has(const char *groupName) const
		{ return theType.Has(groupName); }

	private:
		// no assignment allowed, because of member that is a reference
		TemplateGroupListWithLevel& operator=(const TemplateGroupListWithLevel &)
		{}
	};

	template<class G>
	inline TemplateGroupList<GroupHolder<G> > MakeGroupList(Group<G> &group)
	{
		return TemplateGroupList<GroupHolder<G> >(GroupHolder<G>(group.type));
	}

	template<class G>
	inline TemplateGroupList<FinalCombinationHolder<G> > MakeGroupList(const FinalCombinationHolder<G> &group)
	{
		return TemplateGroupList<FinalCombinationHolder<G> >(group);
	}

	template<class L>
	inline TemplateGroupListWithLevel<Level<L> > MakeGroupList(Level<L> &g)
	{
		return TemplateGroupListWithLevel<Level<L> >(g);
	}

	template<class G, class L>
	inline TemplateGroupListWithLevel<GroupWithLevel<G, L> > MakeGroupList(const GroupWithLevel<G, L> &g)
	{
		return TemplateGroupListWithLevel<GroupWithLevel<G, L> >(g);
	}

	class ReportNone: public detail::ReportBase
	{
	public:
		ReportNone(const RichBool::detail::String &name_): detail::ReportBase(name_) { }

		enum { ifSuccess = false, enabled = false };
		enum { size = 1 };

		bool GetDisplay(bool ) const { return false; }
		bool GetDisplay(size_t ) const { return false; }
		void SetDisplay(bool ) { }
		void SetDisplay(size_t , bool ) { }

		bool GetLog(bool ) const { return false; }
		bool GetLog(size_t ) const { return false; }
		void SetLog(bool ) { }
		void SetLog(size_t , bool ) { }
	};

	class ReportFailure: public detail::ReportBase
	{
	public:
		ReportFailure(const RichBool::detail::String &name_):
			detail::ReportBase(name_), display(true), log(true)
		{ }

		enum { ifSuccess = false, enabled = true };
		enum { size = 1 };

		bool GetDisplay(bool ma_success) const { return !ma_success && display; }
		bool GetDisplay(size_t ) const { return display; }
		void SetDisplay(bool b) { display = b; }
		void SetDisplay(size_t , bool b) { display = b; }

		bool GetLog(bool ma_success) const { return !ma_success && log; }
		bool GetLog(size_t ) const { return log; }
		void SetLog(bool b) { log = b; }
		void SetLog(size_t , bool b) { log = b; }
	private:
		bool display, log;
	};

	class ReportAll: public detail::ReportBase
	{
	public:
		ReportAll(const RichBool::detail::String &name_):
			detail::ReportBase(name_+" (nok)"),
			display(2), log(2), name2(name_+" (ok)")
		{ }

		enum { ifSuccess = true, enabled = true };

		// two, because reporting success and failure are handled separately:
		enum { size = 2 };

		size_t GetSize() const { return 2; }

		bool GetDisplay(bool ma_success) const
		{
			return ma_success ? display==2 : display>=1;
		}
		bool GetDisplay(size_t n) const { return GetDisplay(n==1); }
		void SetDisplay(size_t n, bool b)
		{
			if (n==1)
			{
				if (!b && (display==2) )
					display = 1;
				else if (b)
					display = 2;
			}
			else
			{
				if (b && (display==0))
				{
					display = 1;
				}
				else if (!b)
				{
					display = 0;
				}
			}
		}

		bool GetLog(bool ma_success) const
		{
			return ma_success ? log==2 : log>=1;
		}
		bool GetLog(size_t n) const { return GetLog(n==1); }
		void SetLog(size_t n, bool b)
		{
			if (n==1)
			{
				if (!b && (log==2) )
					log = 1;
				else if (b)
					log = 2;
			}
			else
			{
				if (b && (log==0))
				{
					log = 1;
				}
				else if (!b)
				{
					log = 0;
				}
			}
		}
		const RichBool::detail::String& GetName(size_t idx) const
		{
			return idx==0 ? ReportBase::GetName(0) : name2;
		}

	private:
		int display, log;
		RichBool::detail::String name2;
	};


	// operator && and ||
	// note: GroupsAnd and GroupsOr have GroupHolder<...> or CombinationHolder<...>
	// as their template arguments, because these can be copy-constructed while
	// still holding pointers to the original Group<...> objects
	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsAnd<GroupHolder<Type1>, GroupHolder<Type2> > >
	operator&&(Group<Type1> &type1, Group<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsAnd<GroupHolder<Type1>, GroupHolder<Type2> > >
			(detail::GroupsAnd<GroupHolder<Type1>, GroupHolder<Type2> >(GroupHolder<Type1>(type1.type), GroupHolder<Type2>(type2.type)));
	}

	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsOr<GroupHolder<Type1>, GroupHolder<Type2> > >
	operator||(Group<Type1> &type1, Group<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsOr<GroupHolder<Type1>, GroupHolder<Type2> > >
			(detail::GroupsOr<GroupHolder<Type1>, GroupHolder<Type2> >(GroupHolder<Type1>(type1.type), GroupHolder<Type2>(type2.type)));
	}


	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsAnd<CombinationHolder<Type1>, GroupHolder<Type2> > >
	operator&&(const CombinationHolder<Type1> &type1, Group<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsAnd<CombinationHolder<Type1>, GroupHolder<Type2> > >
			(detail::GroupsAnd<CombinationHolder<Type1>, GroupHolder<Type2> >(type1, GroupHolder<Type2>(type2.type)));
	}

	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsOr<CombinationHolder<Type1>, GroupHolder<Type2> > >
	operator||(const CombinationHolder<Type1> &type1, Group<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsOr<CombinationHolder<Type1>, GroupHolder<Type2> > >
			(detail::GroupsOr<CombinationHolder<Type1>, GroupHolder<Type2> >(type1, GroupHolder<Type2>(type2.type)));
	}


	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsAnd<GroupHolder<Type1>, CombinationHolder<Type2> > >
	operator&&(Group<Type1> &type1, const CombinationHolder<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsAnd<GroupHolder<Type1>, CombinationHolder<Type2> > >
			(detail::GroupsAnd<GroupHolder<Type1>, CombinationHolder<Type2> >(GroupHolder<Type1>(type1.type), type2));
	}

	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsOr<GroupHolder<Type1>, CombinationHolder<Type2> > >
	operator||(Group<Type1> &type1, const CombinationHolder<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsOr<GroupHolder<Type1>, CombinationHolder<Type2> > >
			(detail::GroupsOr<GroupHolder<Type1>, CombinationHolder<Type2> >(GroupHolder<Type1>(type1.type), type2));
	}


	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsAnd<CombinationHolder<Type1>, CombinationHolder<Type2> > >
	operator&&(const CombinationHolder<Type1> &type1, const CombinationHolder<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsAnd<CombinationHolder<Type1>, CombinationHolder<Type2> > >
			(detail::GroupsAnd<CombinationHolder<Type1>, CombinationHolder<Type2> >(type1.type, type2.type));
	}

	template<class Type1, class Type2>
	CombinationHolder< detail::GroupsOr<CombinationHolder<Type1>, CombinationHolder<Type2> > >
	operator||(const CombinationHolder<Type1> &type1, const CombinationHolder<Type2> &type2)
	{
		return CombinationHolder< detail::GroupsOr<CombinationHolder<Type1>, CombinationHolder<Type2> > >
			(detail::GroupsOr<CombinationHolder<Type1>, CombinationHolder<Type2> >(type1.type, type2.type));
	}


	// operator% to add a level to a group
	template<class Type, class L>
	GroupWithLevel<GroupHolder<Type>, L> operator%(Group<Type> &type,
		const Level<L> &)
	{
		GroupWithLevel<GroupHolder<Type>, L> rv(GroupHolder<Type>(type.type));
		return rv;
	}

	template<class Type, class L>
	GroupWithLevel<FinalCombinationHolder<Type>, L> operator%(const FinalCombinationHolder<Type> &type,
		const Level<L> &)
	{
		GroupWithLevel<FinalCombinationHolder<Type>, L> rv(type.type);
		return rv;
	}
}

#endif // #ifndef MOD_ASSERT_REPORT_TYPE_H__QM
