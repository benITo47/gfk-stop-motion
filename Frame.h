#pragma once

#include "Shape.h"
#include <string>
#include <vector>
#include <memory>

class Frame {
private:
	std::string _bgPath;
	std::vector<std::unique_ptr<ShapeToParse>> _shapes;
public:
	static Frame fromParams(std::vector<std::string> params);
};