
#include "../inc/PmergeMe.hpp"
#include <cstddef>
#include <stdexcept>


PmergeMe::PmergeMe(int nums[], std::size_t size) noexcept
{
	for (std::size_t i = 0; i < size; ++i) {
		sequ_.push_back(nums[i]);
	}
}

PmergeMe::~PmergeMe() noexcept {}

// PmergeMe::PmergeMe(const PmergeMe& toCopy) {
// 	*this = toCopy;
// }
// PmergeMe& PmergeMe::operator=(const PmergeMe& toAsgn) {
// 	if (this != &toAsgn) {
// 		sequ_ = toAsgn.sequ_;
// 	}
// 	return (*this);
// }

void	PmergeMe::swapElements(Element A, Element B) {
	if (A.elIdx == B.elIdx) {
		return; // no need to swap
	}
	if (A.endIdx() >= sequ_.size() || B.endIdx() >= sequ_.size()) {
		throw std::out_of_range("Element indices out of range");
	}

	std::swap_ranges(std::next(sequ_.begin(), A.startIdx()), std::next(sequ_.begin(), A.endIdx() + 1), std::next(sequ_.begin(), B.startIdx()));
}

void	PmergeMe::moveElement(Element toMove, size_t elmntInsertionIdx) {
	if (toMove.elIdx == elmntInsertionIdx) {
		return; // no need to move
	}

	size_t	insertionPosition = elmntInsertionIdx * toMove.getSize();
	if (toMove.endIdx() >= sequ_.size() || insertionPosition + toMove.getSize() - 1 > sequ_.size()) {
		throw std::out_of_range("Element indices out of range");
	}

	std::vector<int> tmp(std::next(sequ_.begin(), toMove.startIdx()), std::next(sequ_.begin(), toMove.endIdx() + 1));
	sequ_.erase(std::next(sequ_.begin(), toMove.startIdx()), std::next(sequ_.begin(), toMove.endIdx() + 1));
	sequ_.insert(std::next(sequ_.begin(), insertionPosition), tmp.begin(), tmp.end());
}


void	PmergeMe::sort(std::size_t elmntSize) {
	// each element can be defined by its size and its index inside the sequ_ence
	// on one recursion level all elements are of the same size
	// the last number of an element is it's comparison value
	size_t numElements = sequ_.size() / elmntSize;
	if (numElements < 2) {
		return; // basecase
	}

	Element left(0, elmntSize), right(1, elmntSize);
	for (; right.elIdx < numElements; ++right.elIdx, ++left.elIdx) {
		if (sequ_[right.endIdx()] < sequ_[left.endIdx()]) {
			swapElements(left, right);
		}
	}
	sort(elmntSize * 2);
}

std::vector<int>	PmergeMe::getSequence() const noexcept {
	return std::vector<int>(sequ_.begin(), sequ_.end());
}

