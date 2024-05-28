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
    std::string _bgPath;

    /**
     * @brief Wektor kształtów zawartych w klatce.
     */
    std::vector<Shape> _shapes;

public:
    /**
     * @brief Zwraca klatkę stworzoną z wektora łańcuchów reprezentujących jej parametry.
     *
     * @param params Wektor parametrów, pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty.
     * @return Utworzona klatka.
     */
    static Frame fromParams(std::vector<wxString> params);
};
