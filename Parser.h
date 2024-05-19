#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <fstream>

class Frame;

class Parser {
private:
	std::vector<std::string> _lines;
public:
	/// <summary>Wczytuje i wstepnie rozdziela na linie podany plik</summary>
	/// 
	///	Format wczytywanego pliku:
	/// - w poszczególnych liniach kolejne klatki
	/// - w kazdych klatkach kolejne argumenty rozdzielone `;`
	///		- pierwszy argument: sciezka do pliku tla
	///		- kolejne argumenty: poszczególne ksztalty, opisane jako `[nazwa]([param1],[param2],...)`
	/// 
	/// <param name="path">sciezka do pliku</param>
	void readFile(std::string path);

	/// <summary>
	/// Parsuje linie i zwraca je w formie wektora klatek
	/// </summary>
	/// <returns>Wektor klatek</returns>
	std::vector<Frame> getFrames() const;

	/// <summary>
	/// Funkcja pomocnicza, wyciaga z linii kolejne parametry dla klatki
	/// </summary>
	/// <param name="input">wejsciowa linia</param>
	/// <returns></returns>
	static std::vector<std::string> getFrameParams(std::string input);

	static std::string getName(std::string input);

	static std::vector<std::string> getParams(std::string input);
};