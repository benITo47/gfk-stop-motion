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

class MainFrame : public wxFrame
{
public:
	MainFrame();

	void newProject(wxCommandEvent& e);
	void saveAnimationFile(wxCommandEvent& e);
	void loadAnimationFile(wxCommandEvent& e);
	void loadImage(wxCommandEvent& e);
	void addFrame(wxCommandEvent& e);
	void delFrame(wxCommandEvent& e);
	void delShape(wxCommandEvent& e);
	void nextFrame(wxCommandEvent& e);
	void playFrame(wxCommandEvent& e);
	void prevFrame(wxCommandEvent& e);
	void copyPrevFrame(wxCommandEvent& e);
	void onFillCheckBoxChanged(wxCommandEvent& e);
	void updateShapeInPanel(wxCommandEvent& e);
	void onScrollBrightness(wxScrollEvent& e);
	void onScrollTransparent(wxScrollEvent& e);
	void onExit(wxCommandEvent& e);
	void onAbout(wxCommandEvent& e);
	void onClose(wxCloseEvent& e);
	void deleteAllShapes(wxCommandEvent& e);
	void OnSpinButton(wxSpinEvent& e);
	void OnSpinCtrl(wxSpinDoubleEvent& e);
	void changeTextCounter();

private:
	MyPanel* _myPanel = nullptr;
	wxPanel* _shapePanel;
	wxChoice* _shapeChoice;
	wxButton* _playFrame;
	wxColourPickerCtrl* _colorPicker;
	wxColourPickerCtrl* _fillColorPicker;
	wxCheckBox* _fillCheckBox;
	wxCheckBox* _copyPrevFrame;
	wxCheckBox* _copyBackground;
	wxStaticText* _fillColorLabel;
	wxStaticText* _loadedBackgroundLabel;
	wxScrollBar* _scrollBarBrightness;
	wxScrollBar* _scrollBarTransparent; 
	wxStaticText* counterDisplay;
	//wxSpinButton* spinButton;
	wxSpinCtrlDouble* spinCtrl;
	wxTextCtrl* valueDisplay;

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

	//int maxCounter = 1;
};

