#pragma once

#include <wx/wx.h>
#include <vector>
#include <array>
#include <memory>
#include "ConfigClass.h"

class ConfigClass;

/**
 * @class MyPanel
 * @brief Panel do rysowania kształtów i zarządzania animacją.
 *
 * Klasa MyPanel jest odpowiedzialna za obsługę zdarzeń rysowania, 
 * aktualizację panelu oraz odtwarzanie animacji. Przechowuje i 
 * zarządza konfiguracją kształtów i klatek animacji.
 */
class MyPanel : public wxPanel {
public:
    /**
     * @brief Konstruktor klasy MyPanel.
     */
    MyPanel(wxWindow* parent);

    /**
     * @brief Obsługuje zdarzenia rysowania na panelu.
     */
    void onPaint(wxPaintEvent& event);

    /**
     * @brief Obsługuje zdarzenie wyboru drugiego punktu potrzebnego do stworzenia figury.
     */
    void onMotion(wxMouseEvent& event);

    /**
     * @brief Obsługuje zdarzenie wyboru pierwszego punktu jako punktu od którego zaczynamy rysować figurę oraz
     	przy kolejnym wyborze - zapisanie kształtu.
     */
    void onLeftDown(wxMouseEvent& event);

    /**
     * @brief Ustawia parametry kształtu do rysowania.
     * @param shape Typ kształtu.
     * @param borderColor Kolor obramowania.
     * @param filled Czy kształt ma być wypełniony.
     * @param fillColor Kolor wypełnienia.
     */
    void setShape(const wxString& shape, const wxColour& borderColor, bool filled, const wxColour& fillColor);

    /**
     * @brief Odtwarza animację.
     */
    void playAnimation();

    friend class MainFrame;

private:
    std::shared_ptr<ConfigClass> _cfg; ///< Wskaźnik do obiektu konfiguracji.

    /**
    	*@brief flagi służące do poprawnego obsługiwania animacji
    */
    std::atomic<bool> stopFlag = false; ///< Flaga zatrzymania animacji. Flaga pomocna
    std::atomic<bool> prevAnimation = false; ///< Flaga poprzedniej animacji. Jeżeli animacja została zatrzymana to zacznij od poprawnego iteratora (na tym na kótrym animacja została zatrzymana)
    std::atomic<bool> endAnimation = false; ///< Flaga zakończenia animacji. Flaga pomocna
    int _clickCount = 0; ///< Licznik kliknięć myszy.

};
