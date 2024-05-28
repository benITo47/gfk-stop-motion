#include "Frame.h"

Frame Frame::fromParams(std::vector<wxString> params) {
	Frame frame;
	frame._bgPath = params[0];
	std::for_each(params.begin() + 1, params.end(), [&frame](auto s) {
		frame._shapes.push_back(Shape::fromString(s));
		});

	return frame;
}
