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
    Shape(const wxString& type, const wxColour& color, bool filled)
        : type(type), color(color), filled(filled) {}
    
    wxString type;
    wxColour color;
    bool filled; 
};