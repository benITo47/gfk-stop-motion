#include "../include/Parser.h"
#include "../include/Frame.h"

Frame Frame::fromParams(std::vector<std::string> params) {
	Frame frame;
	frame._bgPath = params[0];
	std::for_each(params.begin() + 1, params.end(), [&frame](auto s) {
		frame._shapes.push_back(ShapeToParse::fromStrings(Parser::getName(s), Parser::getParams(s)));
		});

	return frame;
}
