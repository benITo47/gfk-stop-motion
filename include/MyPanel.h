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
	void onPaint(wxPaintEvent& event);
    void onMotion(wxMouseEvent& event);
	void onLeftDown(wxMouseEvent& event);
	void setShape(const wxString& shape, const wxColour& borderColor, bool filled, const wxColour& fillColor);
    void playAnimation();


	friend class MainFrame;
private:
    std::shared_ptr<ConfigClass> _cfg;

	std::atomic<bool> stopFlag = false;
	std::atomic<bool> prevAnimation = false;
	std::atomic<bool> endAnimation = false;
	int _clickCount=0;
};