#include "Frame.h"
#include "Parser.h"

#include "util.h"

void Parser::readFile(std::string path) {
	std::ifstream f;
	f.open(path);
	if (!f.is_open())
		throw std::runtime_error("Couldn't open file: " + path);

	std::string line;
	while (std::getline(f, line))
		_lines.push_back(line);
}

std::vector<Frame> Parser::getFrames() const {
	std::vector<Frame> result(_lines.size());

	std::transform(_lines.begin(), _lines.end(), result.begin(), [](auto l) {
		return Frame::fromParams(getFrameParams(l));
		});

	return result;
}

std::vector<std::string> Parser::getFrameParams(std::string input) {
	return split(input, ";");
}

std::string Parser::getName(std::string input) {
	auto paren = input.begin() + input.find("(");
	return std::string(input.begin(), paren);
}

std::vector<std::string> Parser::getParams(std::string input) {
	auto lparen = input.begin() + input.find("(");
	auto rparen = input.begin() + input.find(")");
	return split(std::string(lparen + 1, rparen), ",");
}
