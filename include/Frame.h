#pragma once

#include "ShapeToParse.h"
#include <string>
#include <vector>
#include <memory>

/// <summary>
/// Klasa reprezentująca jedną klatkę animacji
/// </summary>
class Frame {
private:
	/// <summary>
	/// Ścieżka do obrazu tła
	/// </summary>
	std::string _bgPath;

	/// <summary>
	/// Wektor kształtów zawartych w klatce
	/// </summary>
	std::vector<std::unique_ptr<ShapeToParse>> _shapes;
public:

	/// <summary>
	/// Zwraca klatkę stworzoną z wektora łańcuchów reprezentujących jej parametry
	/// </summary>
	/// <param name="params">Wektor parametrów, pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty</param>
	/// <returns>Utworzona klatka</returns>
	static Frame fromParams(std::vector<std::string> params);
};