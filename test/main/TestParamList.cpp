//  Copyright (C) 2004-2009 Q-Mentum.
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
				((ModAssert::ParameterList::Value*)message)->GetValue();

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

MA_TEST(OneExpression)
{
	ModAssert::ParameterList list("1");
	list << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);
	
	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
}

MA_TEST(OneMessage)
{
	ModAssert::ParameterList list("\"test\"");
	list << "test";

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(OneMessageInTwoParts)
{
	ModAssert::ParameterList list("\"te\" \"st\"");
	list << "te" "st";

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(OneMessageAndOneExpression)
{
	ModAssert::ParameterList list("\"test\" << 1");
	list << "test" << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(OneMessageInTwoPartsAndOneExpression)
{
	ModAssert::ParameterList list("\"te\" \"st\" << 1");
	list << "te" "st" << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "test"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(OneExpressionAndOneMessage)
{
	ModAssert::ParameterList list("1 << \"test\"");
	list << 1 << "test";

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "test"));
	META_ASSERT(rbEQUAL(values[1]  , ""));
}

MA_TEST(OneExpressionAndOneMessageInTwoParts)
{
	ModAssert::ParameterList list("1 << \"te\" \"st\"");
	list << 1 << "te" "st";

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "test"));
	META_ASSERT(rbEQUAL(values[1]  , ""));
}

MA_TEST(TwoExpressions)
{
	ModAssert::ParameterList list("1<<2");
	list << 1 << 2;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(TwoExpressionsWithSpaceAfterFirst)
{
	ModAssert::ParameterList list("1 <<2");
	list << 1 << 2;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(TwoExpressionsWithSpaceBeforeSecond)
{
	ModAssert::ParameterList list("1<< 2");
	list << 1 << 2;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "1"));
	META_ASSERT(rbEQUAL(values[0]  , "1"));
	META_ASSERT(rbEQUAL(messages[1], "2"));
	META_ASSERT(rbEQUAL(values[1]  , "2"));
}

MA_TEST(ThreeExpressionsWithSpace)
{
	ModAssert::ParameterList list("1 << 2 << 3");
	list << 1 << 2 << 3;

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

MA_TEST(ExpressionWithStreamInString)
{
	ModAssert::ParameterList list("\"1<<2\"");
	list << "1<<2";

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "1<<2"));
	META_ASSERT(rbEQUAL(values[0]  , ""));
}

MA_TEST(ExpressionWithStreamInExpression)
{
	ModAssert::ParameterList list("(1<<2)");
	list << (1<<2);

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "(1<<2)"));
	META_ASSERT(rbEQUAL(values[0]  , "4"));
}

MA_TEST(ExpressionWithParensInString)
{
	ModAssert::ParameterList list("\"((\"<<1");
	list << "((" << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "(("));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithParenInChar)
{
	ModAssert::ParameterList list("'('<<1");
	list << '(' << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "'('"));
	META_ASSERT(rbEQUAL(values[0]  , "("));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithStreamInBrackets)
{
	int a[] = { 1, 2, 3, 4 };
	ModAssert::ParameterList list("a[1<<1]");
	list << a[1<<1];

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 1u));

	META_ASSERT(rbEQUAL(messages[0], "a[1<<1]"));
	META_ASSERT(rbEQUAL(values[0]  , "3"));
}

MA_TEST(ExpressionWithBracketsInString)
{
	ModAssert::ParameterList list("\"[[\"<<1");
	list << "[[" << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "[["));
	META_ASSERT(rbEQUAL(values[0]  , ""));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(ExpressionWithBracketInChar)
{
	ModAssert::ParameterList list("'['<<1");
	list << '[' << 1;

	RichBool::detail::StringArray messages, values;
	GetMessages(list, messages, values);

	META_ASSERT(rbEQUAL(messages.size(), 2u));

	META_ASSERT(rbEQUAL(messages[0], "'['"));
	META_ASSERT(rbEQUAL(values[0]  , "["));
	META_ASSERT(rbEQUAL(messages[1], "1"));
	META_ASSERT(rbEQUAL(values[1]  , "1"));
}

MA_TEST(StreamOut_WithMessage)
{
	ModAssert::ParameterList list("1");
	list << 1;

	RichBool::detail::String str = RichBool::ToString(list);
	META_ASSERT(rbSTRING_CS(str, ==, "  1: 1\r\n"));
}

MA_TEST(StreamOut_WithExpression)
{
	ModAssert::ParameterList list("\"test\"");
	list << "test";

	RichBool::detail::String str = RichBool::ToString(list);
	META_ASSERT(rbSTRING_CS(str, ==, "  test\r\n"));
}

MA_TEST(StreamOut_WithExpressionAndMessage)
{
	ModAssert::ParameterList list("1 << \"test\"");
	list << 1 << "test";

	RichBool::detail::String str = RichBool::ToString(list);
	META_ASSERT(rbSTRING_CS(str, ==, "  1: 1\r\n  test\r\n"));
}
