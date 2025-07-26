#include "../inc/PmergeMe.hpp"
#include <iostream>

int	main(void) {
	std::vector<int> vec = 
		{11 ,2, 17, 0, 16,
		8, 6, 15, 10, 3,
		21, 1,18, 9, 14, 
		19, 12, 5,4, 20, 13, 7};
	PmergeMe pmerge(vec.data(), vec.size());
	pmerge.sort(1);
	std::vector<int> result = pmerge.getSequence();
	for (auto el : result) {
		std::cout << el << " ";
	}
}
