#pragma once

#include "Parser.h"
#include "Shape.h"
#include <string>
#include <vector>
#include <memory>

class Frame {
private:
	std::string _bgPath;
	std::vector<std::unique_ptr<ShapeToParse>> _shapes;
public:
	static Frame fromParams(std::vector<std::string> params) {
		Frame frame;
		frame._bgPath = params[0];
		std::for_each(params.begin() + 1, params.end(), [&frame](auto s) {
			frame._shapes.push_back(ShapeToParse::fromStrings(Parser::getName(s), Parser::getParams(s)));
			});
	}
};