#include "ReversePolishExpression.h"

static constexpr char kOpenBracket = '(';
static constexpr char kCloseBracket = ')';
static constexpr char kPlus = '+';
static constexpr char kMinus = '-';
static constexpr char kMul = '*';
static constexpr char kDiv = '/';
static constexpr char kPower = '^';



bool SymbolIsOperator(const char symbol) {

	static const std::string operators{ kOpenBracket, kCloseBracket, kPlus, kMinus, kMul, kDiv, kPower, '!' };

	if (operators.find(symbol) != std::string::npos) return true;

	return false;

}

Priority ReturnPriorityStack(const char symbol) {

	if (SymbolIsOperator(symbol)) {

		switch (symbol) {
		case kOpenBracket: return 0;
		case kCloseBracket: return 10;
		case kPlus: return 2;
		case kMinus: return 2;
		case kMul: return 4;
		case kDiv: return 4;
		case kPower: return 5;
		case '!':return -1;
		};

	}
	else
		return 8;

}

Priority ReturnPriorityRel(const char symbol) {

	if (SymbolIsOperator(symbol)) {

		switch (symbol) {
		case kOpenBracket: return 9;
		case kCloseBracket: return 0;
		case kPlus: return 1;
		case kMinus: return 1;
		case kMul: return 3;
		case kDiv: return 3;
		case kPower: return 6;
		};

	}
	else
		return 7;

}

//Priority ReturnPriorityRel(const char symbol) {
//
//	switch (symbol) {
//	case kOpenBracket: return 9;
//	case kCloseBracket: return 0;
//	case kPlus: return 1;
//	case kMinus: return 1;
//	case kMul: return 3;
//	case kDiv: return 3;
//	case kPower: return 6;
//	};
//
//}

int CountRang(const std::string& expression) {

	std::regex operands{ "([a-z])" };
	std::regex operators{ "([\-\+\*/\^])" };
	int rang = 0;

	std::string symbol;

	for (auto it = expression.cbegin(); it != expression.cend(); it++) {

		//Two function calls:)
		symbol = *it;
		bool symbol_is_operand = std::regex_match(symbol, operands);
		bool symbol_is_operator = std::regex_match(symbol, operators);

		if (symbol_is_operand)
			rang++;
		else
			if (symbol_is_operator)
				rang--;

	}

	return rang;
}

std::string ConvertToRevPolExpr(const std::string& expression) {

	Stack<char> stack;

	std::string reverse_pol_expr{};
	reverse_pol_expr.reserve(expression.size());

	stack.push('!');

	for (auto it = expression.cbegin(); it != expression.cend(); it++) {

		char symbol = *it;

		Priority priority = ReturnPriorityRel(symbol);

		if (priority == 7) {
			reverse_pol_expr.push_back(symbol);
			continue;
		}

		if (priority == 0) {

			while (ReturnPriorityStack(stack.top()) != 0)
				reverse_pol_expr.push_back(stack.pop());

			symbol = stack.pop();
			continue;
		}

		if (priority > ReturnPriorityStack(stack.top())) {
			stack.push(symbol);
		}
		else {

			while (priority <= ReturnPriorityStack(stack.top())) {
				reverse_pol_expr.push_back(stack.pop());

			}

			stack.push(symbol);

		}

	}

	if (!stack.empty() ) {
		char symbol = stack.top();

		while (!stack.empty() && stack.top() != '!') {
			reverse_pol_expr.push_back(stack.pop());
			if(!stack.empty())
			symbol = stack.top();
		}
	}

	return reverse_pol_expr;
}