#include "../inc/PmergeMe.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <regex>
#include <stdexcept>

std::vector<int> parseInput(char *nums[]) {
	std::vector<int> vec;
	for (int i = 0; nums[i]; ++i) {
		if (!std::regex_match(nums[i], std::regex("^[0-9]+$"))) {
			throw std::invalid_argument("Invalid element: " + std::string(nums[i]));
		}
		
		try {
			vec.push_back(std::stoi(nums[i]));
		} catch (std::exception& e) {
			std::cerr << "Invalid element: " << nums[i] << " : " << e.what() << std::endl;
		}
	}
	return (vec);
}

std::string	vecToString(const std::vector<int>& toPrint) {
	std::string result;
	for (auto el : toPrint) {
		result.append(std::to_string(el)).append(" ");
	}
	return (result);
}

int	main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <numbers to sort>" << std::endl;
		return 1;
	}
	try {
		// parse input
		std::vector<int> vec = parseInput(&argv[1]);
		std::cout << "Before: " << vecToString(vec) << std::endl;

		// sort with vector
		auto start = std::chrono::high_resolution_clock::now();
		PmergeMe<std::vector<int>> pmVec(vec.data(), vec.size());
		pmVec.sort();
		auto end = std::chrono::high_resolution_clock::now();
		auto vecDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		// sort with list
		start = std::chrono::high_resolution_clock::now();
		PmergeMe<std::list<int>> pmList(vec.data(), vec.size());
		pmList.sort();
		end = std::chrono::high_resolution_clock::now();
		auto listDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		// get sorted containers
		auto vecResult = pmVec.getSequence();
		auto listResult = pmList.getSequence();

		// check that results are equal
		if ((vecResult.size() != listResult.size())
			|| !std::equal(vecResult.begin(), vecResult.end(), listResult.begin(), listResult.end())) {
			throw std::logic_error("vector result and listue result differ");
		}

		// print results
		std::cout << "After: " << vecToString(vecResult) << std::endl;
		std::cout << "Time to process a range of " << vec.size() << " elements with std::vector<int>: " << vecDuration << " us" << std::endl;
		std::cout << "Time to process a range of " << vec.size() << " elements with std::list<int>: " << listDuration << " us" << std::endl;

	} catch (std::exception& e) {
		std::cerr << "Error occurred: " << e.what() << std::endl;
		return 1;
	}
	return (0);
}
