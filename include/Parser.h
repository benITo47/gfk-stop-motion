/**
 * @file Parser.h
 * 
 * @brief Moduł z zaimplementowaną logiką zapisu oraz odczytu z pliku
 * 
 * ## Format pliku 
 * Projekt animacji składa się z dwóch części: pliku animacji, oraz folderu `img` zawierającego tła poszczególnych klatek. 
 * Zalecane jest, aby na elementy te przeznaczyć osobny katalog projektowy.
 * 
 * Dane o animacji zapisane są w pliku tekstowym o rozszerzeniu `.anim`. W kolejnych linijkach pliku znajdują się informacje o kolejnych klatkach animacji. 
 * Wewnątrz linijek może znajdować się dowolnie dużo wyrażeń rozdzielonych znakiem ';', przy czym:
 * - pierwszym wyrażeniem jest nazwa obrazu tła - wyrażenie to jest puste, jeżeli tła w klatce nie ma
 * - kolejne wyrażenia to reprezentacje kształtów narysowanych na klatce, opisane w formacie `[nazwa]([x0],[y0],[x1],[y1],[kolor_obramowania][kolor_wypełnienia])`. 
 * Tak jednolity format zapisu umożliwiony jest przez fakt, że każdy rodzaj kształtu zapamiętany jest jako para punktów `(x0, y0); (x1, y1)`.
 * 
 * ## Zapis do pliku
 * Zapis zaimplementowany jest warstwowo. Cały proces wywoływany jest przez funkcję `MainFrame::saveAnimationFile`. 
 * Funkcja ta otwiera okno dialogowe zapisu, a następnie przekazuje ścieżkę pliku do funkcji `ConfigClass::saveFramesToFile`.
 * 
 * ### Zapis obrazów tła
 * Przy tworzeniu animacji użytkownik ma możliwość wybrać plik obrazu o wspieranym formacie jako tło swojej klatki znajdujący się w dowolnym miejscu na jego komputerze. 
 * W pliku `.anim` mogłaby zostać zapisana ścieżka do danego obrazu (tak też zostało to zaimplementowane na początku), powoduje to jednak kilka problemów:
 * - Użytkownik może usunąć obraz, nie myśląc o tym że używany jest w animacji, co poskutkuje zniszczeniem projektu
 * - Użytkownik może chcieć przesłać komuś swoją animację, na innym komputerze zaś prawie na pewno w podanych lokalizacjach nie będą się znajdowały potrzebne pliki
 * 
 * Aby zatem zaradzić temu problemowi, każdorazowo przy zapisie wszystkie bitmapy tła są zapisywane w formacie `.jpg` do folderu `img` 
 * (istniejącego bądź tworzonego przez program), znajdującego się w tym samym katalogu co plik `.anim`. Dzięki temu wszystkie obrazy tła znajdują się w jednym miejscu, 
 * a operowanie od tego czasu na ścieżkach względnych umożliwia łatwe przenoszenie projektu.
 * 
 * Operacja ta wykonywana jest przez funkcję `ConfigClass::copyImagesToProjectDirectory`. Nazwy zapisywanych plików to `[tytuł_animacji][numer_klatki].jpg`.
 * 
 * ### Zapis informacji o klatkach
 * Po skopiowaniu obrazów następuje zapis samej animacji do pliku `.anim`. W tym momencie dostrzegamy warstwowość implementacji algorytmu zapisu. 
 * Patrząc na najwyższą warstwę, najpierw przy użyciu metody `Parser::setFrames` do obiektu klasy `Parser` zapisywane są wszystkie klatki, 
 * a następnie przez `Parser::saveToFile` klatki są zapisywane do pliku. Pod tym bardzo prostym API kryje się kilka operacji:
 * - Metoda `Parser::setFrames` wywołuje na każdym obiekcie klasy `Frame` metodę `Frame::toString()`, zapisując klatki od razu jako wektor napisów
 * - Wewnątrz `Frame::toString()`, dla każdego kształtu następuje wywołanie `Shape::toString()`
 * 
 * Dzięki tej warstwowej implementacji, łatwo można było testować każdy z kroków procesu.
 * 
 * 
 * ## Wczytywanie z pliku
 * Wczytywanie jest procesem odwrotnym do zapisywania, o dość analogicznej implementacji:
 * - Początek - `MainFrame::saveAnimationFile` - okno dialogowe i ustalenie ścieżki wczytywanego pliku `.anim`
 * - Wywołanie `ConfigClass::loadFramesFromFile`
 * - Utworzenie obiektu klasy `Parser` i wywołanie metody `Parser::readFile`
 * - Konwersja wektora napisów na wektor obiektów typu `Frame` przez wywołanie metody `Parser::getFrames`, korzystającej z:
 *  - `Frame::fromString` - wykorzystuje funkcję pomocniczą `Parser::getFrameParams`, korzysta z:
 *      - `Shape::fromString` - wykorzystuje funkcje pomocnicze `Parser::getName` oraz `Parser::getParams`.
 * - Utworzenie wektora klatek w `ConfigClass`.
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
     *     - kolejne argumenty: poszczególne kształty, opisane jako `[nazwa]([x0],[y0],[x1],[y1],[kolor_obramowania][kolor_wypełnienia])`
     *
     * @param path ścieżka do pliku
     */
    void readFile(const wxString& path);

    /**
     * @brief Zapisuje klatki jako tekst do parsera
    */
    void setFrames(const std::vector<Frame>& frames);

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
