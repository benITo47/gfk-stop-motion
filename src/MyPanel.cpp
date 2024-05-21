#include "../include/MyPanel.h"

#define PANEL_HEIGHT  900
#define  PANEL_WIDTH  1200

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent) {
    this->SetInitialSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMaxSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
    this->SetMinSize(wxSize(PANEL_WIDTH,PANEL_HEIGHT));
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::OnLeftDown, this);
}

void MyPanel::OnLeftDown(wxMouseEvent& event) {
    if (isShapeSelected) {
        wxPoint pos = event.GetPosition();
        if (clickCount == 0) {
            firstPoint = pos;
            clickCount++;
            std::cout << "x1:  " << pos.x << "   y1:  " << pos.y << std::endl;
        }
        else if (clickCount == 1) {
            secondPoint = pos;
            shapes.push_back({ firstPoint, secondPoint });
            std::cout << "x2:  " << pos.x << "   y2:  " << pos.y << std::endl;
            Refresh(); 
            clickCount = 0;
            _currFrame.emplace_back(type,color,filled,firstPoint,secondPoint);
            _currFrameShapesCounter++;
        }
    }
}

void MyPanel::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
    dc.Clear();

    if (_backgroundBitmap.IsOk()) {
        dc.DrawBitmap(_backgroundBitmap, 0, 0, false);
    }




    for (const auto& el : _currFrame) {

        el.drawShape(dc);
    }
}

void MyPanel::SetShape(const wxString& shape, const wxColour& col, bool fill) {

    type = shape;
    color = col;
    filled = fill;

    isShapeSelected = true;
    clickCount = 0;
}

void MyPanel::SetBackgroundImage(wxString &shape, wxBitmap &bitmap)
{

    int bitmapWidth = bitmap.GetWidth();
    int bitmapHeight = bitmap.GetHeight();

    double bitmapAspectRatio = static_cast<double>(bitmapWidth) / bitmapHeight;
    double panelAspectRatio = static_cast<double>(PANEL_WIDTH) / PANEL_HEIGHT;

    if (bitmapWidth > PANEL_WIDTH || bitmapHeight > PANEL_HEIGHT) {
        // Scale down
        if (panelAspectRatio > 1) {
            bitmapWidth = PANEL_WIDTH;
            bitmapHeight = static_cast<int>(PANEL_WIDTH / bitmapAspectRatio);
        } else {
            bitmapHeight = PANEL_HEIGHT;
            bitmapWidth = static_cast<int>(PANEL_HEIGHT * bitmapAspectRatio);
        }
    } else {
        // Scale up
        if (bitmapAspectRatio > panelAspectRatio) {
            bitmapWidth = PANEL_WIDTH;
            bitmapHeight = static_cast<int>(PANEL_WIDTH / bitmapAspectRatio);
        } else {
            bitmapHeight = PANEL_HEIGHT;
            bitmapWidth = static_cast<int>(PANEL_HEIGHT * bitmapAspectRatio);
        }
    }



    wxImage image = bitmap.ConvertToImage();
    image.Rescale(bitmapWidth, bitmapHeight);
    _backgroundBitmap = wxBitmap(image);

    Refresh();
}

