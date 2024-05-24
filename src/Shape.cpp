//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#include "Shape.h"





void Shape::drawShape(wxDC &dc) const
{

    dc.SetBrush(wxBrush(color, filled ? wxBRUSHSTYLE_SOLID : wxBRUSHSTYLE_TRANSPARENT));
    dc.SetPen(wxPen(color));

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
        dc.DrawRectangle(firstPoint, wxSize(side, side));
    }
    else if (type == "Triangle") {
        wxPoint points[3];
        points[0] = wxPoint((firstPoint.x + secondPoint.x) / 2, firstPoint.y);
        points[1] = wxPoint(firstPoint.x, secondPoint.y);
        points[2] = wxPoint(secondPoint.x, secondPoint.y);
        dc.DrawPolygon(3, points);
    }
}