
#include <gtest/gtest.h>
#include "../../inc/Element.hpp"

TEST(Element, startIdx) {
	Element A = { 0, 2};
	EXPECT_EQ(A.startIdx(), 0);
	Element B = { 0, 5};
	EXPECT_EQ(B.startIdx(), 0);
	Element C = { 1, 5};
	EXPECT_EQ(C.startIdx(), 5);
	Element D = { 2, 2};
	EXPECT_EQ(D.startIdx(), 4);
}

TEST(Element, endIdx) {
	Element A = { 0, 2};
	EXPECT_EQ(A.endIdx(), 1);
	Element B = { 0, 5};
	EXPECT_EQ(B.endIdx(), 4);
	Element C = { 1, 5};
	EXPECT_EQ(C.endIdx(), 9);
	Element D = { 2, 2};
	EXPECT_EQ(D.endIdx(), 5);
}

