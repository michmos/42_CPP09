
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

void	PmergeMe::addElementToPend(Element toAdd) {
	if (toAdd.endIdx() >= sequ_.size()) {
		throw std::out_of_range("Element indices out of range");
	}

	pend_.insert(pend_.end(),
			  std::next(sequ_.begin(), toAdd.startIdx()), 
			  std::next(sequ_.begin(), toAdd.endIdx() + 1));
	sequ_.erase(std::next(sequ_.begin(), toAdd.startIdx()), 
			 std::next(sequ_.begin(), toAdd.endIdx() + 1));
}

// uses binary search to find the correct position where 
// to insert the element toInsrt so that the sequence
// stays ordered
size_t	PmergeMe::getElmntInsrtnIdx(Element toInsrt, Element aCounterpart) {
	size_t elSize = toInsrt.getSize();
	int insrtValue = pend_[toInsrt.endIdx()];
	size_t numElements = sequ_.size() / elSize;

	Element left({0, elSize});
	Element right({aCounterpart.elIdx, elSize});
	if (aCounterpart.elIdx > numElements - 1) { // no counterpart
		right.elIdx = numElements;
	}

	
	while (left.elIdx < right.elIdx) {
		Element mid({(left.elIdx + right.elIdx) / 2, elSize});

		if (insrtValue < sequ_[mid.endIdx()]) {
			right.elIdx = mid.elIdx;
		} else {
			left.elIdx = mid.elIdx + 1;
		}
	}
	return (left.elIdx);
}

int	PmergeMe::insrtElementFromPend(Element toInsrt, Element aCounterpart) {
	size_t elmntInsertionIdx = getElmntInsrtnIdx(toInsrt, aCounterpart);
	size_t insertionPosition = elmntInsertionIdx * toInsrt.getSize();

	sequ_.insert(std::next(sequ_.begin(), insertionPosition), 
			  std::next(pend_.begin(), toInsrt.startIdx()),
			  std::next(pend_.begin(), toInsrt.endIdx()+ 1));
	return (elmntInsertionIdx);
}

void	PmergeMe::sortElementPairs(size_t elmntSize, size_t numElements) {
	Element left(0, elmntSize), right(1, elmntSize);
	for (; right.elIdx < numElements; right.elIdx+=2, left.elIdx+=2) {
		if (sequ_[left.endIdx()] > sequ_[right.endIdx()]) {
			swapElements(left, right);
		}
	}
}

void	PmergeMe::buildPend(size_t elmntSize, size_t numElements) {
	// elements are in the following order: b1 a1 b2 a2
	// move b elements to pend starting with b2 (which is at index 2),
	Element b(2, elmntSize);
	for (; b.elIdx < numElements; ++b.elIdx, --numElements) {
		addElementToPend(b); // TODO: rename to move
	}
}

void	PmergeMe::insrtPend(size_t elmntSize) {
	std::vector<int> elmntInsrtIdxCount(sequ_.size() + pend_.size(), 0);

	unsigned int lstJacobsthalNum = 1;
	unsigned int currJacobsthalNum = 3;
	size_t	elementsToInsert = pend_.size() / elmntSize;

	size_t bLable = currJacobsthalNum;
	for (; elementsToInsert > 0; --elementsToInsert, --bLable) {
		if (bLable == lstJacobsthalNum) {	// update Jacobsthal number
			unsigned int tmp = currJacobsthalNum;
			currJacobsthalNum += 2 * lstJacobsthalNum;
			lstJacobsthalNum = tmp;
			bLable = currJacobsthalNum;
			if (lstJacobsthalNum + elementsToInsert < currJacobsthalNum) {
				bLable = lstJacobsthalNum + elementsToInsert;
			}
		}
		Element toInsrt(bLable - 2, elmntSize);
		Element aCounterpart(bLable, elmntSize);
		for (int e = 0; e <= aCounterpart.elIdx; ++e) {
			aCounterpart.elIdx += elmntInsrtIdxCount[e];
		}
		size_t elmntInsrtIdx = insrtElementFromPend(toInsrt, aCounterpart);
		elmntInsrtIdxCount[elmntInsrtIdx]++;
	}
}

void	PmergeMe::sort(std::size_t elmntSize) {
	size_t numElements = sequ_.size() / elmntSize;
	if (numElements < 2) {	// basecase
		return;
	}
	sortElementPairs(elmntSize, numElements);	// step 1

	sort(elmntSize * 2);

	buildPend(elmntSize, numElements);			// step 2
	insrtPend(elmntSize);						// step 3
	pend_.clear();
}



std::vector<int>	PmergeMe::getSequence() const noexcept {
	return std::vector<int>(sequ_.begin(), sequ_.end());
}

