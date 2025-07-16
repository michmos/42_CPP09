
#include "../inc/BtcConverter.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <stdexcept>
#include <system_error>


BtcConverter::BtcConverter(const std::string& pathToCsv) {
	std::ifstream	csvFile(pathToCsv);
	
	if (csvFile.fail()) {
		throw std::invalid_argument("Couldn't open file: " + pathToCsv + ": " + strerror(errno));
	}

	std::string	line;
	for (std::size_t lineNbr = 0; std::getline(csvFile, line); ++lineNbr) {
		if (lineNbr == 0) { 
			continue; 
		}

		std::smatch match;
		bool lineIsValid = false;
		if (std::regex_match(line, match, std::regex("(" REGEX_DATE "),(" REGEX_NUMBER ")"))) {
			std::string date = match[1];
			if (lineNbr == 1) {
				oldestDate_ = date;
			}
			try {
				float value = std::stof(match[2]);
				exchangeRate_[date] = value;
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
