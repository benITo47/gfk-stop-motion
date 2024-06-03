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


#include "MyPanel.h"

class MainFrame : public wxFrame
{
public:
	MainFrame();

	void fun_saveAnimationFile(wxCommandEvent& e);
	void fun_loadAnimationFile(wxCommandEvent& e);
	void fun_loadImage(wxCommandEvent& e);
	void fun_addFrame(wxCommandEvent& e);
	void fun_delFrame(wxCommandEvent& e);
	void fun_delShape(wxCommandEvent& e);
	void fun_nextFrame(wxCommandEvent& e);
	void fun_playFrame(wxCommandEvent& e);
	void fun_prevFrame(wxCommandEvent& e);
	void fun_copyPrevFrame(wxCommandEvent& e);
	void OnFillCheckBoxChanged(wxCommandEvent& e);
	void UpdateShapeInPanel(wxCommandEvent& e);
	void OnScrollBrightness(wxScrollEvent& e);
	void OnScrollTransparent(wxScrollEvent& e);
	void OnExit(wxCommandEvent& e);
	void OnAbout(wxCommandEvent& e);
	void OnClose(wxCloseEvent& e);
	void DeleteAllData(wxCommandEvent& e);

private:
	MyPanel* _myPanel;
	wxPanel* shapePanel;
	wxChoice* shapeChoice;
	wxColourPickerCtrl* colorPicker;
	wxColourPickerCtrl* fillColorPicker;
	wxCheckBox* fillCheckBox;
	wxCheckBox* copyPrevFrame;
	wxCheckBox* copyBackground;
	wxStaticText* fillColorLabel;
	wxStaticText* loadedBackgroundLabel;
	wxBoxSizer* shapeSizer;
	wxScrollBar* ScrollBarBrightness;
	wxScrollBar* ScrollBarTransparent;

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
		ID_delAll
	};

};

int clamp(int value, int min, int max);

