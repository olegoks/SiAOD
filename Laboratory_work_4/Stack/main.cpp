#include "Stack.h"
#include <regex>
#include <string>
#include <limits>

inline static bool InputIsCorrect(const std::string& input_str) {
	//[(\s)(\()(\))(\+)(\-)(\\)(\*)(\d)]+
	static const std::regex regular_expression{ "([a-z0-9\-\+\(\)\*/]+)" };

	return std::regex_match(input_str.cbegin(), input_str.cend(), regular_expression);
}

static std::string EnterString() {

	using std::cin;
	static constexpr long long max_stream_size = std::numeric_limits<std::streamsize>::max();
	static constexpr char endl = '\n';
	static constexpr size_t kMaxExprLength = 255;

	std::unique_ptr<char> input_string{(char*) new char[kMaxExprLength]};

	cin.clear();
	cin.getline(input_string.get(), max_stream_size, endl);

	if (!cin.good())
		exit(EXIT_FAILURE);

	cin.clear();

	return std::string(input_string.get());

}

void PrintString(const std::string& string) {

	std::cout << string << std::endl;

	if (!std::cout.good())
		exit(EXIT_FAILURE);

	std::cout.clear();
}

static std::string EnterExpression() {

	static constexpr const char* const enter_expression = "Enter expression.";
	static constexpr const char* const try_again = "Incorrect input. Please, try again.";
	bool input_is_correct = false;
	std::string input_expression{};

	do {

		system("cls");
		PrintString(enter_expression);
		input_expression = EnterString();
		input_is_correct = InputIsCorrect(input_expression);

		if (!input_is_correct) {

			PrintString(try_again);
			system("pause");

		}

	} while (!input_is_correct);

	return input_expression;
}

int main() {

	std::cout << EnterExpression() << std::endl;
	std::cout << "Success input!" << std::endl;

	return 0;
}