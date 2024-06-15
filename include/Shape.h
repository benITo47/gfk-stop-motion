#ifndef STOP_MOTION_SHAPE_H
#define STOP_MOTION_SHAPE_H

#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/clrpicker.h>
#include <wx/graphics.h>
#include <memory>

class Shape {
public:
    /**
     * @brief Constructor for creating shape without fill colour
     * @param p1 First point
     * @param p2 Second point
     * @param type Shape type
     * @param color  Border colour
     * @param filled
     */
    Shape( wxPoint p1, wxPoint p2, const wxString& type, const wxColour& color, bool filled)
            : type(type), borderColour(color), fillColour(*wxWHITE),isFilled(filled), firstPoint(p1), secondPoint(p2) {}


    /**
     * @brief Constructor for creating shape with fill colour
     * @param p1 First point
     * @param p2 Second point
     * @param type Shape type
     * @param color Border colour
     * @param filled If true - shape will be filled with fillColor
     * @param fillColor - Fill Color of the shape
     */
    Shape( wxPoint p1, wxPoint p2, const wxString& type, const wxColour& color, bool filled, wxColour fillColor)
            : type(type), borderColour(color), fillColour(fillColor), isFilled(filled), firstPoint(p1), secondPoint(p2) {}

    /**
     * @brief Function responsible for drawing this shape on provided GraphicsContext
     * @param gc - GraphicsContext that will be drawn on
     */
    void drawShape(std::shared_ptr<wxGraphicsContext> gc) const;

    wxString type;
    wxColour borderColour;
    wxColour fillColour;
    bool isFilled;

    wxPoint firstPoint;
    wxPoint secondPoint;

    /// @brief Dokonuje konwersji napisu na obiekt klasy `Shape`
    static Shape fromString(const wxString& input);

    /// @brief Dokonuje konwersji kształtu na napis
    ///
    /// Format:
    /// 
    /// `[nazwa]([x0],[y0],[x1],[y1],[kolor_obramowania][kolor_wypełnienia])`
    wxString toString() const;
};



#endif //STOP_MOTION_SHAPE_H
