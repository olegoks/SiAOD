
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
		
		TEST_METHOD(Test1){
		
			const std::string correct_output{"abc*+dab+/-"};
			const std::string input_expression{ "a+b*c-d/(a+b)" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(input_expression) == correct_output);
			
		}

		TEST_METHOD(Test2)
		{
			const std::string correct_output = { "abc+-d*ef+^" };
			const std::string input_expression{ "((a-(b+c))*d)^(e+f)" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "((a-(b+c))*d)^(e+f)" }) == correct_output);

		}

		TEST_METHOD(Test3)
		{
			const std::string correct_output = { "abc*+d+" };
			const std::string input_expression{ "a+b*c+d" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "a+b*c+d" }) == correct_output);

		}

		TEST_METHOD(Test4)
		{
			const std::string correct_output = { "abcdef+/-*+" };
			const std::string input_expression{ "a+b*(c-d/(e+f))" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "a+b*(c-d/(e+f))" }) == correct_output);

		}

		TEST_METHOD(Test5)
		{
			const std::string correct_output = { "ab+c*d-" };
			const std::string input_expression{ "((a+b)*c)-d" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "((a+b)*c)-d" }) == correct_output);

		}

		TEST_METHOD(Test6)
		{
			const std::string correct_output = { "ab+cd-*" };
			const std::string input_expression{  "(a+b)*(c-d)" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "(a+b)*(c-d)" }) == correct_output);

		}

 		TEST_METHOD(Test7)
		{
			const std::string correct_output = { "ab+d*kxy^^-mn+/" };
			const std::string input_expression{ "((a+b)*d-k^x^y)/(m+n)" };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "((a+b)*d-k^x^y)/(m+n)" }) == correct_output);

		}

		TEST_METHOD(Test8)
		{
			const std::string correct_output = { "wab^cygd*-*+uv^^*" };
			const std::string input_expression{ "w*(a^b+c*(y-g*d))^u^v"  };
			Assert::IsTrue(1 == CountRang(input_expression));
			Assert::IsTrue(ConvertToRevPolExpr(std::string{ "w*(a^b+c*(y-g*d))^u^v" }) == correct_output);

		}

		TEST_METHOD(TestRang1)
		{

			const std::string input_expression{ "w**(a^b+c*(y-g*d))^u^v" };
			Assert::IsTrue(0 == CountRang(input_expression));
			
		}

		TEST_METHOD(TestRang2)
		{

			const std::string input_expression{ "w*(a^b+c*(y-g*d))^uv" };
			Assert::IsTrue(2 == CountRang(input_expression));

		}

		TEST_METHOD(TestRang3)
		{

			const std::string input_expression{ "w(a^b+c(y-g*d))^u^v" };
			Assert::IsTrue(3 == CountRang(input_expression));

		}

	};
}
