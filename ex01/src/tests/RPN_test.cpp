
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
	EXPECT_THROW(rpn("(1 + 1)"), std::invalid_argument);
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

TEST(invalidExpression, divisionByZero) {
	RPN rpn;
	EXPECT_THROW(rpn("3 3 3 - /"), std::logic_error);
	EXPECT_THROW(rpn("4 0 /"), std::logic_error);
}

TEST(invalidExpression, notEnoughOperators) {
	RPN rpn;
	EXPECT_THROW(rpn("3 3 3 -"), std::logic_error);
	EXPECT_THROW(rpn("4 0 2 + 5 6 2 -"), std::logic_error);
}

TEST(invalidExpression, notEnoughOperands) {
	RPN rpn;
	EXPECT_THROW(rpn("3 -"), std::logic_error);
	EXPECT_THROW(rpn("4 2 + * /"), std::logic_error);
}

TEST(validExpression, subjectTest) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("8 9 * 9 - 9 - 9 - 4 - 1 +"), 42);
	EXPECT_FLOAT_EQ(rpn("7 7 * 7 -"), 42);
	EXPECT_FLOAT_EQ(rpn("1 2 * 2 / 2 * 2 4 - +"), 0);
}

TEST(validExpression, multipleSpaces) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("8   9  * 9   - 9 - 9 - 4 - 1 +"), 42);
	EXPECT_FLOAT_EQ(rpn("  8   9  * 9   - 9 - 9 - 4 - 1 +"), 42);
	EXPECT_FLOAT_EQ(rpn("  8   9  * 9   - 9 - 9 - 4 - 1 +   "), 42);
}

TEST(validExpression, negativeResults) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("2 9 -"), -7);
	EXPECT_FLOAT_EQ(rpn("2 9 - 9 - 9 -"), -25);
}

TEST(validExpression, floatResults) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("2 4 /"), 0.5);
	EXPECT_FLOAT_EQ(rpn("2 8 /"), 0.25);
	EXPECT_FLOAT_EQ(rpn("2 8 / 2 8 / +"), 0.5);
}
