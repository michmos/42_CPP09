#pragma once

#include <string>
#define REGEX_DATE "[0-9]{4}(?:-[0-9]{2}){2}"

class Date {
private:
	int			day_;
	int			month_;
	int			year_;
	
public:
	Date(const std::string& date) noexcept(false);
	Date(const Date& toCopy);
	Date& operator=(const Date& toAsgn);
	~Date();

	std::string decrementDate();
	int getYear() const;
	int getMonth() const;
	int getDay() const;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
