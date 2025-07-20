
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
	if (!std::regex_match(polishMathExpression, std::regex("^ *[0-9](?: +(?:[0-9]|[*+\\-\\/]))* *$"))) {
		throw std::invalid_argument("invalid expression");
	}

	std::stack<float> operands;
	auto performOperation = [&operands](std::function<float(float, float)> operate) {
		if (operands.size() < 2) {
			throw std::logic_error("not enough operands available to perform operation");
		}
		float op1 = operands.top(); operands.pop();
		float op2 = operands.top(); operands.pop();
		float result = operate(op2, op1);
		operands.push(result);
	};
	for (char c : polishMathExpression) {
		switch (c) {
			case ' ':
				continue;
			case '+':
				performOperation([](float a, float b) { return(a + b);} );
				break;
			case '*':
				performOperation([](float a, float b) { return(a * b);} );
				break;
			case '-':
				performOperation([](float a, float b) { return(a - b);} );
				break;
			case '/':
				performOperation([](float a, float b) { 
					if (b == 0) {
						throw std::logic_error("division by 0 not possible");
					}
					return(a / b);
				} );
				break;
			default:
				operands.push(c - '0');
				break;
		}
	}
	if (operands.size() > 1) {
		throw std::logic_error("not enough operators provided");
	}
	return (operands.top());
}

