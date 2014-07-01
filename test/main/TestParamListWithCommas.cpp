//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif


#include "ModAssertTest.h"
#include "CreateList.h"
#include "richbool/richbool.hpp"


static void GetMessages(const ModAssert::ParameterList &parList,
				 RichBool::detail::StringArray &messages,
				 RichBool::detail::StringArray &values)
{
	for (const ModAssert::ParameterList::Message *message=parList.GetFirst();
		message; message = message->GetNext())
	{
		messages.push_back(message->GetMessage());
		if (message->GetType()==ModAssert::ParameterList::eValue)
		{
			RichBool::detail::String str =
				((const ModAssert::ParameterList::Value*)message)->GetValue();

			// it is possible that a value is empty,
			// but in these tests we promise to have no empty values
			// so we can easily tell the difference between a message and a value
			META_ASSERT(!RichBool::detail::is_empty(str));
			RichBool::detail::AddString(values, str);
		}
		else
			RichBool::detail::AddString(values, "");
	}
}

#define MAKE_PARAMLIST(params) \
	ModAssert::ParameterList list; \
	ModAssert::MakeHoldReferencesAndString(ModAssert::MakeHoldReferences params , #params).AddToParameterList(list);

MA_TEST(OneExpression_Commas)
{
	MAKE_PARAMLIST((1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
}

MA_TEST(OneMessage_Commas)
{
	MAKE_PARAMLIST(("test"));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(OneMessageInTwoParts_Commas)
{
	MAKE_PARAMLIST(("te" "st"));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(OneMessageAndOneExpression_Commas)
{
	MAKE_PARAMLIST(("test", 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(OneMessageInTwoPartsAndOneExpression_Commas)
{
	MAKE_PARAMLIST(("te" "st", 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(OneExpressionAndOneMessage_Commas)
{
	MAKE_PARAMLIST((1, "test"));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "test"));
	META_ASSERT(rbEQUAL(values[1]  , ""));
}

MA_TEST(OneExpressionAndOneMessageInTwoParts_Commas)
{
	MAKE_PARAMLIST((1, "te" "st"));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "test"));
	META_ASSERT(rbEQUAL(values[1]  , ""));
}

MA_TEST(TwoExpressions_Commas)
{
	MAKE_PARAMLIST((1 , 2));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(TwoExpressionsWithSpaceAfterFirst_Commas)
{
	MAKE_PARAMLIST((1 , 2));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(TwoExpressionsWithSpaceBeforeSecond_Commas)
{
	MAKE_PARAMLIST((1 , 2));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(ThreeExpressionsWithSpace_Commas)
{
	MAKE_PARAMLIST((1 , 2 , 3));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 3u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
}

MA_TEST(FourExpressions_Commas)
{
	MAKE_PARAMLIST((1, 2, 3, 4));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 4u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
}

MA_TEST(FiveExpressions_Commas)
{
	MAKE_PARAMLIST((1, 2, 3, 4, 5));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 5u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
	META_ASSERT(rbEQUAL(messages[4], "5"));
	META_ASSERT(rbEQUAL(values[4]  , "5"));
}

MA_TEST(SixExpressions_Commas)
{
	MAKE_PARAMLIST((1, 2, 3, 4, 5, 6));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 6u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
	META_ASSERT(rbEQUAL(messages[4], "5"));
	META_ASSERT(rbEQUAL(values[4]  , "5"));
	META_ASSERT(rbEQUAL(messages[5], "6"));
	META_ASSERT(rbEQUAL(values[5]  , "6"));
}

MA_TEST(SevenExpressions_Commas)
{
	MAKE_PARAMLIST((1, 2, 3, 4, 5, 6, 7));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 7u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
	META_ASSERT(rbEQUAL(messages[4], "5"));
	META_ASSERT(rbEQUAL(values[4]  , "5"));
	META_ASSERT(rbEQUAL(messages[5], "6"));
	META_ASSERT(rbEQUAL(values[5]  , "6"));
	META_ASSERT(rbEQUAL(messages[6], "7"));
	META_ASSERT(rbEQUAL(values[6]  , "7"));
}

MA_TEST(EightExpressions_Commas)
{
	MAKE_PARAMLIST((1, 2, 3, 4, 5, 6, 7, 8));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 8u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
	META_ASSERT(rbEQUAL(messages[4], "5"));
	META_ASSERT(rbEQUAL(values[4]  , "5"));
	META_ASSERT(rbEQUAL(messages[5], "6"));
	META_ASSERT(rbEQUAL(values[5]  , "6"));
	META_ASSERT(rbEQUAL(messages[6], "7"));
	META_ASSERT(rbEQUAL(values[6]  , "7"));
	META_ASSERT(rbEQUAL(messages[7], "8"));
	META_ASSERT(rbEQUAL(values[7]  , "8"));
}

MA_TEST(ExpressionWithCommaInString_Commas)
{
	MAKE_PARAMLIST(("1,2"));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "1,2"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(ExpressionWithCommaInExpression_Commas)
{
	MAKE_PARAMLIST(((1,2)));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "(1,2)"));
	META_ASSERT(rbEQUAL(values[0]  , "2"));
}

MA_TEST(ExpressionWithParensInString_Commas)
{
	MAKE_PARAMLIST(("((" , 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "(("));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithParenInChar_Commas)
{
	MAKE_PARAMLIST(('(' , 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "'('"));
	META_ASSERT(rbEQUAL(values[0]  , "("));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithCommaInBrackets_Commas)
{
	int a[] = { 1, 2, 3, 4 };
	MAKE_PARAMLIST((a[1,1]));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "a[1,1]"));
	META_ASSERT(rbEQUAL(values[0]  , "2"));
}

MA_TEST(ExpressionWithBracketsInString_Commas)
{
	MAKE_PARAMLIST(("[[" , 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "[["));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithBracketInChar_Commas)
{
	MAKE_PARAMLIST(('[' , 1));

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "'['"));
	META_ASSERT(rbEQUAL(values[0]  , "["));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(DoubleHoldReferencesAndString_Two)
{
	ModAssert::ParameterList list;

	list.AddParameters(
		ModAssert::DoubleHoldReferencesAndString
			<ModAssert::Hold1Reference<int>, ModAssert::Hold1Reference<int> >
		(ModAssert::Hold1Reference<int>(1), "(1)", ModAssert::Hold1Reference<int>(3), "(3)")
	);

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "3"));
	META_ASSERT(rbEQUAL(values[1]  , "3"));
}

MA_TEST(DoubleHoldReferencesAndString_Four)
{
	ModAssert::ParameterList list;

	list.AddParameters(
		ModAssert::DoubleHoldReferencesAndString
			<ModAssert::Hold2References<int,int>, ModAssert::Hold2References<int,int> >
		(ModAssert::Hold2References<int,int>(1,2), "(1,2)", ModAssert::Hold2References<int,int>(3,4), "(3,4)")
	);

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 4u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
	META_ASSERT(rbEQUAL(messages[2], "3"));
	META_ASSERT(rbEQUAL(values[2]  , "3"));
	META_ASSERT(rbEQUAL(messages[3], "4"));
	META_ASSERT(rbEQUAL(values[3]  , "4"));
}

