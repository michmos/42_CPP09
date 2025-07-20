
#include "../inc/RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
		return 1;
	}

	RPN rpn;
	try {
		float result = rpn(argv[1]);
		std::cout << "Result: " << result << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

