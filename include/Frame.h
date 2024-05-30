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
     * @brief Wektor kształtów zawartych w klatce.
     */
    std::vector<Shape> _shapes;

public:
    Frame() = default;

    Frame(wxString bgPath, std::vector<Shape> shapes) : _bgPath(bgPath), _shapes(shapes) {}

    /**
     * @brief Zwraca klatkę stworzoną z łańcucha reprezentującego jej parametry (oddzielone `;`).
     *
     * @param params Pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty.
     * @return Utworzona klatka.
     */
    static Frame fromString(const wxString& params);

    wxString toString() const;

    const wxString& getBgPath() const { return _bgPath; }

    const std::vector<Shape>& getShapes() const { return _shapes; }
};
