#pragma once

#include <wx/wx.h>
#include <vector>
#include <array>
#include "ShapeDialog.h"

class MyPanel : public wxPanel {
public:
	MyPanel(wxWindow* parent);
	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void SetShape(const wxString& shape, const wxColour& color, bool filled); 
	friend class MainFrame;
private:
	wxPoint firstPoint, secondPoint;
	std::vector<std::array<wxPoint, 2>> shapes;

	std::vector<std::vector<Shape>> _frames;
	int _framesCounter = 1;

	std::vector<Shape> _currFrame;
	int _currFramesCounter = 1;

	bool isShapeSelected;
	int clickCount=0;
};