//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef HOLD_REFERENCES_H__QM
#define HOLD_REFERENCES_H__QM

namespace ModAssert
{
	template <typename T1>
	struct Hold1Reference
	{
		Hold1Reference(const T1 &t1_): t1(t1_) {}
		const T1 &t1;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1;
		}
	private:
		Hold1Reference& operator=(const Hold1Reference &)
		{
			return *this;
		}
	};

	template <typename T1>
	Hold1Reference<T1> MakeHoldReferences(const T1 &t1)
	{
		return Hold1Reference<T1>(t1);
	}

	template <typename T1, typename T2>
	struct Hold2References
	{
		Hold2References(const T1 &t1_, const T2 &t2_): t1(t1_), t2(t2_) {}
		const T1 &t1;
		const T2 &t2;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2;
		}
	private:
		Hold2References& operator=(const Hold2References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2>
	Hold2References<T1, T2> MakeHoldReferences(const T1 &t1, const T2 &t2)
	{
		return Hold2References<T1, T2>(t1, t2);
	}

	template <typename T1, typename T2, typename T3>
	struct Hold3References
	{
		Hold3References(const T1 &t1_, const T2 &t2_, const T3 &t3_):
			t1(t1_), t2(t2_), t3(t3_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3;
		}
	private:
		Hold3References& operator=(const Hold3References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3>
	Hold3References<T1, T2, T3> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3)
	{
		return Hold3References<T1, T2, T3>(t1, t2, t3);
	}

	template <typename T1, typename T2, typename T3, typename T4>
	struct Hold4References
	{
		Hold4References(const T1 &t1_, const T2 &t2_, const T3 &t3_,
			const T4 &t4_):
			t1(t1_), t2(t2_), t3(t3_), t4(t4_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;
		const T4 &t4;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3 << t4;
		}
	private:
		Hold4References& operator=(const Hold4References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3, typename T4>
	Hold4References<T1, T2, T3, T4> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3, const T4 &t4)
	{
		return Hold4References<T1, T2, T3, T4>(t1, t2, t3, t4);
	}

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5>
	struct Hold5References
	{
		Hold5References(const T1 &t1_, const T2 &t2_, const T3 &t3_,
			const T4 &t4_, const T5 &t5_):
			t1(t1_), t2(t2_), t3(t3_), t4(t4_), t5(t5_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;
		const T4 &t4;
		const T5 &t5;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3 << t4 << t5;
		}
	private:
		Hold5References& operator=(const Hold5References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5>
	Hold5References<T1, T2, T3, T4, T5> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5)
	{
		return Hold5References<T1, T2, T3, T4, T5>(t1, t2, t3, t4, t5);
	}

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6>
	struct Hold6References
	{
		Hold6References(const T1 &t1_, const T2 &t2_, const T3 &t3_,
			const T4 &t4_, const T5 &t5_, const T6 &t6_):
			t1(t1_), t2(t2_), t3(t3_), t4(t4_), t5(t5_), t6(t6_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;
		const T4 &t4;
		const T5 &t5;
		const T6 &t6;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3 << t4 << t5 << t6;
		}
	private:
		Hold6References& operator=(const Hold6References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6>
	Hold6References<T1, T2, T3, T4, T5, T6> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5,
		const T6 &t6)
	{
		return Hold6References<T1, T2, T3, T4, T5, T6>(t1, t2, t3, t4, t5, t6);
	}

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7>
	struct Hold7References
	{
		Hold7References(const T1 &t1_, const T2 &t2_, const T3 &t3_,
			const T4 &t4_, const T5 &t5_, const T6 &t6_,
			const T7 &t7_):
			t1(t1_), t2(t2_), t3(t3_), t4(t4_), t5(t5_), t6(t6_), t7(t7_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;
		const T4 &t4;
		const T5 &t5;
		const T6 &t6;
		const T7 &t7;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3 << t4 << t5 << t6 << t7;
		}
	private:
		Hold7References& operator=(const Hold7References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7>
	Hold7References<T1, T2, T3, T4, T5, T6, T7> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5,
		const T6 &t6, const T7 &t7)
	{
		return Hold7References<T1, T2, T3, T4, T5, T6, T7>
			(t1, t2, t3, t4, t5, t6, t7);
	}

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8>
	struct Hold8References
	{
		Hold8References(const T1 &t1_, const T2 &t2_, const T3 &t3_,
			const T4 &t4_, const T5 &t5_, const T6 &t6_,
			const T7 &t7_, const T8 &t8_):
			t1(t1_), t2(t2_), t3(t3_), t4(t4_), t5(t5_), t6(t6_), t7(t7_), t8(t8_) {}
		const T1 &t1;
		const T2 &t2;
		const T3 &t3;
		const T4 &t4;
		const T5 &t5;
		const T6 &t6;
		const T7 &t7;
		const T8 &t8;

		void AddToParameterList(ParameterList &parList) const
		{
			parList << t1 << t2 << t3 << t4 << t5 << t6 << t7 << t8;
		}
	private:
		Hold8References& operator=(const Hold8References &)
		{
			return *this;
		}
	};

	template <typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8>
	Hold8References<T1, T2, T3, T4, T5, T6, T7, T8> MakeHoldReferences(const T1 &t1,
		const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5,
		const T6 &t6, const T7 &t7, const T8 &t8)
	{
		return Hold8References<T1, T2, T3, T4, T5, T6, T7, T8>
			(t1, t2, t3, t4, t5, t6, t7, t8);
	}

	template <class HR1, class HR2>
	struct HoldReferencesCombined
	{
		HoldReferencesCombined(const HR1 &hr1_, const HR2 &hr2_):
			hr1(hr1_), hr2(hr2_) {}

		const HR1 &hr1;
		const HR2 &hr2;

		void AddToParameterList(ParameterList &parList) const
		{
			hr1.AddToParameterList(parList);
			hr2.AddToParameterList(parList);
		}
	private:
		HoldReferencesCombined& operator=(const HoldReferencesCombined &)
		{
			return *this;
		}
	};

	template <class HR>
	struct HoldReferencesAndString
	{
		HoldReferencesAndString(const HR &hr_, const char *expr_):
			hr(hr_), expr(expr_)
		{}

		void AddToParameterList(ParameterList &parList) const
		{
			parList.AddCommaSeparatedList(expr);
			hr.AddToParameterList(parList);
		}

		const HR &hr;
		const char *expr;
	private:
		HoldReferencesAndString& operator=(const HoldReferencesAndString &)
		{
			return *this;
		}
	};

	template <class HR>
	HoldReferencesAndString<HR> MakeHoldReferencesAndString(const HR &hr,
		const char *exprs)
	{
		return HoldReferencesAndString<HR>(hr, exprs);
	}

	template <class HR1, class HR2>
	struct DoubleHoldReferencesAndString
	{
		DoubleHoldReferencesAndString(const HR1 &hr1_, const char *expr1_,
			const HR2 &hr2_, const char *expr2_):
			hr1(hr1_), expr1(expr1_), hr2(hr2_), expr2(expr2_)
		{}

		void AddToParameterList(ParameterList &parList) const
		{
			parList.AddCommaSeparatedList(expr1);
			parList.AddCommaSeparatedList(expr2);
			hr1.AddToParameterList(parList);
			hr2.AddToParameterList(parList);
		}

		const HR1 &hr1;
		const HR2 &hr2;
		const char *expr1, *expr2;
	private:
		DoubleHoldReferencesAndString& operator=(const DoubleHoldReferencesAndString &)
		{
			return *this;
		}
	};

	template <class HR1, class HR2>
	DoubleHoldReferencesAndString<HR1, HR2> MakeDoubleHoldReferencesAndString(
		const HR1 &hr1, const char *expr1,
		const HR2 &hr2, const char *expr2)
	{
		return DoubleHoldReferencesAndString<HR1, HR2>(hr1, expr1,
				hr2, expr2);
	}
}

#endif // #ifndef HOLD_REFERENCES_H__QM
