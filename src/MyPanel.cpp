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
            isShapeSelected = false;
        }
    }
}

void MyPanel::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
    dc.Clear();

    if (_backgroundBitmap.IsOk()) {
        dc.DrawBitmap(_backgroundBitmap, 0, 0, false);
    }

    int i = 0;
    for (const auto& el : _currFrame) {
        dc.SetBrush(wxBrush(el.color, el.filled ? wxBRUSHSTYLE_SOLID : wxBRUSHSTYLE_TRANSPARENT));
        dc.SetPen(wxPen(el.color));

        if (el.type == "Line") {
            dc.DrawLine(shapes[i].at(0), shapes[i].at(1));
        }
        else if (el.type == "Polyline") {
            wxPoint points[4];
            points[0] = shapes[i].at(0);
            points[1] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[2] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(1).y);
            points[3] = shapes[i].at(1);
            dc.DrawLines(4, points);
        }
        else if (el.type == "Curve") {
            wxPoint points[3];
            points[0] = shapes[i].at(0);
            points[1] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[2] = shapes[i].at(1);
            dc.DrawSpline(3, points);
        }
        else if (el.type == "Circle") {
            int radius = wxMin(abs(shapes[i].at(1).x - shapes[i].at(0).x), abs(shapes[i].at(1).y - shapes[i].at(0).y)) / 2;
            dc.DrawCircle((shapes[i].at(0).x + shapes[i].at(1).x) / 2, (shapes[i].at(0).y + shapes[i].at(1).y) / 2, radius);
        }
        else if (el.type == "Ellipse") {
            dc.DrawEllipse(wxRect(shapes[i].at(0), shapes[i].at(1)));
        }
        else if (el.type == "Square") {
            int side = wxMin(abs(shapes[i].at(1).x - shapes[i].at(0).x), abs(shapes[i].at(1).y - shapes[i].at(0).y));
            dc.DrawRectangle(shapes[i].at(0), wxSize(side, side));
        }
        else if (el.type == "Triangle") {
            wxPoint points[3];
            points[0] = wxPoint((shapes[i].at(0).x + shapes[i].at(1).x) / 2, shapes[i].at(0).y);
            points[1] = wxPoint(shapes[i].at(0).x, shapes[i].at(1).y);
            points[2] = wxPoint(shapes[i].at(1).x, shapes[i].at(1).y);
            dc.DrawPolygon(3, points);
        }
        i++;
    }
}

void MyPanel::SetShape(const wxString& shape, const wxColour& color, bool filled) {
    _currFrame.emplace_back(shape, color, filled);
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

