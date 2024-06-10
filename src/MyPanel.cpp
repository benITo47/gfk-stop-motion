#include "MyPanel.h"

#include <wx/dcbuffer.h>

#define PANEL_HEIGHT  900
#define PANEL_WIDTH  1200
#define MIN_SPEED_ANIMATION 201

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent), _cfg(std::make_shared<ConfigClass>()) {
    this->SetInitialSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMaxSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMinSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));

    SetBackgroundStyle(wxBG_STYLE_PAINT);

	Bind(wxEVT_PAINT, &MyPanel::onPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::onLeftDown, this);
    Bind(wxEVT_MOTION, &MyPanel::onMotion, this);
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

void MyPanel::onMotion(wxMouseEvent& event)
{
    if (_clickCount == 1)
    {
        wxPoint currentPoint = event.GetPosition();
        _cfg->setPoint2(currentPoint); // Update the current end point of the shape
        Refresh(); // Trigger a repaint to show the updated shape
    }
}

void MyPanel::onPaint(wxPaintEvent& event) {
    wxBufferedPaintDC dc(this);
    dc.Clear();
    wxBitmap currentBitmap = _cfg->getCurrentBitmap();
    wxBitmap middleBitmap = _cfg->getMiddleBitmap();
    wxBitmap backgroundBitmap = _cfg->getBackgroundBitmap();
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    if (gc)
    {
        // Check if background bitmap is valid before drawing
        if (backgroundBitmap.IsOk()) {
            wxGraphicsBitmap background = gc->CreateBitmap(backgroundBitmap);
            gc->DrawBitmap(background, 0, 0, backgroundBitmap.GetWidth(), backgroundBitmap.GetHeight());
        }

        // Check if middle bitmap is valid before drawing
        if (middleBitmap.IsOk()) {
            wxGraphicsBitmap middle = gc->CreateBitmap(middleBitmap);
            gc->DrawBitmap(middle, 0, 0, middleBitmap.GetWidth(), middleBitmap.GetHeight());
        }

        // Check if current bitmap is valid before drawing
        if (currentBitmap.IsOk()) {
            wxGraphicsBitmap current = gc->CreateBitmap(currentBitmap);
            gc->DrawBitmap(current, 0, 0, currentBitmap.GetWidth(), currentBitmap.GetHeight());
        }

        if(_clickCount == 1){
        Shape currentShape(_cfg->getPoint1(), _cfg->getPoint2(),_cfg->getType(), _cfg->getBorderColour(), _cfg->getIsFilled(), _cfg->getFillColour());
        currentShape.drawShape(gc);
        }
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
    int i = prevAnimation ? _cfg->getFrameIterator() : 0;
    int speedAnimation = _cfg->getSpeedAnimation();
    for( ; i < frames && !stopFlag; i++)
    {
        _cfg->setFrameIterator(i);
        _cfg->prepareBitmaps();
        Refresh();
        wxMilliSleep(MIN_SPEED_ANIMATION - speedAnimation); // Sleep for 100 milliseconds (0.1 seconds)
        wxYield();
    }
    prevAnimation = stopFlag ? true : false;
    endAnimation = true;
    _cfg->setOpacity(opacityLevel);
}

