
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

TEST(validExpression, subjectTest) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("8 9 * 9 - 9 - 9 - 4 - 1 +"), 42);
	EXPECT_FLOAT_EQ(rpn("7 7 * 7 -"), 42);
	EXPECT_FLOAT_EQ(rpn("1 2 * 2 / 2 * 2 4 - +"), 0);
}

TEST(validExpression, multipleSpaces) {
	RPN rpn;
	EXPECT_FLOAT_EQ(rpn("8   9  * 9   - 9 - 9 - 4 - 1 +"), 42);
}
