#include "../inc/Date.hpp"
#include <iomanip>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

static const std::unordered_map<unsigned int, unsigned int> g_daysInMonth = {
	{1, 31}, {2, 28}, {3, 31}, {4, 30},
	{5, 31}, {6, 30}, {7, 31}, {8, 31},
	{9, 30}, {10, 31}, {11, 30}, {12, 31}
};

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
	} else if (day > g_daysInMonth.at(month)) {
			return ("month " + std::to_string(month) + " doesn't have 31 days");
	}
	return (std::nullopt);
}

Date::Date(const std::string& date) {
	if (!std::regex_match(date, std::regex(REGEX_DATE))) {
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


std::string Date::decrementDate() {
	if (day_ > 1) { 			// same month
		day_--;
	} else if (month_ > 1) {	// last mont
		month_--;
		day_ = g_daysInMonth.at(month_);
	} else {					// last year
		year_--;
		month_ = 12;
		day_ = 31;
	}
	return (getDate());
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return (os);
}

int Date::getYear() const { return year_; }
int Date::getMonth() const { return month_; }
int Date::getDay() const { return day_; }

std::string Date::getDate() const {
	std::ostringstream oss;
	oss << year_
		<< "-" << std::setw(2) << std::setfill('0') << month_
		<< "-" << std::setw(2) << std::setfill('0') << day_;
	return oss.str();
}

