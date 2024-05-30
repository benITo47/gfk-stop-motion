#include "Frame.h"
#include "Parser.h"

Frame Frame::fromString(const wxString& input) {
	auto params = Parser::getFrameParams(input);
	Frame frame;
	frame._bgPath = params[0];
	std::for_each(params.begin() + 1, params.end(), [&frame](auto s) {
		frame._shapes.push_back(Shape::fromString(s));
		});

	return frame;
}

wxString Frame::toString() const {
	wxString result = _bgPath;
	for (auto& shape : _shapes)
		result += wxString::Format(";%s", shape.toString());
	return result;
}
