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

    /// @brief getter do ścieżki tła
    const wxString& getBgPath() const { return _bgPath; }

    /// @brief getter do listy kształtów
    const std::vector<Shape>& getShapes() const { return _shapes; }
};
