#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/sizer.h>
#include <wx/scrolbar.h>
#include <wx/radiobut.h>
#include <wx/choice.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>

#include "MyPanel.h"

/**
 * @class MainFrame
 * @brief Główne okno aplikacji do tworzenia animacji stop-motion.
 *
 * Klasa MainFrame jest głównym oknem aplikacji. Zawiera metody umożliwiające 
 * zarządzanie projektem, wczytywanie i zapisywanie plików animacji, dodawanie 
 * i usuwanie klatek, oraz zarządzanie kształtami.
 */
class MainFrame : public wxFrame
{
public:
    /**
     * @brief Konstruktor klasy MainFrame.
     */
    MainFrame();

    /**
     * @brief Tworzy nowy projekt.
     */
    void newProject(wxCommandEvent& e);

    /**
     * @brief Zapisuje animację do pliku.
     */
    void saveAnimationFile(wxCommandEvent& e);

    /**
     * @brief Wczytuje animację z pliku.
     */
    void loadAnimationFile(wxCommandEvent& e);

    /**
     * @brief Wczytuje obraz tła.
     */
    void loadImage(wxCommandEvent& e);

    /**
     * @brief Dodaje nową klatkę do animacji.
     */
    void addFrame(wxCommandEvent& e);

    /**
     * @brief Usuwa bieżącą klatkę z animacji.
     */
    void delFrame(wxCommandEvent& e);

    /**
     * @brief Przechodzi do następnej klatki animacji.
     */
    void nextFrame(wxCommandEvent& e);

    /**
     * @brief Odtwarza animację.
     */
    void playFrame(wxCommandEvent& e);

    /**
     * @brief Przechodzi do poprzedniej klatki animacji.
     */
    void prevFrame(wxCommandEvent& e);

    /**
     * @brief Kopiuje kształty z poprzedniej klatki.
     */
    void copyPrevFrame(wxCommandEvent& e);

    /**
     * @brief Zmienia stan checkboxa odpowiedzialnego za wypełnienie kształtu.
     */
    void onFillCheckBoxChanged(wxCommandEvent& e);

    /**
     * @brief Aktualizuje kształt w panelu rysowania.
     */
    void updateShapeInPanel(wxCommandEvent& e);

    /**
     * @brief Zmienia jasność tła.
     */
    void onScrollBrightness(wxScrollEvent& e);

    /**
     * @brief Zmienia przezroczystość poprzedniej klatki.
     */
    void onScrollTransparent(wxScrollEvent& e);

    /**
     * @brief Metoda wywołuję metodę onClose.
     */
    void onExit(wxCommandEvent& e);

    /**
     * @brief Wyświetla informacje o aplikacji.
     */
    void onAbout(wxCommandEvent& e);

    /**
     * @brief Obsługuje zdarzenie zamknięcia okna.
     */
    void onClose(wxCloseEvent& e);

    /**
     * @brief Usuwa ostatnio dodany kształt.
     */
    void delShape(wxCommandEvent& e);

    /**
     * @brief Usuwa wszystkie kształty z bieżącej klatki.
     */
    void deleteAllShapes(wxCommandEvent& e);

    /**
     * @brief Metoda wywoływana podczas zmiany wartości prędkośći animacji.
     */
    void OnSpinCtrl(wxSpinDoubleEvent& e);

    /**
     * @brief Aktualizuje licznik klatek.
     */
    void changeTextCounter();

private:
    MyPanel* _myPanel; ///< Panel rysowania.
    wxPanel* _shapePanel; ///< Panel wyboru kształtów.
    wxChoice* _shapeChoice; ///< Lista wyboru kształtów.
    wxButton* _playFrame; ///< Przycisk odtwarzania animacji.
    wxColourPickerCtrl* _colorPicker; ///< Kontrolka wyboru koloru obramowania.
    wxColourPickerCtrl* _fillColorPicker; ///< Kontrolka wyboru koloru wypełnienia.
    wxCheckBox* _fillCheckBox; ///< Checkbox do zaznaczania wypełnienia kształtów.
    wxCheckBox* _copyPrevFrame; ///< Checkbox do kopiowania kształtów z poprzedniej klatki.
    wxCheckBox* _copyBackground; ///< Checkbox do kopiowania tła z poprzedniej klatki.
    wxStaticText* _fillColorLabel; ///< Etykieta koloru wypełnienia.
    wxStaticText* _loadedBackgroundLabel; ///< Etykieta załadowanego tła.
    wxSlider* _scrollBarBrightness; ///< Suwak do zmiany jasności tła.
    wxSlider* _scrollBarTransparent; ///< Suwak do zmiany przezroczystości tła.
    wxStaticText* counterDisplay; ///< Wyświetlacz licznika klatek.
    wxSpinCtrlDouble* spinCtrl; ///< spinCtrl umożliwiający zmienianie wartości prędkości animacji.
    wxTextCtrl* valueDisplay; ///< Wyświetlacz wartości SpinCtrl.

    enum {
        ID_saveFile = 1001,
        ID_loadFile,
        ID_loadImage,
        ID_addFrame,
        ID_delFrame,
        ID_addShape,
        ID_nextFrame,
        ID_playFrame,
        ID_prevFrame,
        ID_checkbox,
        ID_copyPrevFrame,
        ID_copyPrevBackground,
        ID_scrollBarTransparent,
        ID_scrollBarBrightness,
        ID_delLastShape,
        ID_exit,
        ID_about,
        ID_delAll,
        ID_newProject,
        ID_spinButton,
        ID_spinCtrl
    };
};
