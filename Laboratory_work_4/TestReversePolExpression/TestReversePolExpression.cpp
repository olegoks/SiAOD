
#include "CppUnitTest.h"
#include "../Stack/ReversePolishExpression.h"
#include <string>
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestReversePolExpression
{
	TEST_CLASS(TestReversePolExpression)
	{
	public:
		
		TEST_METHOD(Test1)
		{
			const std::string correct_output = {"abc*+dab+/-"};
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "a+b*c-d/(a+b)" }) == correct_output);

		}

		TEST_METHOD(Test2)
		{
			const std::string correct_output = { "abc+-d*ef+^" };
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "((a-(b+c))*d)^(e+f)" }) == correct_output);

		}

		TEST_METHOD(Test3)
		{
			const std::string correct_output = { "abc*+d+" };
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "a+b*c+d" }) == correct_output);

		}

		TEST_METHOD(Test4)
		{
			const std::string correct_output = { "abcdef+/-*+" };
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "a+b*(c-d/(e+f))" }) == correct_output);

		}

		TEST_METHOD(Test5)
		{
			const std::string correct_output = { "ab+c*d-" };
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "((a+b)*c)-d" }) == correct_output);

		}

		TEST_METHOD(Test6)
		{
			const std::string correct_output = { "ab+cd-*" };
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "(a+b)*(c-d)" }) == correct_output);

		}

	};
}
