
#include <gtest/gtest.h>
#include "../../inc/PmergeMe.hpp"

void	testSort(std::vector<int> vecToSort) {
	PmergeMe pm(vecToSort.data(), vecToSort.size());
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
