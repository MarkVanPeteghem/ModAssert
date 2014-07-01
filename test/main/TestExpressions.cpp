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

static const int n=2;
static const int array[] = { 1, 2, 3, 4, 5 };

MA_TEST(Expressions)
{
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n), NULL);
	MOD_ASSERT_P(n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("(n<<1)", n<<1), NULL);
	MOD_ASSERT_P((n<<1), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array[n<<1]", array[n<<1]), NULL);
	MOD_ASSERT_P(array[n<<1], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("(n<<1)", n<<1), NULL);
	MOD_ASSERT_P(n<<(n<<1), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("array[n<<1]", array[n<<1]), NULL);
	MOD_ASSERT_P(n<<array[n<<1], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("(n<<1)", n<<1)("n", n), NULL);
	MOD_ASSERT_P((n<<1)<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array[n<<1]", array[n<<1])("n", n), NULL);
	MOD_ASSERT_P(array[n<<1]<<n, n==1);

	EXPECT_NO_FAILURE;
}

MA_TEST(ExpressionsWithSpaces)
{
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n), NULL);
	MOD_ASSERT_P( n , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("( n << 1 )", n<<1), NULL);
	MOD_ASSERT_P( ( n << 1 ) , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array [ n << 1 ]", array[n<<1]), NULL);
	MOD_ASSERT_P( array [ n << 1 ] , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("( n << 1 )", n<<1), NULL);
	MOD_ASSERT_P( n << ( n << 1 ) , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("array [ n << 1 ]", array[n<<1]), NULL);
	MOD_ASSERT_P( n << array [ n << 1 ] , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("( n << 1 )", n<<1)("n", n), NULL);
	MOD_ASSERT_P( ( n << 1 ) << n , n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array [ n << 1 ]", array[n<<1])("n", n), NULL);
	MOD_ASSERT_P( array [ n << 1 ] << n, n==1);

	EXPECT_NO_FAILURE;
}

MA_TEST(MessageAndExpressions)
{
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n), NULL);
	MOD_ASSERT_P("test"<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("test"), NULL);
	MOD_ASSERT_P(n<<"test", n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("(n<<1)", n<<1), NULL);
	MOD_ASSERT_P("test"<<(n<<1), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("array[n<<1]", array[n<<1]), NULL);
	MOD_ASSERT_P("test"<<array[n<<1], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n)("(n<<1)", n<<1), NULL);
	MOD_ASSERT_P("test"<<n<<(n<<1), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n)("array[n<<1]", array[n<<1]), NULL);
	MOD_ASSERT_P("test"<<n<<array[n<<1], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("(n<<1)", n<<1)("n", n), NULL);
	MOD_ASSERT_P("test"<<(n<<1)<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("array[n<<1]", array[n<<1])("n", n), NULL);
	MOD_ASSERT_P("test"<<array[n<<1]<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array[n<<1]", array[n<<1])("test")("n", n), NULL);
	MOD_ASSERT_P(array[n<<1]<<"test"<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array[n<<1]", array[n<<1])("n", n)("test"), NULL);
	MOD_ASSERT_P(array[n<<1]<<n<<"test", n==1);

	EXPECT_NO_FAILURE;
}

MA_TEST(MessageAndExpressionsWithSpace)
{
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n), NULL);
	MOD_ASSERT_P("test" << n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("n", n)("test"), NULL);
	MOD_ASSERT_P(n << "test", n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("( n << 1 )", n<<1), NULL);
	MOD_ASSERT_P("test" << ( n << 1 ), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("array [ n << 1 ]", array[n<<1]), NULL);
	MOD_ASSERT_P("test" << array [ n << 1 ], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n)("( n << 1 )", n<<1), NULL);
	MOD_ASSERT_P("test" << n << ( n << 1 ), n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("n", n)("array [ n << 1 ]", array[n<<1]), NULL);
	MOD_ASSERT_P("test" << n << array [ n << 1 ], n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("( n << 1 )", n<<1)("n", n), NULL);
	MOD_ASSERT_P("test" << ( n << 1 ) << n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("test")("array [ n << 1 ]", array[n<<1])("n", n), NULL);
	MOD_ASSERT_P("test" << array [ n << 1 ] << n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array [ n << 1 ]", array[n<<1])("test")("n", n), NULL);
	MOD_ASSERT_P(array [ n << 1 ] << "test"<<n, n==1);
	EXPECT_ASSERT(false, "n==1", NULL, CreateParameterList()("array [ n << 1 ]", array[n<<1])("n", n)("test"), NULL);
	MOD_ASSERT_P(array [ n << 1 ] << n << "test", n==1);

	EXPECT_NO_FAILURE;
}
