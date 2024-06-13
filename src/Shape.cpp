#include "Shape.h"

#include "Parser.h"

#include <wx/graphics.h>
#include <memory>


void Shape::drawShape(std::shared_ptr<wxGraphicsContext> gc) const
{
    gc->SetBrush(gc->CreateBrush(wxBrush(fillColour, isFilled ? wxBRUSHSTYLE_SOLID : wxBRUSHSTYLE_TRANSPARENT)));
    gc->SetPen(gc->CreatePen(wxPen(borderColour)));

    if (type == "Line") {
        gc->StrokeLine(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
    }
    else if (type == "Polyline") {
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(firstPoint.x, firstPoint.y);
        path.AddLineToPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y);
        path.AddLineToPoint((firstPoint.x + secondPoint.x) / 2, secondPoint.y);
        path.AddLineToPoint(secondPoint.x, secondPoint.y);
        gc->StrokePath(path);
    }
    else if (type == "Curve") {
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(firstPoint.x, firstPoint.y);
        path.AddQuadCurveToPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y, secondPoint.x, secondPoint.y);
        gc->StrokePath(path);
    }
    else if (type == "Circle") {
        int radius = sqrt(pow(secondPoint.x - firstPoint.x, 2) + pow(secondPoint.y - firstPoint.y, 2));
        gc->DrawEllipse(firstPoint.x - radius, firstPoint.y - radius, radius * 2, radius * 2);
    }
    else if (type == "Ellipse") {
        double w = abs(secondPoint.x - firstPoint.x) * 2;
        double h = abs(secondPoint.y - firstPoint.y) * 2;
        gc->DrawEllipse(firstPoint.x - w / 2, firstPoint.y - h / 2, w, h);
    }
    else if (type == "Square") {
        int side = wxMin(abs(secondPoint.x - firstPoint.x), abs(secondPoint.y - firstPoint.y));
        int topLeftX = firstPoint.x;
        int topLeftY = firstPoint.y;
        if (secondPoint.x < firstPoint.x) {
            topLeftX = firstPoint.x - side;
        }
        if (secondPoint.y < firstPoint.y) {
            topLeftY = firstPoint.y - side;
        }
        gc->DrawRectangle(topLeftX, topLeftY, side, side);
    }
    else if (type == "Triangle") {
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(firstPoint.x, firstPoint.y);  // Peak of the triangle
        path.AddLineToPoint(secondPoint.x, secondPoint.y); // Base point at secondPoint
        path.AddLineToPoint(2 * firstPoint.x - secondPoint.x, secondPoint.y); // Base point opposite to secondPoint
        path.CloseSubpath();
        gc->FillPath(path);
        gc->StrokePath(path);
    }
}


Shape Shape::fromString(const wxString& input) {
	auto name = Parser::getName(input);
	auto params = Parser::getParams(input);

	if (params.size() < 6)
		throw std::runtime_error("Invalid input string for shape creation");

	bool result = true;

	int aX, aY, bX, bY;
	result = (result && params[0].ToInt(&aX));
	result = (result && params[1].ToInt(&aY));
	result = (result && params[2].ToInt(&bX));
	result = (result && params[3].ToInt(&bY));

	if (!result)
		throw std::runtime_error("Couldn't parse `int` value for shape creation");

	wxColour outlineColour;

	wxUint32 outlineColourRGB;
	result = (result && params[4].ToUInt(&outlineColourRGB));
	if (!result)
		throw std::runtime_error("Couldn't parse `wxUint32` value for shape creation");
	outlineColour.SetRGB(outlineColourRGB);

	if (params[5] == "-")
		return Shape(wxPoint(aX, aY), wxPoint(bX, bY), wxString(name), outlineColour, false);

	wxColour fillColour;
	wxUint32 fillColourRGB;
	result = (result && params[5].ToUInt(&fillColourRGB));
	if (!result)
		throw std::runtime_error("Couldn't parse `wxUint32` value for shape creation");
	fillColour.SetRGB(fillColourRGB);

	return Shape(wxPoint(aX, aY), wxPoint(bX, bY), wxString(name), outlineColour, true, fillColour);
}

wxString Shape::toString() const {
	return wxString::Format("%s(%d,%d,%d,%d,%u,%s)",
		type,
		firstPoint.x,
		firstPoint.y,
		secondPoint.x,
		secondPoint.y,
		borderColour.GetRGB(),
		isFilled ? wxString::Format("%u", fillColour.GetRGB()) : wxString("-")
	);
}
