#pragma once

#include <wx/wx.h>
#include <vector>
#include <array>
#include <memory>
#include "ConfigClass.h"

class ConfigClass;

class MyPanel : public wxPanel {
public:
	MyPanel(wxWindow* parent);
	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void SetShape(const wxString& shape, const wxColour& borderColor, bool filled, const wxColour& fillColor);
    wxBitmap RescaleBitmap(const wxBitmap &bitmap);
    void PlayAnimation();



	friend class MainFrame;
private:
    std::shared_ptr<ConfigClass> cfg;



	bool isShapeSelected;
	int clickCount=0;
};