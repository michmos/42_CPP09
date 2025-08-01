
#include <climits>
#include <gtest/gtest.h>
#include <random>
#include "../../inc/PmergeMe.hpp"

void	testSort(std::vector<int> vecToSort) {
	PmergeMe<std::vector<int>> pm(vecToSort.data(), vecToSort.size());
	pm.sort();
	auto res = pm.getSequence();
	std::sort(vecToSort.begin(), vecToSort.end());
	if (res == vecToSort) {
		SUCCEED();
	} else {
		FAIL();
	}
}

TEST(PmergeMe, evenNumElements_unique) {
	std::vector<int> vec = {4, 3, 2, 1};
	testSort(vec);
	vec = { -20, 10, 4, 90, 102491, -124};
	testSort(vec);
	vec =  {11,2, 17, 0, 16,
		    8, 6, 15, 10, 3,
		  21,1,18, 9, 14, 
		  19,12, 5,4, 20, 13, 7};
	testSort(vec);
}

TEST(PmergeMe, oddNumElements_unique) {
	std::vector<int> vec = {5, 1, 3};
	testSort(vec);
	vec = {100, -50, 0, 25, -75};
	testSort(vec);
	vec = {7, 2, 9, 4, 1, 8, 3};
	testSort(vec);
}

TEST(PmergeMe, edgeValues_unique) {
	std::vector<int> vec = {INT_MIN, 0, INT_MAX};
	testSort(vec);
	vec = {INT_MAX, INT_MIN, 1, -1, 0};
	testSort(vec);
	vec = {INT_MIN, INT_MAX, -100, 100, 0, 50, -50};
	testSort(vec);
}

TEST(PmergeMe, withDuplicates) {
	std::vector<int> vec = {2, 2, 1, 3, 3, 1};
	testSort(vec);
	vec = {5, 5, 5, 5, 5};
	testSort(vec);
	vec = {INT_MIN, INT_MAX, INT_MAX, INT_MIN, 0, 0};
	testSort(vec);
}

TEST(PmergeMe, singleElement) {
	std::vector<int> vec = {2};
	testSort(vec);
}

TEST(PmergeMe, emptyArray) {
	std::vector<int> vec = {};
	testSort(vec);
}

TEST(PmergeMe, threeThousandElements_unsorted) {
		std::vector<int> vec;
	for (int i = 0; i < 3000; ++i) {
		vec.push_back(i * 3 - 100); // unique values
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vec.begin(), vec.end(), g);
	testSort(vec);
}

TEST(PmergeMe, threeThousandElements_sorted) {
		std::vector<int> vec;
	for (int i = 0; i < 3000; ++i) {
		vec.push_back(i); // unique values
	}
	testSort(vec);
}

