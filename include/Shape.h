//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#ifndef STOP_MOTION_SHAPE_H
#define STOP_MOTION_SHAPE_H

#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/clrpicker.h>

class Shape {
public:
    Shape(const wxString& type, const wxColour& color, bool filled, wxPoint& p1, wxPoint& p2)
            : type(type), color(color), fillColour(*wxWHITE),filled(filled), firstPoint(p1), secondPoint(p2) {}


    Shape(const wxString& type, const wxColour& color, bool filled, wxColour fillColor, wxPoint& p1, wxPoint& p2)
            : type(type), color(color), fillColour(fillColor), filled(filled), firstPoint(p1), secondPoint(p2) {}


    void drawShape(wxDC& dc)const ;

    wxString type;
    wxColour color;
    wxColour fillColour;
    bool filled;


    wxPoint firstPoint;
    wxPoint secondPoint;
};



#endif //STOP_MOTION_SHAPE_H
