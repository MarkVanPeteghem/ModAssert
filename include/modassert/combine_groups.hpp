//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef TYPECOMB_H__QM
#define TYPECOMB_H__QM

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

namespace ModAssert
{
	namespace detail
	{
		template<class Groups1, class Groups2>
		struct GroupsCombination
		{
			GroupsCombination(const Groups1 &t1, const Groups2 &t2):
				type1(t1), type2(t2)
			{}

			Groups1 type1;
			Groups2 type2;

			enum { size = Groups1::size + Groups2::size };

			bool GetDisplay(size_t idx) const
			{
				if (idx<type1.GetSize())
					return type1.GetDisplay(idx);
				else
					return type2.GetDisplay(idx-type1.GetSize());
			}
			void SetDisplay(size_t idx, bool b) const
			{
				if (idx<type1.GetSize())
					type1.SetDisplay(idx, b);
				else
					type2.SetDisplay(idx-type1.GetSize(), b);
			}
			bool GetLog(size_t idx) const
			{
				if (idx<type1.GetSize())
					return type1.GetLog(idx);
				else
					return type2.GetLog(idx-type1.GetSize());
			}
			void SetLog(size_t idx, bool b) const
			{
				if (idx<type1.GetSize())
					type1.SetLog(idx, b);
				else
					type2.SetLog(idx-type1.GetSize(), b);
			}

			size_t GetSize() const { return type1.GetSize()+type2.GetSize(); }

			const RichBool::detail::String& GetName(size_t idx) const
			{
				if (idx<type1.GetSize())
					return type1.GetName(idx);
				else
					return type2.GetName(idx-type1.GetSize());
			}

			bool Has(const char *groupName) const
			{
				return type1.Has(groupName) || type2.Has(groupName);
			}

		private:
			GroupsCombination& operator=(const GroupsCombination&)
			{ return *this; }
		};

		template<class Groups1, class Groups2>
		struct GroupsOr: public GroupsCombination<Groups1, Groups2>
		{
			GroupsOr(const Groups1 &t1, const Groups2 &t2):
				GroupsCombination<Groups1, Groups2>(t1, t2)
			{}

			// 3 enums, necessary to be able to exclude assertions at compile time
			enum { level = 2 };
			enum { ifSuccess = Groups1::ifSuccess || Groups2::ifSuccess };
			enum { enabled = Groups1::enabled || Groups2::enabled };

			using GroupsCombination<Groups1, Groups2>::GetDisplay;
			bool GetDisplay(bool success) const
			{
				return this->type1.GetDisplay(success) ||
					this->type2.GetDisplay(success);
			}

			using GroupsCombination<Groups1, Groups2>::GetLog;
			bool GetLog(bool success) const
			{
				return this->type1.GetLog(success) ||
					this->type2.GetLog(success);
			}
		private:
			GroupsOr& operator=(const GroupsOr&)
			{ return *this; }
		};

		template<class Groups1, class Groups2>
		struct GroupsAnd: public GroupsCombination<Groups1, Groups2>
		{
			GroupsAnd(const Groups1 &t1, const Groups2 &t2):
				GroupsCombination<Groups1, Groups2>(t1, t2)
			{}

			// 3 enums, necessary to be able to exclude assertions at compile time
			enum { level = 2 };
			enum { ifSuccess = Groups1::ifSuccess && Groups2::ifSuccess };
			enum { enabled = Groups1::enabled && Groups2::enabled };

			using GroupsCombination<Groups1, Groups2>::GetDisplay;
			bool GetDisplay(bool success) const
			{
				return this->type1.GetDisplay(success) &&
					this->type2.GetDisplay(success);
			}

			using GroupsCombination<Groups1, Groups2>::GetLog;
			bool GetLog(bool success) const
			{
				return this->type1.GetLog(success) &&
					this->type2.GetLog(success);
			}

		private:
			GroupsAnd& operator=(const GroupsAnd&)
			{ return *this; }
		};

		template<class Groups1, class Groups2>
		struct GroupsAnd_FirstIfSuccess: public GroupsAnd<Groups1, Groups2>
		{
			GroupsAnd_FirstIfSuccess(const Groups1 &t1, const Groups2 &t2):
				GroupsAnd<Groups1, Groups2>(t1, t2)
			{}

			enum { ifSuccess = Groups1::ifSuccess };

			using GroupsAnd<Groups1, Groups2>::GetDisplay;
			bool GetDisplay(bool success) const
			{
				return this->type1.GetDisplay(success) &&
					this->type2.GetDisplay(false);
			}

			using GroupsAnd<Groups1, Groups2>::GetLog;
			bool GetLog(bool success) const
			{
				return this->type1.GetLog(success) &&
					this->type2.GetLog(false);
			}
		private:
			GroupsAnd_FirstIfSuccess& operator=(const GroupsAnd_FirstIfSuccess&)
			{ return *this; }
		};
	}
}

#endif // #ifndef TYPECOMB_H__QM
