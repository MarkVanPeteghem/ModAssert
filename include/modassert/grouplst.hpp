//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef GROUPLIST_H__QM
#define GROUPLIST_H__QM

#include "richbool/portability.hpp"

namespace ModAssert
{
	class CategoryBase;

	// abstract base class to pass assertion type information
	// to Responder and Logger derived objects
	class GroupList
	{
	public:
		virtual ~GroupList() {}

		// note: the setters are const, because this object contains
		// a combination of GroupHolder objects, that don't own their
		// Group objects, they only have a pointer to them,
		// and we can only pass the combination of the GroupHolder objects
		// as a const reference because it is a temporary object

		virtual bool GetDisplay(bool success, const CategoryBase&) const = 0;
		virtual bool GetLog(bool success, const CategoryBase&) const = 0;

		virtual bool GetDisplay(size_t idx, const CategoryBase&) const = 0;
		virtual void SetDisplay(size_t idx, bool b, const CategoryBase&) const = 0;
		virtual bool GetLog(size_t idx, const CategoryBase&) const = 0;
		virtual void SetLog(size_t idx, bool b, const CategoryBase&) const = 0;

		virtual size_t GetSize() const = 0;

		virtual const RichBool::detail::String& GetName(size_t idx) const = 0;

		virtual bool HasLevel() const = 0;
		virtual int GetLevel() const = 0;

		virtual bool IfSuccess() const = 0;

		virtual bool Has(const char *groupName) const = 0;
	};
}

#endif // #ifndef GROUPLIST_H__QM
