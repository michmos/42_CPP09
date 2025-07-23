
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>
#include "../../inc/PmergeMe.hpp"

TEST(PMergeMe, startIdx) {
	Element A = { 0, 2};
	EXPECT_EQ(A.startIdx(), 0);
	Element B = { 0, 5};
	EXPECT_EQ(B.startIdx(), 0);
	Element C = { 1, 5};
	EXPECT_EQ(C.startIdx(), 5);
	Element D = { 2, 2};
	EXPECT_EQ(D.startIdx(), 4);
}

TEST(PMergeMe, endIdx) {
	Element A = { 0, 2};
	EXPECT_EQ(A.endIdx(), 1);
	Element B = { 0, 5};
	EXPECT_EQ(B.endIdx(), 4);
	Element C = { 1, 5};
	EXPECT_EQ(C.endIdx(), 9);
	Element D = { 2, 2};
	EXPECT_EQ(D.endIdx(), 5);
}

class PMergeMeTest : public testing::Test {
protected:
	PMergeMeTest() 
		: sequence({0, 1, 2, 3, 4, 5, 6, 7}),
		pmerge(sequence.data(), sequence.size())
	{
	}

	bool	isEqual(const std::vector<int>& toComp) {
			return (pmerge.getSequence() == toComp);
	}

	std::vector<int> sequence;
	PmergeMe pmerge;
};

TEST_F(PMergeMeTest, swapElements1) {
	// swap 0 - 3 with 4 - 7
	Element A = {0, 4};
	Element B = {1, 4};
	pmerge.swapElements(A, B);
	EXPECT_TRUE(isEqual({4, 5, 6, 7, 0, 1, 2, 3}));
	pmerge.swapElements(B, A);
	EXPECT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
}

TEST_F(PMergeMeTest, swapElements2) {
	// swap 1 and 2
	Element A = {1, 1};
	Element B = {2, 1};
	pmerge.swapElements(A, B);
	EXPECT_TRUE(isEqual({0, 2, 1, 3, 4, 5, 6, 7}));
	pmerge.swapElements(B, A);
	EXPECT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
}

TEST_F(PMergeMeTest, swapElements3) {
	// swap 2-3 with 6-7
	Element A = {1, 2};
	Element B = {3, 2};
	pmerge.swapElements(A, B);
	EXPECT_TRUE(isEqual({0, 1, 6, 7, 4, 5, 2, 3}));
	pmerge.swapElements(B, A);
	EXPECT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
}

TEST_F(PMergeMeTest, swapElements_outOfRange) {
	// B element is just not out of range
	Element A = {1, 1};
	Element B = {7, 1};
	EXPECT_NO_THROW(pmerge.swapElements(A, B));
	// B element is just out of range
	B = {8, 1};
	EXPECT_THROW(pmerge.swapElements(A, B), std::out_of_range);
}

TEST_F(PMergeMeTest, moveElement_toFront) {
	Element toMove = {1, 2}; // element 1 with size 2
	ASSERT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
	pmerge.moveElement(toMove, 0); // move to front
	if (isEqual({2, 3, 0, 1, 4, 5, 6, 7})) {
		SUCCEED();
	} else {
		std::string sequence;
		for (auto el : pmerge.getSequence()) {
			sequence += std::to_string(el) +  " ";
		}
		FAIL() << "actual sequence: " << sequence;
	}
}

TEST_F(PMergeMeTest, moveELement_toBack) {
	Element toMove = {1, 2}; // element 1 with size 2
	ASSERT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
	pmerge.moveElement(toMove, 3); // move to back
	if (isEqual({0, 1, 4, 5, 6, 7, 2, 3})) {
		SUCCEED();
	} else {
		std::string sequence;
		for (auto el : pmerge.getSequence()) {
			sequence += std::to_string(el) +  " ";
		}
		FAIL() << "actual sequence: " << sequence;
	}
}

TEST_F(PMergeMeTest, moveElement_dontMove) {
	Element toMove = {1, 2}; // element 1 with size 2
	ASSERT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
	pmerge.moveElement(toMove, 1); // move don't move
	if (isEqual({0, 1, 2, 3, 4, 5, 6, 7})) {
		SUCCEED();
	} else {
		std::string sequence;
		for (auto el : pmerge.getSequence()) {
			sequence += std::to_string(el) +  " ";
		}
		FAIL() << "actual sequence: " << sequence;
	}
}

TEST_F(PMergeMeTest, moveElement_moveToOutOfBounds) {
	Element toMove = {0, 1}; // element 1 with size 2
	ASSERT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
	ASSERT_NO_THROW(pmerge.moveElement(toMove, 7));
	EXPECT_THROW(pmerge.moveElement(toMove, 8), std::out_of_range); // move don't move
}

TEST_F(PMergeMeTest, moveElement_moveFromOutOfBounds) {
	Element toMove = {8, 1}; // element 1 with size 2
	ASSERT_TRUE(isEqual({0, 1, 2, 3, 4, 5, 6, 7}));
	EXPECT_THROW(pmerge.moveElement(toMove, 0), std::out_of_range); // move don't move
}
