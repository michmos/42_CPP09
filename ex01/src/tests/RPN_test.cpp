
#include <gtest/gtest.h>
#include <stdexcept>
#include "../../inc/RPN.hpp"

TEST(invalidExpression, noSpace) {
	RPN rpn;
	EXPECT_THROW(rpn("1 2+"), std::invalid_argument);
	EXPECT_THROW(rpn("1 2+"), std::invalid_argument);
	EXPECT_THROW(rpn("1 23 +"), std::invalid_argument);
	EXPECT_THROW(rpn("12 3 +"), std::invalid_argument);
}

TEST(invalidExpression, invalidChars) {
	RPN rpn;
	EXPECT_THROW(rpn("1 2 a"), std::invalid_argument);
	EXPECT_THROW(rpn("1 2 ."), std::invalid_argument);
	EXPECT_THROW(rpn("a 2 3"), std::invalid_argument);
	EXPECT_THROW(rpn("1 a 3"), std::invalid_argument);
	EXPECT_THROW(rpn("1 \\ 3"), std::invalid_argument);
}

TEST(invalidExpression, emptyString) {
	RPN rpn;
	EXPECT_THROW(rpn(""), std::invalid_argument);
}

TEST(invalidExpression, startingWithOperator) {
	RPN rpn;
	EXPECT_THROW(rpn("+ 3 3 +"), std::invalid_argument);
	EXPECT_THROW(rpn("* 3 3 +"), std::invalid_argument);
	EXPECT_THROW(rpn("- 3 3 +"), std::invalid_argument);
	EXPECT_THROW(rpn("/ 3 3 +"), std::invalid_argument);
}
