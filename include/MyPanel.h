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
    void SetBackgroundImage(wxString& filePath, wxBitmap& bitmap);
    void AddFrame();

	friend class MainFrame;
private:
    std::shared_ptr<ConfigClass> cfg;


    //Frame data - primitives for drawing - set based on GUI events
    wxPoint firstPoint, secondPoint;
    wxString type;
    wxColour color;
    bool filled;


    //Background data;
    wxBitmap _backgroundBitmap;
    wxString _backgroundPath;



	std::vector<std::array<wxPoint, 2>> shapes;
    std::vector<Shape> _currFrame;


	std::vector<std::vector<Shape>> _frames;
	int _framesIterator = 0;


	int _currFrameShapesCounter = 1;
	bool isShapeSelected;
	int clickCount=0;
};