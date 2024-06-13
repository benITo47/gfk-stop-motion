/**
 * @file Parser.h
 * 
 * @brief Parser
 */

#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include <wx/string.h>

class Frame;

/**
 * @class Parser
 * @brief Klasa do parsowania klatek z pliku.
 */
class Parser {
private:
    /// @brief Sciezka do zawartego pliku
    wxString _path;

    /// @brief Zawiera linie z wczytanego/zapisywanego pliku
    std::vector<wxString> _lines;

public:
    /**
     * @brief Wczytuje i wstępnie rozdziela na linie podany plik.
     *
     * Format wczytywanego pliku:
     * - w poszczególnych liniach kolejne klatki
     * - w każdej klatce kolejne argumenty rozdzielone `;`
     *     - pierwszy argument: ścieżka do pliku tła
     *     - kolejne argumenty: poszczególne kształty, opisane jako `[nazwa]([param1],[param2],...)`
     *
     * @param path ścieżka do pliku
     */
    void readFile(const wxString& path);

    /**
     * @brief Zapisuje klatki jako tekst do parsera
    */
    void setFrames(const std::vector<Frame> frames);

    /**
     * @brief Zapisuje klatki do pliku
    */
    void saveToFile(const wxString& path) const;

    /**
     * @brief Parsuje linie i zwraca je w formie wektora klatek.
     *
     * @return Wektor klatek.
     */
    std::vector<Frame> getFrames() const;

    /**
     * @brief Funkcja pomocnicza, wyciąga z linii kolejne parametry dla klatki.
     *
     * Parametry w linii są rozdzielone średnikami. Pierwszym parametrem jest ścieżka do obrazu tła, reszta to narysowane kształty.
     *
     * @param input Wejściowa linia.
     * @return Wektor zawierający kolejne parametry do stworzenia klatki.
     */
    static std::vector<wxString> getFrameParams(const wxString& input);

    /**
     * @brief Funkcja pomocnicza, zwraca nazwę kształtu z łańcucha go opisującego.
     *
     * @param input Wejściowy łańcuch w formie `[nazwa]([param1],[param2],...)`
     * @return Nazwa wyciągnięta z łańcucha.
     */
    static std::string getName(const wxString& input);

    /**
     * @brief Funkcja pomocnicza, zwraca wektor zawierający parametry kształtu z łańcucha go opisującego.
     *
     * @param input Wejściowy łańcuch w formie `[nazwa]([param1],[param2],...)`
     * @return Wektor parametrów wyciągniętych z łańcucha.
     */
    static std::vector<wxString> getParams(const wxString& input);
};
