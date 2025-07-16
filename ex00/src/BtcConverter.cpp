
#include "../inc/BtcConverter.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <stdexcept>
#include "../inc/Date.hpp"


BtcConverter::BtcConverter(const std::string& pathToCsv) {
	// open csv file
	std::ifstream	csvFile(pathToCsv);
	if (csvFile.fail()) {
		throw std::invalid_argument("Couldn't open file: " + pathToCsv + ": " + strerror(errno));
	}

	// construct map of exchange rates from csv file
	std::string	line;
	for (std::size_t lineNbr = 0; std::getline(csvFile, line); ++lineNbr) {
		// skip header line
		if (lineNbr == 0) { continue; }

		std::smatch match;
		bool lineIsValid = false;
		if (std::regex_match(line, match, std::regex("(" REGEX_DATE "),(" REGEX_NUMBER ")"))) {
			std::string date = match[1];
			std::string exchangeRate = match[2];
			if (lineNbr == 1) {
				oldestDate_ = date;
			}

			try {
				float exRate = std::stof(exchangeRate);
				exchangeRate_[date] = exRate;
				lineIsValid = true;
			} catch (std::exception&) {}
		}
		if (!lineIsValid) {
			std::cerr << "Invalid line in csv: line " << lineNbr << ": " << line << std::endl;
		}
	}
}

// BtcConverter::BtcConverter(const BtcConverter& toCopy) {
// 	*this = toCopy;
// }

// BtcConverter& BtcConverter::operator=(const BtcConverter& toAsgn)  {
// 	if (this != &toAsgn) {
// 		exchangeRate_ = toAsgn.exchangeRate_;
// 	}
// 	return (*this);
// }

BtcConverter::~BtcConverter() {}

std::optional<float>	BtcConverter::getValue(const std::string& valuationDate, float amount) const noexcept(false) {
	Date date(valuationDate);
	std::string sDate = date.getDate();
	while (sDate >= oldestDate_) {
		auto it = exchangeRate_.find(sDate);
		if (it != exchangeRate_.end()) {
			return (amount * it->second);
		}
		date.decrementDate();
		sDate = date.getDate();
	}
	return std::nullopt;
}
