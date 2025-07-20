#pragma once

#include <string>

class RPN {
public:
	RPN();
	RPN(const RPN& toCopy) = delete;
	RPN& operator=(const RPN& toAsgn) = delete;
	~RPN();

	float operator()(const std::string& polishMathExpression);
};
