#include "Parser.h"

Parser::Parser(std::string procString) : procString_(procString), relevantSubstringsNum_(0)
{
	searchSubstrings();
}

std::ostream &Parser::printRelevantSubsrings(std::ostream &out) {
	for (size_t i = 0; i < relevantSubstringsNum_; i++) {
		out << relevantSubstrings_[i].first + 1 << ": ";
		out << procString_.substr(relevantSubstrings_[i].first, relevantSubstrings_[i].second - relevantSubstrings_[i].first + 1);
		out << std::endl;
	}
	return out;
}

size_t Parser::getRelevantSubstringsNum() {
	return relevantSubstringsNum_;
}

void Parser::searchSubstrings() {
	std::vector<size_t> stringPluses;
	size_t plusesNum = searchPluses(stringPluses);
	for (size_t i = 1; i < plusesNum; i++) {
		if (checkSubstring(stringPluses[i - 1], stringPluses[i]) == true) {
			relevantSubstrings_.push_back(std::pair<size_t, size_t>(stringPluses[i - 1], stringPluses[i]));
			relevantSubstringsNum_++;
		}
	}
}

size_t Parser::searchPluses(std::vector<size_t> &stringPluses) {
	size_t plusesCounter = 0;
	for (size_t i = 0, stringSize = procString_.length(); i < stringSize; i++)
		if (procString_[i] == '+') {
			stringPluses.push_back(i);
			plusesCounter++;
		}
	return plusesCounter;
}

bool Parser::checkSubstring(size_t firstPlus, size_t secondPlus) {
	bool prevA = false, prevB = false;
	for (size_t i = firstPlus + 1; i < secondPlus; i++) 
		switch (procString_[i]) {
		case 'a':
			if (prevA == true) return false;
			prevA = true;
			prevB = false;
			break;
		case 'b':
			if (prevB == true) return false;
			prevB = true;
			prevA = false;
			break;
		case '-':
			if (prevA == false && prevB == false) return false;
			if (procString_[i - 1] != procString_[i + 1]) return false;
			prevA = false;
			prevB = false;
			break;
		default:
			return false;
		}
	return true;
}