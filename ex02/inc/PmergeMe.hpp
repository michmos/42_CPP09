
#pragma once

#include <deque>
#include <vector>
#include "Element.hpp"

class PmergeMe {
private:
	size_t			mainChainEndIdx_;	// idx where the main chain ends
	size_t			pendStartIdx_;		// idx in sequ_ where the pend starts (= mainChainEndIdx_ + 1)
	std::deque<int>	sequ_;
	// size_t			ignoredItemsIdx_;
	
	void			sort(std::size_t elementSize);

public:
	PmergeMe(int nums[], std::size_t size) noexcept;
	PmergeMe(const PmergeMe& toCopy) = delete;
	PmergeMe& operator=(const PmergeMe& toAsgn) = delete;
	~PmergeMe() noexcept;

	void				swapElements(Element A, Element B) noexcept(false);

	// @brief	move element to a different position. All elements between its current and new position:
	// - if moved to front: will be pushed one position back
	// - if move to back: will be pushed one position to the front
	// @param Element to move
	// @param element idx defining new position
	void				moveElement(Element toMove, size_t elmntInsrtIdx) noexcept(false);
	std::vector<int>	getSequence() const noexcept;
};

