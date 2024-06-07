//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#ifndef STOP_MOTION_SHAPE_H
#define STOP_MOTION_SHAPE_H

#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/clrpicker.h>
#include <wx/graphics.h>
#include <memory>

class Shape {
public:
    Shape( wxPoint p1, wxPoint p2, const wxString& type, const wxColour& color, bool filled)
            : type(type), borderColour(color), fillColour(*wxWHITE),isFilled(filled), firstPoint(p1), secondPoint(p2) {}


    Shape( wxPoint p1, wxPoint p2, const wxString& type, const wxColour& color, bool filled, wxColour fillColor)
            : type(type), borderColour(color), fillColour(fillColor), isFilled(filled), firstPoint(p1), secondPoint(p2) {}


    void drawShape(std::shared_ptr<wxGraphicsContext> gc) const;

    wxString type;
    wxColour borderColour;
    wxColour fillColour;
    bool isFilled;

    wxPoint firstPoint;
    wxPoint secondPoint;


    static Shape fromString(const wxString& input);

    wxString toString() const;
};



#endif //STOP_MOTION_SHAPE_H
