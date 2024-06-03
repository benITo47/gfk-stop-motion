#include "MyPanel.h"

#include <wx/dcbuffer.h>

#define PANEL_HEIGHT  900
#define PANEL_WIDTH  1200

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent), cfg(std::make_shared<ConfigClass>()) {
    this->SetInitialSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMaxSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMinSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));

    SetBackgroundStyle(wxBG_STYLE_PAINT);

	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::OnLeftDown, this);
}

void MyPanel::OnLeftDown(wxMouseEvent& event) {
    if (isShapeSelected) {
        wxPoint pos = event.GetPosition();
        if (clickCount == 0) {
            cfg->setPoint1(pos);
            clickCount++;
            //
            std::cout << "x1:  " << pos.x << "   y1:  " << pos.y << std::endl;
            //
        }
        else if (clickCount == 1) {
            //
            std::cout << "x2:  " << pos.x << "   y2:  " << pos.y << std::endl;
            //
            cfg->setPoint2(pos);
            cfg->saveShape();
            clickCount = 0;
            Refresh();
        }
    }
}


void MyPanel::OnPaint(wxPaintEvent& event) {
    //wxPaintDC dc(this);
    wxBufferedPaintDC dc(this);
    dc.Clear();

    // Draw the background bitmap
    wxBitmap backgroundBitmap = cfg->getBackgroundBitmap();
    if (backgroundBitmap.IsOk()) {
        dc.DrawBitmap(backgroundBitmap, 0, 0, false);
    }

    // Draw the middle bitmap
    wxBitmap middleBitmap = cfg->getMiddleBitmap();
    if (middleBitmap.IsOk()) {
        dc.DrawBitmap(middleBitmap, 0, 0, true);
    }

    // Draw the current bitmap
    wxBitmap currentBitmap = cfg->getCurrentBitmap();
    if (currentBitmap.IsOk()) {
        dc.DrawBitmap(currentBitmap, 0, 0, true);
    }
}


void MyPanel::SetShape(const wxString& shape, const wxColour& borderColor, bool filled, const wxColour& fillColor) {

    cfg->setType(shape);
    cfg->setBorderColour(borderColor);
    cfg->setIsFilled(filled);
    cfg->setFillColour(fillColor);
    isShapeSelected = true;
    clickCount = 0;
}
/*
wxBitmap MyPanel::RescaleBitmap(const wxBitmap &bitmap)
{
    int bitmapWidth = bitmap.GetWidth();
    int bitmapHeight = bitmap.GetHeight();

    double bitmapAspectRatio = static_cast<double>(bitmapWidth) / bitmapHeight;
    double panelAspectRatio = static_cast<double>(PANEL_WIDTH) / PANEL_HEIGHT;

    if (bitmapAspectRatio > panelAspectRatio) {
        // Image is wider relative to the panel
        bitmapWidth = PANEL_WIDTH;
        bitmapHeight = static_cast<int>(PANEL_WIDTH / bitmapAspectRatio);
    } else {
        // Image is taller relative to the panel
        bitmapHeight = PANEL_HEIGHT;
        bitmapWidth = static_cast<int>(PANEL_HEIGHT * bitmapAspectRatio);
    }


    wxImage image = bitmap.ConvertToImage();
    image.Rescale(bitmapWidth, bitmapHeight, wxIMAGE_QUALITY_HIGH);
    return  wxBitmap(image);
}
*/

void MyPanel::PlayAnimation()
{
    int frames = cfg->getFrameNumber();
    auto opacityLevel = cfg->getOpacity();
    cfg->setOpacity(0);
    for(int i = 0; i < frames; i++)
    {
        cfg->setFrameIterator(i);
        cfg->prepareBitmaps();
        Refresh();
        wxMilliSleep(100); // Sleep for 100 milliseconds (0.1 seconds)
        wxYield();
    }
    cfg->setOpacity(opacityLevel);
}

