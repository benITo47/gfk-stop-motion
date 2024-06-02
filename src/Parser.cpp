#include "Frame.h"
#include "Parser.h"

#include "util.h"

void Parser::readFile(const wxString& path) {
	_path = path;

	std::ifstream f;
	f.open(path.ToStdString());
	if (!f.is_open())
		throw std::runtime_error("Couldn't open file: " + path);

	std::string line;
	while (std::getline(f, line))
		_lines.push_back(line);
}

void Parser::setFrames(const std::vector<Frame> frames) {
	_lines.clear();
	for (auto& frame : frames)
		_lines.push_back(frame.toString());
}

void Parser::saveToFile(const wxString& path) const {
	std::ofstream f;
	f.open(path.ToStdString());
	for (auto& line : _lines)
		f << line << "\n";
}

std::vector<Frame> Parser::getFrames() const {
	std::vector<Frame> result(_lines.size());

	std::transform(_lines.begin(), _lines.end(), result.begin(), [this](auto l) {
		return Frame::fromString(_path.BeforeLast('\\') + "\\img\\" + l);
		});

	return result;
}

std::vector<wxString> Parser::getFrameParams(const wxString& input) {
	return split(input, ";");
}

std::string Parser::getName(const wxString& input) {
	auto paren = input.begin() + input.find("(");
	return std::string(input.begin(), paren);
}

std::vector<wxString> Parser::getParams(const wxString& input) {
	auto lparen = input.begin() + input.find("(");
	auto rparen = input.begin() + input.find(")");
	return split(std::string(lparen + 1, rparen), ",");
}
