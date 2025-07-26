
#pragma once

#include <deque>
#include <vector>
#include "Element.hpp"

class PmergeMe {
private:
	std::deque<int>	pend_;
	std::deque<int>	sequ_;

public:
	PmergeMe(int nums[], std::size_t size) noexcept;
	PmergeMe(const PmergeMe& toCopy) = delete;
	PmergeMe& operator=(const PmergeMe& toAsgn) = delete;
	~PmergeMe() noexcept;

	size_t	getElmntInsrtnIdx(Element toInsrt, Element aCounterpart);

	void	sortElementPairs(size_t elmntSize, size_t numElements);
	void	buildPend(size_t elmntSize, size_t numElements);
	void	insrtPend(size_t elmntSize);

	void	swapElements(Element A, Element B) noexcept(false);
	void	addElementToPend(Element toAdd);
	int		insrtElementFromPend(Element toInsrt, Element aCounterpart);

	void	sort(std::size_t elementSize);

	std::vector<int>	getSequence() const noexcept;
};

