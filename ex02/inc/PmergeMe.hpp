
#pragma once

#include "Element.hpp"
#include <vector>

template <typename Container = std::deque<int>>
class PmergeMe {
private:
	Container	pend_;
	Container	sequ_;

	//--------------------------------------------------------------------
	// stage 1: presorting elements
	//--------------------------------------------------------------------

	// swaps to elements within sequ_
	// THROW if A or B are invalid ranges
	void	swapElements(Element A, Element B) noexcept(false) {
		if (A.elIdx == B.elIdx) {
			return; // no need to swap
		}
		if (A.endIdx() >= sequ_.size() || B.endIdx() >= sequ_.size()) {
			throw std::out_of_range("Element indices out of range");
		}

		std::swap_ranges(std::next(sequ_.begin(), A.startIdx()), std::next(sequ_.begin(), A.endIdx() + 1), std::next(sequ_.begin(), B.startIdx()));
	}


	void	sortElementPairs(size_t elmntSize, size_t numElements) {
		Element left(0, elmntSize), right(1, elmntSize);
		for (; right.elIdx < numElements; right.elIdx+=2, left.elIdx+=2) {
			if (*std::next(sequ_.begin(), left.endIdx()) > *std::next(sequ_.begin(), right.endIdx())) {
				swapElements(left, right);
			}
		}
	}

	//--------------------------------------------------------------------
	// stage 2: build pend
	//--------------------------------------------------------------------

	// mv element toMove from sequ_ to the end of pend_
	void	mvElementToPend(Element toMove) {
		if (toMove.endIdx() >= sequ_.size()) {
			throw std::out_of_range("Element indices out of range");
		}

		pend_.insert(pend_.end(),
				std::next(sequ_.begin(), toMove.startIdx()), 
				std::next(sequ_.begin(), toMove.endIdx() + 1));
		sequ_.erase(std::next(sequ_.begin(), toMove.startIdx()), 
				std::next(sequ_.begin(), toMove.endIdx() + 1));
	}

	// moves b elements starting from b2 from sequ_ to pend_
	void	buildPend(size_t elmntSize, size_t numElements) {
		Element b(2, elmntSize);
		for (; b.elIdx < numElements; ++b.elIdx, --numElements) {
			mvElementToPend(b);
		}
	}

	//--------------------------------------------------------------------
	// stage 3: insert pend
	//--------------------------------------------------------------------

	// returns the element Index where @toInsrt should be inserted in sequ_
	// using binary search
	// @aCounterpart serves as the right boundary of the search
	size_t	getElmntInsrtnIdx(Element toInsrt, Element aCounterpart) {
		size_t elSize = toInsrt.getSize();
		int insrtValue = *std::next(pend_.begin(), toInsrt.endIdx());
		size_t numElements = sequ_.size() / elSize;

		Element left({0, elSize});
		Element right({aCounterpart.elIdx, elSize});
		if (aCounterpart.elIdx > numElements - 1) { // no counterpart
			right.elIdx = numElements;
		}

		
		while (left.elIdx < right.elIdx) {
			Element mid({(left.elIdx + right.elIdx) / 2, elSize});

			if (insrtValue < *std::next(sequ_.begin(), mid.endIdx())) {
				right.elIdx = mid.elIdx;
			} else {
				left.elIdx = mid.elIdx + 1;
			}
		}
		return (left.elIdx);
	}

	// inserts the element @toInsrt which should be referring to pend_ into
	// sequ_. 
	// @aCounterpart serves as a boundary for binary search.
	// The element is NOT removed from pend_
	int		insrtElementFromPend(Element toInsrt, Element aCounterpart) {
		size_t elmntInsertionIdx = getElmntInsrtnIdx(toInsrt, aCounterpart);
		size_t insertionPosition = elmntInsertionIdx * toInsrt.getSize();

		sequ_.insert(std::next(sequ_.begin(), insertionPosition), 
				std::next(pend_.begin(), toInsrt.startIdx()),
				std::next(pend_.begin(), toInsrt.endIdx()+ 1));
		return (elmntInsertionIdx);
	}

	static Element	getACounterpart(const std::vector<int>& elmntInsrtIdxCount, size_t bLable, size_t elmntSize) {
		Element aCounterpart(bLable, elmntSize);
		for (int e = 0; e <= aCounterpart.elIdx; ++e) {
			aCounterpart.elIdx += elmntInsrtIdxCount[e];
		}
		return (aCounterpart);
	}

	// assumes that currNum and lastNum are valid jacobsthal nums
	// applies jacobsthal formula to update both variables
	static void	updateJacobsthalNums(unsigned int& currNum, unsigned int& lastNum) {
		unsigned int tmp = currNum;;
		currNum += 2 * lastNum;
		lastNum = tmp;
	}

	void	insrtPend(size_t elmntSize) {
		unsigned int 	lstJTNum = 1;
		unsigned int 	currJTNum = 3;
		size_t numElmntsToInsert = pend_.size() / elmntSize;
		size_t 			bLable = (numElmntsToInsert > 1) ? 3 : 2;

		std::vector<int> eInsrtIdxCount(sequ_.size() + pend_.size(), 0);
		for (; numElmntsToInsert > 0; --numElmntsToInsert, --bLable) {
			if (bLable == lstJTNum) {
				updateJacobsthalNums(currJTNum, lstJTNum);

				bLable = currJTNum;
				if (lstJTNum + numElmntsToInsert < currJTNum) {
					bLable = lstJTNum + numElmntsToInsert;
				}
			}
			Element toInsrt(bLable - 2, elmntSize);
			Element aCounterpart = getACounterpart(eInsrtIdxCount, bLable, elmntSize);

			size_t eInsrtIdx = insrtElementFromPend(toInsrt, aCounterpart);
			eInsrtIdxCount[eInsrtIdx]++;
		}
	}

	//--------------------------------------------------------------------
	// general sorting algorithm
	//--------------------------------------------------------------------

	void	recSort(std::size_t elmntSize) {
		size_t numElements = sequ_.size() / elmntSize;
		if (numElements < 2) {	// basecase
			return;
		}
		sortElementPairs(elmntSize, numElements);	// step 1

		recSort(elmntSize * 2);

		buildPend(elmntSize, numElements);			// step 2
		insrtPend(elmntSize);						// step 3
		pend_.clear();
	}

public:
	PmergeMe(int nums[], std::size_t size) noexcept {
		for (std::size_t i = 0; i < size; ++i) {
			sequ_.push_back(nums[i]);
		}
	}
	PmergeMe(const PmergeMe& toCopy) = delete;
	PmergeMe& operator=(const PmergeMe& toAsgn) = delete;
	~PmergeMe() noexcept {}

	void	sort() {
		if (sequ_.size() < 2) {		// nothing to sort
			return;
		}
		recSort(1);
	}

	inline const Container&	getSequence() const noexcept {
		return sequ_;
	}
};

