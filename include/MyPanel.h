#pragma once

#include <wx/wx.h>
#include <vector>
#include <array>

#include "ConfigClass.h"

class MyPanel : public wxPanel {
public:
	MyPanel(wxWindow* parent);
	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void SetShape(const wxString& shape, const wxColour& color, bool filled);
    void SetBackgroundImage(const wxString &filePath, const wxBitmap &bitmap);
    void AddFrame();

	friend class MainFrame;
private:
    std::shared_ptr<ConfigClass> cfg;


    //Frame data - primitives for drawing - set based on GUI events


	bool isShapeSelected;
	int clickCount=0;
};