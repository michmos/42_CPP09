
#include "../inc/RPN.hpp"
#include <cstring>
#include <regex>
#include <stack>
#include <stdexcept>

RPN::RPN() {
}

RPN::~RPN() {}

// RPN::RPN(const RPN& toCopy) {
// 	*this = toCopy;
// }
// RPN& RPN::operator=(const RPN& toAsgn) {
// 	return *this;
// }

float RPN::operator()(const std::string& polishMathExpression) {
	if (!std::regex_match(polishMathExpression, std::regex("^[0-9](?: (?:[0-9]|[*+\\-\\/]))*$"))) {
		throw std::invalid_argument("invalid expression");
	}

	// std::stack<unsigned int> operands;
	// auto performOperation = [&operands](std::function<int(int, int)> operate) {
	// 	int op1 = operands.top(); operands.pop();
	// 	int op2 = operands.top(); operands.pop();
	// 	int result = operate(op2, op1);
	// 	operands.push(result);
	// 	// TODO: maybe should be float instead and then stack needs to account for that as well
	// 	// TODO: check for size first 
	// };
	// for (char c : polishMathExpression) {
	// 	switch (c) {
	// 		case ' ':
	// 			continue;
	// 		case '+':
	// 			performOperation([](int a, int b) { return(a + b);} );
	// 			break;
	// 		case '*':
	// 			performOperation([](int a, int b) { return(a * b);} );
	// 			break;
	// 		case '-':
	// 			performOperation([](int a, int b) { return(a - b);} );
	// 			break;
	// 		case '/':
	// 			performOperation([](int a, int b) { return(a / b);} );
	// 			break;
	// 		default:
	// 			break;
	// 		// TODO: chek whether a b order is correct for - and /
	// 	}
	// }
	// // TODO: chek whether stack size = 1
	return (3.4);

}
