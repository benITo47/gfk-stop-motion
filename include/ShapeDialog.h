#pragma once

#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/clrpicker.h>

class ShapeDialog : public wxDialog {
public:
    ShapeDialog(wxWindow* parent);

    wxString GetSelectedShape() const;
    wxColour GetSelectedColor() const;
    bool IsFilled() const;

private:
    wxChoice* shapeChoice;
    wxColourPickerCtrl* colorPicker;
    wxCheckBox* fillCheckBox;

};

class Shape {
public:
    Shape(const wxString& type, const wxColour& color, bool filled, wxPoint& p1, wxPoint& p2)
            : type(type), color(color), filled(filled), firstPoint(p1), secondPoint(p2) {}


    void drawShape(wxDC& dc)const ;

    wxString type;
    wxColour color;
    bool filled;

    wxPoint firstPoint;
    wxPoint secondPoint;
};


