
#pragma once

#include <deque>
#include <vector>
#include "Element.hpp"

class PmergeMe {
private:
	std::deque<int>	pend_;
	std::deque<int>	sequ_;

	size_t	getElmntInsrtnIdx(Element toInsrt, Element aCounterpart);
	void	sortElementPairs(size_t elmntSize, size_t numElements);
	void	buildPend(size_t elmntSize, size_t numElements);
	void	insrtPend(size_t elmntSize);
	void	swapElements(Element A, Element B) noexcept(false);
	void	mvElementToPend(Element toMove);
	int		insrtElementFromPend(Element toInsrt, Element aCounterpart);
	void	recSort(std::size_t elementSize);

public:
	PmergeMe(int nums[], std::size_t size) noexcept;
	PmergeMe(const PmergeMe& toCopy) = delete;
	PmergeMe& operator=(const PmergeMe& toAsgn) = delete;
	~PmergeMe() noexcept;

	void	sort();
	std::vector<int>	getSequence() const noexcept;
};

