#pragma once

#include <string>

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

	void advanceDate();
	inline int getYear() const { return year_; }
	inline int getMonth() const { return month_; }
	inline int getDay() const { return day_; }
};

std::ostream& operator<<(std::ostream& os, const Date& date);
