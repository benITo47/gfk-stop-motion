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
	/// <summary>Wczytuje i wstępnie rozdziela na linie podany plik</summary>
	/// 
	///	Format wczytywanego pliku:
	/// - w poszczególnych liniach kolejne klatki
	/// - w każdej klatce kolejne argumenty rozdzielone `;`
	///		- pierwszy argument: scieżka do pliku tła
	///		- kolejne argumenty: poszczególne kształty, opisane jako `[nazwa]([param1],[param2],...)`
	/// 
	/// <param name="path">ścieżka do pliku</param>
	void readFile(std::string path);

	/// <summary>
	/// Parsuje linie i zwraca je w formie wektora klatek
	/// </summary>
	/// <returns>Wektor klatek</returns>
	std::vector<Frame> getFrames() const;

	/// <summary>
	/// Funkcja pomocnicza, wyciąga z linii kolejne parametry dla klatki
	/// </summary>
	/// Parametry w linii są rozdzielone średnikami. Pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty
	/// <param name="input">Wejściowa linia</param>
	/// <returns>Wektor zawierający kolejne parametry do stworzenia klatki</returns>
	static std::vector<std::string> getFrameParams(std::string input);


	/// <summary>
	/// Funkcja pomocnicza, zwraca nazwę ksztaltu z łańcucha go opisującego
	/// </summary>
	/// <param name="input">Wejściowy łańcuch w formie `[nazwa]([param1],[param2],...)`</param>
	/// <returns>Nazwa wyciągnięta z łańcucha</returns>
	static std::string getName(std::string input);

	/// <summary>
	/// Funkcja pomocnicza, zwraca wektor zawierający parametry kształtu z lańcucha go opisującego
	/// </summary>
	/// <param name="input">wejściowy łańcuch w formie `[nazwa]([param1],[param2],...)`</param>
	/// <returns>wektor parametrów wyciągnietych z łańcucha</returns>
	static std::vector<std::string> getParams(std::string input);
};