#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#define REGEX_NUMBER "(?:\\+|-)?[0-9]+(?:\\.[0-9]+)?"

class BtcConverter {
private:
	std::unordered_map<std::string, float> exchangeRate_;
	std::string	oldestDate_;

public:
	// class that stores exchange rate data from csv file
	// @param path to csv file with exchange rate data in the following format
	// YYYY-MM-DD,<FloatWithDot>
	BtcConverter(const std::string& pathToCsv) noexcept(false);
	~BtcConverter();

	BtcConverter(const BtcConverter& toCopy) = delete;
	BtcConverter& operator=(const BtcConverter& toAsgn) = delete;

	// @brief function to determine the value of <amount> bitcoins at <date>
	// @param date of valuation in YYYY-MM-DD format
	// @param amount of bitcoins to value
	// @return value of bitcoins if valuationDate or newer date found in database, otherwise std::nullopt
	std::optional<float>	getValue(const std::string& valuationDate, float amount) const noexcept(false);
};
