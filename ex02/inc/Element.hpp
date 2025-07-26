
#pragma once

#include <cstddef>
#include <deque>
#include <iterator>

class Element {
private:
	size_t	elSize;

public:
	Element(std::size_t elIdx, std::size_t elSize) noexcept;
	Element(const Element& toCopy);
	Element& operator=(const Element& toAsgn);
	~Element();

	size_t	elIdx;					// element index in the sequence
	size_t	startIdx() const;		// actual inclusive start index of the element in the sequence
	size_t	endIdx() const;			// actual inclusive end index of the element in the sequence
	size_t	getSize() const;		// returns the size of the element - how many numbers the range contains
	std::deque<int>::iterator it; 
};

