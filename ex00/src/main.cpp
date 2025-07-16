#include "../inc/Date.hpp"
#include "../inc/BtcConverter.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>

#define CSV_PATH "data.csv"


void printInputError(size_t lineNbr, const std::string& str) {
	std::cerr << "Error in line: " << lineNbr << ": " << str << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr <<"Usage: ./btc <pathToInputFile>" << std::endl;
		return 1;
	}
	
	try {
		BtcConverter converter(CSV_PATH);

		std::ifstream	inputFile(argv[1]);
		if (inputFile.fail()) {
			std::cerr << "Could not open input file: " << strerror(errno) << std::endl;
			return 1;
		}

		std::string line;
		for (size_t lineNbr = 0; std::getline(inputFile, line); ++lineNbr) {
			if (line == "date | value" && lineNbr == 0) { continue; }

			std::smatch match;
			if (std::regex_match(line, match, std::regex("(" REGEX_DATE ") \\| (" REGEX_NUMBER ")"))) {
				try {
					Date date(match[1]);
					float btcAmount = std::stof(match[2]);
					if (btcAmount < 0) {
						printInputError(lineNbr, "negative value");
						continue;
					} else if (btcAmount > 1000) {
						printInputError(lineNbr, "value > 1000");
						continue;
					}
					std::optional<float> convertedValue = converter.getValue(date.getDate(), btcAmount);
					if (!convertedValue.has_value()) {
						printInputError(lineNbr, "date past last database date");
						continue;
					}
					std::cout << match[1] << " => " << btcAmount << " => " << convertedValue.value() << std::endl;
				} catch (std::exception &e) {
					printInputError(lineNbr, e.what());
				}
		
			} else {
				printInputError(lineNbr, "invalid input");
			}
		
		}
	} catch (std::exception& e)  {
		std::cerr << e.what() << std::endl;
		return (1);
	}


}

// TODO:open csv file and parse csv file into a map
// TODO:check validity of input line
