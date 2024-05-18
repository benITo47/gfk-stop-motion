#pragma once

#include "util.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <fstream>

class Parser {
private:
	std::vector<std::string> _lines;
public:
	void readFile(std::string path) {
		std::ifstream f;
		f.open(path);
		if (!f.is_open())
			throw std::runtime_error("Couldn't open file: " + path);

		std::string line;
		while (std::getline(f, line))
			_lines.push_back(line);
	}


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