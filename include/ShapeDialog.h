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

