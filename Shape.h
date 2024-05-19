#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <wx/wx.h>
#include <format>

/// <summary>
/// Przykładowa klasa bazowa dla kształtu z funckjonalnością parsowania
/// </summary>
/// 
/// Dany kształt musi:
/// - być dodany do funkcji `ShapeToParse::fromStrings`
/// - posiadać funkcję konwertującą do `std::string` - 
class ShapeToParse {
public:
	/// <summary>
	/// Zwraca kształt opisany przez podane parametry
	/// </summary>
	/// <param name="name">Nazwa kształtu</param>
	/// <param name="params">Parametry kształtu</param>
	/// <returns>`std::unique_ptr` do kształtu (wymagane by uniknąć bezpośredniego użycia wskaźników)</returns>
	static std::unique_ptr<ShapeToParse> fromStrings(std::string name, std::vector<std::string> params);

	/// <summary>
	/// Funkcja konwertująca kształt do `std::string` - czysto wirtualna
	/// </summary>
	virtual operator std::string() const = 0;
};

// Przy dodawaniu koloru proponuje zapisywac go jako rgb w hex - ulatwi to zapis do pliku
class Circle : public ShapeToParse {
private:
	double _x0, _y0, _r;
public:
	Circle(double x0, double y0, double r) : _x0(x0), _y0(y0), _r(r) {}

	static std::unique_ptr<Circle> fromParams(std::vector<std::string> params) {
		if (params.size() < 3)
			throw std::runtime_error("Too few parameters for parsing circle");

		return std::make_unique<Circle>(stof(params[0]), stof(params[1]), stof(params[2]));
	}

	operator std::string() const {
		return std::format("circle({},{},{})", _x0, _y0, _r);
	}
};