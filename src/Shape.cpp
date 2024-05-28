//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#include "Shape.h"

#include "Parser.h"



void Shape::drawShape(wxDC& dc) const
{
	//wxMessageBox(toString());
	dc.SetBrush(wxBrush(fillColour, isFilled ? wxBRUSHSTYLE_SOLID : wxBRUSHSTYLE_TRANSPARENT));
	dc.SetPen(wxPen(borderColour));

	if (type == "Line") {
		dc.DrawLine(firstPoint, secondPoint);
	}
	else if (type == "Polyline") {
		wxPoint points[4];
		points[0] = firstPoint;
		points[1] = wxPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y);
		points[2] = wxPoint((firstPoint.x + secondPoint.x) / 2, secondPoint.y);
		points[3] = secondPoint;
		dc.DrawLines(4, points);
	}
	else if (type == "Curve") {
		wxPoint points[3];
		points[0] = firstPoint;
		points[1] = wxPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y);
		points[2] = secondPoint;
		dc.DrawSpline(3, points);
	}
	else if (type == "Circle") {
		int radius = wxMin(abs(secondPoint.x - firstPoint.x), abs(secondPoint.y - firstPoint.y)) / 2;
		dc.DrawCircle((firstPoint.x + secondPoint.x) / 2, (firstPoint.y + secondPoint.y) / 2, radius);
	}
	else if (type == "Ellipse") {
		dc.DrawEllipse(wxRect(firstPoint, secondPoint));
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

		dc.DrawRectangle(wxPoint(topLeftX, topLeftY), wxSize(side, side));
	}
	else if (type == "Triangle") {
		wxPoint points[3];
		points[0] = wxPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y);
		points[1] = wxPoint(firstPoint.x, secondPoint.y);
		points[2] = wxPoint(secondPoint.x, secondPoint.y);
		dc.DrawPolygon(3, points);
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
