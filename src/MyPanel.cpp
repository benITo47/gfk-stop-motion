#include "MyPanel.h"

#include <wx/dcbuffer.h>

#define PANEL_HEIGHT  900
#define PANEL_WIDTH  1200

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent), _cfg(std::make_shared<ConfigClass>()) {
    this->SetInitialSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMaxSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMinSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));

    SetBackgroundStyle(wxBG_STYLE_PAINT);

	Bind(wxEVT_PAINT, &MyPanel::onPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::onLeftDown, this);
}

void MyPanel::onLeftDown(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    if (_clickCount == 0) {
        _cfg->setPoint1(pos);
        _clickCount++;
        //
        std::cout << "x1:  " << pos.x << "   y1:  " << pos.y << std::endl;
        //
    }
    else if (_clickCount == 1) {
        //
        std::cout << "x2:  " << pos.x << "   y2:  " << pos.y << std::endl;
        //
        _cfg->setPoint2(pos);
        _cfg->saveShape();
        _clickCount = 0;
        Refresh();
    }
}

void MyPanel::onPaint(wxPaintEvent& event) {
    //wxPaintDC dc(this);
    wxBufferedPaintDC dc(this);
    dc.Clear();

    // Draw the background bitmap
    wxBitmap backgroundBitmap = _cfg->getBackgroundBitmap();
    if (backgroundBitmap.IsOk()) {
        dc.DrawBitmap(backgroundBitmap, 0, 0, false);
    }

    // Draw the middle bitmap
    wxBitmap middleBitmap = _cfg->getMiddleBitmap();
    if (middleBitmap.IsOk()) {
        dc.DrawBitmap(middleBitmap, 0, 0, true);
    }

    // Draw the current bitmap
    wxBitmap currentBitmap = _cfg->getCurrentBitmap();
    if (currentBitmap.IsOk()) {
        dc.DrawBitmap(currentBitmap, 0, 0, true);
    }
}

void MyPanel::setShape(const wxString& shape, const wxColour& borderColor, bool filled, const wxColour& fillColor) {
    _cfg->setType(shape);
    _cfg->setBorderColour(borderColor);
    _cfg->setIsFilled(filled);
    _cfg->setFillColour(fillColor);
    _clickCount = 0;
}

void MyPanel::playAnimation() {
    int frames = _cfg->getFrameNumber();
    auto opacityLevel = _cfg->getOpacity();
    _cfg->setOpacity(0);
    for(int i = 0; i < frames; i++)
    {
        _cfg->setFrameIterator(i);
        _cfg->prepareBitmaps();
        Refresh();
        wxMilliSleep(100); // Sleep for 100 milliseconds (0.1 seconds)
        wxYield();
    }
    _cfg->setOpacity(opacityLevel);
}

