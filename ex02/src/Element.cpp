
#include "../inc/Element.hpp"

Element::Element(std::size_t elIdx, std::size_t elSize) noexcept
	: elSize(elSize), elIdx(elIdx)
{
}

Element::Element(const Element& toCopy)
{
	*this = toCopy;
}

Element& Element::operator=(const Element& toAsgn)
{
	if (this != &toAsgn) {
		this->elIdx = toAsgn.elIdx;
		this->elSize = toAsgn.elSize;
	}
	return (*this);
}

Element::~Element() {}

size_t Element::startIdx() const
{
	return (this->elIdx * this->elSize);
}

size_t Element::endIdx() const
{
	return (this->startIdx() + this->elSize - 1);
}

size_t	Element::getSize() const {
	return (this->elSize);
}
