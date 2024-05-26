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
	void SetShape(const wxString& shape, const wxColour& color, bool filled);
    void SetBackgroundImage(const wxString &filePath, const wxBitmap &bitmap);
    void PlayAnimation();

	friend class MainFrame;
private:
    std::shared_ptr<ConfigClass> cfg;


    //Frame data - primitives for drawing - set based on GUI events
	bool isShapeSelected;
	int clickCount=0;
};