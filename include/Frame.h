#pragma once

#include "Shape.h"
#include <string>
#include <vector>
#include <memory>

/**
 * @class Frame
 * @brief Klasa reprezentująca jedną klatkę animacji.
 */
class Frame {
private:
    /**
     * @brief Ścieżka do obrazu tła.
     */
    wxString _bgPath;
    /**
     * @brief bitmapa rysowana na tle
     */
    wxBitmap _bitmap;
    /**
     * @brief Wektor kształtów zawartych w klatce.
     */
    std::vector<Shape> _shapes;

public:

    void setBitmap(const wxBitmap& bitmap){_bitmap = wxBitmap(bitmap);}
    wxBitmap getBitmap(){return _bitmap;}

    void loadBitmap()
    {
        wxString extension = _bgPath.AfterLast('.').Lower();

        wxBitmapType format = wxBITMAP_TYPE_ANY;
        if (extension == "png")
            format = wxBITMAP_TYPE_PNG;
        else if (extension == "jpg" || extension == "jpeg")
            format = wxBITMAP_TYPE_JPEG;
        else if (extension == "bmp")
            format = wxBITMAP_TYPE_BMP;
        else
            return; // Hack - when no background is present, no error will po up

        wxImage image;
        if(image.LoadFile(_bgPath, format))
        {
            _bitmap = wxBitmap(image);
        }
        else {
            wxLogError("Could not load image file '%s'.", _bgPath);
        }
    }

    /// @brief Domyślny konstruktor
    Frame() = default;

    /// @brief Konstruktor z danych
    Frame(wxString bgPath, std::vector<Shape> shapes) : _bgPath(bgPath), _shapes(shapes) {}

    /**
     * @brief Zwraca klatkę stworzoną z łańcucha reprezentującego jej parametry (oddzielone `;`).
     *
     * @param params Pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty.
     * @return Utworzona klatka.
     */
    static Frame fromString(const wxString& params);

    /// @brief Konwertuje klatkę na zapis w formie `wxString`
    wxString toString() const;

    void setBgPath(const wxString& path){_bgPath = path;}


    /// @brief getter do ścieżki tła
    const wxString& getBgPath() const { return _bgPath; }

    /// @brief getter do listy kształtów
    const std::vector<Shape>& getShapes() const { return _shapes; }

    /**
     *
     * @param shapes
     */
    void setShapes(const std::vector<Shape>& shapes) {_shapes.clear(); _shapes = shapes;} //might add move constructor;

    /**
     * @brief Dodaje Shape
     *
     * @param p1
     * @param p2
     * @param type
     * @param color
     * @param filled
     * @param fillColor
     */
    void addShape( wxPoint p1, wxPoint p2, const wxString& type, const wxColour& color, bool filled, wxColour fillColor)
    {
        _shapes.emplace_back(p1,p2,type,color,filled, fillColor);
    }

    /**
     *  Usuwa ostatnio dodany Shape
     */
    void popLastShape()
    {
        if (!_shapes.empty())
        {
            _shapes.pop_back();
        }
        else
        {
            wxBell();
        }
    }

};
