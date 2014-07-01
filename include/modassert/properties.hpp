//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_PROPERTIES_H__QM
#define MOD_ASSERT_PROPERTIES_H__QM

#include "modassert/context.hpp"
#include "modassert/grouplst.hpp"

namespace ModAssert
{
	class CategoryBase;

	class Properties
	{
	public:
		Properties(const CategoryBase *categoryBase,
			const Context &context,
			const char* condition,
			const GroupList *groupList,
			const char *optionalDescr,
			bool canStopDisplayingThis=true):

			m_categoryBase(categoryBase),
			m_context(context),
			m_condition(condition),
			m_groupList(groupList),
			m_optionalDescr(optionalDescr),
			m_canStopDisplayingThis(canStopDisplayingThis)
		{}

		Properties(const CategoryBase *categoryBase,
			const Context &context,
			const char* condition,
			const GroupList &groupList,
			const char *optionalDescr,
			bool canStopDisplayingThis=true):

			m_categoryBase(categoryBase),
			m_context(context),
			m_condition(condition),
			m_groupList(&groupList),
			m_optionalDescr(optionalDescr),
			m_canStopDisplayingThis(canStopDisplayingThis)
		{}

		const CategoryBase* GetCategory() const { return m_categoryBase; }
		bool IsUnconditional() const { return m_condition==0; }
		const Context& GetContext() const { return m_context; }
		const char* GetCondition() const { return (m_condition==(const char*)1) ? 0 : m_condition; }
		const GroupList* GetGroupList() const { return m_groupList; }
		const char* GetOptional() const { return m_optionalDescr; }
		bool CanStopDisplayingThis() const { return m_canStopDisplayingThis; }

	private:
		const CategoryBase *m_categoryBase;
		const Context &m_context;
		const char* m_condition;
		const GroupList *m_groupList;
		const char *m_optionalDescr;
		bool m_canStopDisplayingThis;

		Properties& operator=(const Properties &)
		{
			return *this;
		}
	};
}

#endif // #ifndef MOD_ASSERT_PROPERTIES_H__QM
