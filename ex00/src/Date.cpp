#include "../inc/Date.hpp"
#include <iostream>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>

static bool isLeapYear(int year) {
	// special rules for centuries
	if (year % 100 == 0)
		return (year % 400 == 0);
	// rule for every other year
	return (year % 4 == 0);
}

// checks whether the date exists
static std::optional<std::string>	validityCheck(unsigned int year, unsigned int month, unsigned int day) {
	if (month < 1 || month > 12) {
		return ("month must be in range: 1 - 12");
	}
	if (day < 1 || day > 31) {
		return ("day must be in range: 1 - 31");
	}
	if (month == 2) {
		if (day == 29 && !isLeapYear(year)) {
			return ("february doesn't have 29 days in year " + std::to_string(year));
		} else if (day > 29){
			return ("february doesn't have " + std::to_string(day) + " days");
		}
	} else if (day == 31 && ((month < 8 && month % 2 == 0)
							|| (month >= 8 && month % 2 == 1))) {
			return ("month " + std::to_string(month) + " doesn't have 31 days");
	}
	return (std::nullopt);
}

Date::Date(const std::string& date) {
	if (!std::regex_match(date, std::regex("[0-9]{4}(-[0-9]{2}){2}"))) {
		throw std::invalid_argument("invalid date format");
	}
	try {
		year_ = std::stoi(date.substr(0,4));
		month_ = std::stoi(date.substr(5, 2));
		day_ = std::stoi(date.substr(8));
	} catch (std::exception &e) {
		throw std::invalid_argument(std::string("invalid date: ") + e.what());
	}
	auto errMsg = validityCheck(year_, month_, day_);
	if (errMsg.has_value()) {
		throw std::invalid_argument("invalid date: " + errMsg.value());
	}
}

Date::Date(const Date& toCopy) {
	*this = toCopy;
}

Date& Date::operator=(const Date& toAsgn) {
	if (this !=  &toAsgn) {
		day_ = toAsgn.day_;
		month_ = toAsgn.month_;
		year_ = toAsgn.year_;
	}
	return (*this);
}

Date::~Date() {
}


void Date::advanceDate() {
	auto errMsg = validityCheck(year_, month_, day_ + 1);
	if (!errMsg) {
		day_++;
		return;
	}
	errMsg = validityCheck(year_, month_ + 1, 1);
	if (!errMsg) {
		month_++;
		day_ = 1;
		return;
	}
	year_++;
	month_ = 1;
	day_ = 1;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return (os);
}

inline int Date::getYear() const { return year_; }
inline int Date::getMonth() const { return month_; }
inline int Date::getDay() const { return day_; }
