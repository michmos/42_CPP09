#include "../inc/Date.hpp"
#include "../inc/BtcConverter.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>

#define CSV_PATH "data.csv"

void printInputError(size_t lineNbr, const std::string& str) {
	std::cerr << "Error in line: " << lineNbr << ": " << str << std::endl;
}

float getValue(const std::string& validationDate, const std::string& amount) {
	static BtcConverter converter(CSV_PATH);

	// create Date object as validity check
	Date date(validationDate);

	// convert btcAmount
	float btcAmount = std::stof(amount);
	if (btcAmount < 0) {
		throw std::invalid_argument("negative value");
	} 
	if (btcAmount > 1000) {
		throw std::invalid_argument("value > 1000");
	}

	// get total value
	auto convertedValue = converter.getValue(date.getDate(), btcAmount);
	if (!convertedValue) {
		throw std::invalid_argument("date before first database entry");
	}
	return (convertedValue.value());
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr <<"Usage: ./btc <pathToInputFile>" << std::endl;
		return 1;
	}
	
	try {
		// open input file
		std::ifstream	inputFile(argv[1]);
		if (inputFile.fail()) {
			std::cerr << "Could not open input file: " << strerror(errno) << std::endl;
			return 1;
		}

		std::string line;
		for (size_t lineNbr = 0; std::getline(inputFile, line); ++lineNbr) {
			if (line == "date | value" && lineNbr == 0) { continue; }

			// retrieve date and btcAmount and check syntax
			std::smatch match;
			if (!std::regex_match(line, match, std::regex("(" REGEX_DATE ") \\| (" REGEX_NUMBER ")"))) {
				printInputError(lineNbr, "invalid input");
				continue;
			}

			// get total value
			try {
				float value = getValue(match[1], match[2]);
				std::cout << match[1] << " => " << match[2] << " => " << value << std::endl;
			} catch (std::exception &e) {
				printInputError(lineNbr, e.what());
			}
		}
	} catch (std::exception& e)  {
		std::cerr << e.what() << std::endl;
		return (1);
	}


}
