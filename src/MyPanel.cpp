#include "MyPanel.h"

#define PANEL_HEIGHT  900
#define PANEL_WIDTH  1200

MyPanel::MyPanel(wxWindow* parent) : wxPanel(parent), cfg(std::make_shared<ConfigClass>()) {
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
	wxPaintDC dc(this);
    dc.Clear();
    wxBitmap backgroundBitmap = cfg->getBackgroundBitmap();
    if (backgroundBitmap.IsOk()) {
        dc.DrawBitmap(backgroundBitmap, 0, 0, false);
    }

    for (const auto& shape : cfg->getCurrentFrame()) {
        shape.drawShape(dc);
    }

}

void MyPanel::SetShape(const wxString& shape, const wxColour& col, bool fill) {

    cfg->setType(shape);
    cfg->setBorderColour(col);
    cfg->setIsFilled(fill);
    isShapeSelected = true;
    clickCount = 0;
}

void MyPanel::SetBackgroundImage(const wxString &filePath, const wxBitmap &bitmap)
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
    wxBitmap bitmapFinal(image);
    cfg->setBackgroundBitmap(bitmapFinal);
    cfg->setBackgroundPath(filePath);

    Refresh();
}

void MyPanel::PlayAnimation()
{
    int frames = cfg->getFrameNumber();
    for(int i = 0; i < frames; i++)
    {
        cfg->setFrameIterator(i);
        Refresh();
        wxMilliSleep(100); // Sleep for 100 milliseconds (0.1 seconds)
        wxYield();
    }
}

