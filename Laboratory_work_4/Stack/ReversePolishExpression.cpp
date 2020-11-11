#include "ReversePolishExpression.h"

static constexpr char kOpenBracket = '(';
static constexpr char kCloseBracket = ')';
static constexpr char kPlus = '+';
static constexpr char kMinus = '-';
static constexpr char kMul = '*';
static constexpr char kDiv = '/';
static constexpr char kPower = '^';



bool SymbolIsOperator(const char symbol) {

	static const std::string operators{ kOpenBracket, kCloseBracket, kPlus, kMinus, kMul, kDiv, kPower };

	if (operators.find(symbol) != std::string::npos) return true;

	return false;

}

Priority ReturnOperatorPriority(const char symbol) {

	switch (symbol) {
	case kOpenBracket: return 0;
	case kCloseBracket: return 1;
	case kPlus: return 2;
	case kMinus: return 2;
	case kMul: return 3;
	case kDiv: return 3;
	case kPower: return 4;
	};

}

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

	Stack<char> operators_stack;

	std::string reverse_pol_expr{};
	reverse_pol_expr.reserve(expression.size());

	for (auto it = expression.cbegin(); it != expression.cend(); it++) {

		const char symbol = *it;

		if (SymbolIsOperator(symbol)) {

			if (!operators_stack.empty()) {

				const Priority symbol_priority = ReturnOperatorPriority(symbol);
				const char top_operator = operators_stack.top();
				Priority stack_top_priority = ReturnOperatorPriority(top_operator);
				const bool push_to_stack = (symbol_priority == 0) || (symbol_priority >= stack_top_priority);

				if (push_to_stack) operators_stack.push(symbol);
				else
					if (symbol != kCloseBracket) {
						
						char top_operator = operators_stack.pop();
						reverse_pol_expr.push_back(top_operator);

						bool stack_is_empty = operators_stack.empty();
						if (!stack_is_empty) {

							Priority top_operator_priority = ReturnOperatorPriority(operators_stack.top());
							
							while (top_operator_priority >= symbol_priority && !stack_is_empty) {

								if (!operators_stack.empty()) {

									top_operator = operators_stack.pop();
									reverse_pol_expr.push_back(top_operator);
									top_operator_priority = ReturnOperatorPriority(top_operator);

								}
								else
									stack_is_empty = true;
							}

						}
						operators_stack.push(symbol);
						
					}
					else {

						bool stack_is_empty = false;
						char top_operator = operators_stack.pop();
					
						while (top_operator != kOpenBracket && !stack_is_empty){
							
							reverse_pol_expr.push_back(top_operator);
							
							if (!operators_stack.empty())
								top_operator = operators_stack.pop();
							else
								stack_is_empty = true;

						} 
						

					}


			}
			else
				operators_stack.push(symbol);

		}//Symbol is operand
		else
			reverse_pol_expr.push_back(symbol);

	}

	while (!operators_stack.empty()) {
		
		const char top_operator = operators_stack.pop();
		reverse_pol_expr.push_back(top_operator);

	}

	return reverse_pol_expr;
}