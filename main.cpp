#include <iostream>
#include <string>
#include "Parser.h"

int main() {
	std::string procString = "";
	std::cout << "Enter string:" << std::endl;
	std::getline(std::cin, procString);
	Parser parser(procString);
	std::cout << "Found " << parser.getRelevantSubstringsNum() << " relevant substrings" << std::endl;
	parser.printRelevantSubsrings();
	system("pause");
	return 0;
}