#include "MyPanel.h"

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent) {
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::OnLeftDown, this);
}

void MyPanel::OnLeftDown(wxMouseEvent& event) {
    if (isShapeSelected) {
        wxPoint pos = event.GetPosition();
        if (clickCount == 0) {
            firstPoint = pos;
            clickCount++;
        }
        else if (clickCount == 1) {
            secondPoint = pos;
            shapes.push_back({ firstPoint, secondPoint });
            Refresh(); 
            clickCount = 0; 
            isShapeSelected = false;
        }
    }
}

void MyPanel::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
    int i = 0;
    for (const auto& el : _currFrame) {
        dc.SetBrush(wxBrush(el.color, el.filled ? wxBRUSHSTYLE_SOLID : wxBRUSHSTYLE_TRANSPARENT));
        dc.SetPen(wxPen(el.color));

        if (el.type == "Line") {
            dc.DrawLine(shapes[i].at(0), shapes[i].at(1));
        }
        else if (el.type == "Polyline") {
            wxPoint points[4];
            points[0] = shapes[i].at(0);
            points[1] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[2] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(1).y);
            points[3] = shapes[i].at(1);
            dc.DrawLines(4, points);
        }
        else if (el.type == "Curve") {
            wxPoint points[3];
            points[0] = shapes[i].at(0);
            points[1] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[2] = shapes[i].at(1);
            dc.DrawSpline(3, points);
        }
        else if (el.type == "Circle") {
            int radius = wxMin(abs(shapes[i].at(1).x - shapes[i].at(0).x), abs(shapes[i].at(1).y - shapes[i].at(0).y)) / 2;
            dc.DrawCircle((shapes[i].at(0).x + shapes[i].at(1).x) / 2, (shapes[i].at(0).y + shapes[i].at(1).y) / 2, radius);
        }
        else if (el.type == "Ellipse") {
            dc.DrawEllipse(wxRect(shapes[i].at(0), shapes[i].at(1)));
        }
        else if (el.type == "Square") {
            int side = wxMin(abs(shapes[i].at(1).x - shapes[i].at(0).x), abs(shapes[i].at(1).y - shapes[i].at(0).y));
            dc.DrawRectangle(shapes[i].at(0), wxSize(side, side));
        }
        else if (el.type == "Triangle") {
            wxPoint points[3];
            points[0] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[1] = wxPoint(shapes[i].at(0).x, shapes[i].at(1).y);
            points[2] = wxPoint(shapes[i].at(1).x, shapes[i].at(1).y);
            dc.DrawPolygon(3, points);
        }
        i++;
    }
}

void MyPanel::SetShape(const wxString& shape, const wxColour& color, bool filled) {
    _currFrame.push_back(Shape(shape, color, filled));
    isShapeSelected = true;
    clickCount = 0;
}