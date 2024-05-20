#include "../include/Shape.h"

std::unique_ptr<ShapeToParse> ShapeToParse::fromStrings(std::string name, std::vector<std::string> params) {
	if (name == "circle") {
		return Circle::fromParams(params);
	}
	else {
		throw std::runtime_error("Invalid shape name");
	}
}
