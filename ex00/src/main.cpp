#include "../inc/Date.hpp"
#include <iostream>

int main(void) {
	while (true) {
		std::string input;
		std::cout << "Date: ";
		std::cin >> input;
		if (input == "exit") {
			break;
		}
		try {
			Date date(input);
			while (true) {
				std::cout << "Advance date? (y/n): ";
				std::cin >> input;
				if (input == "y") {
					date.advanceDate();
					std::cout << "New date: " << date << std::endl;
				} else {
					break;
				}
			}
		} catch (const std::invalid_argument& e) {
			std::cout << "Invalid date format: " << e.what() << std::endl;
		}


	}


}
