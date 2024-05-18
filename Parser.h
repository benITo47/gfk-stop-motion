#pragma once

#include "util.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

class Parser {
private:

public:
	static std::string getName(std::string input) {
		auto paren = input.begin() + input.find("(");
		return std::string(input.begin(), paren);
	}

	static std::vector<std::string> getParams(std::string input) {
		auto lparen = input.begin() + input.find("(");
		auto rparen = input.begin() + input.find(")");
		return split(std::string(lparen + 1, rparen), ",");
	}

	
};