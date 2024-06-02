#include "GUI.h"


MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stop motion po roku w Rosji", wxDefaultPosition, wxDefaultSize) {
    _myPanel = new MyPanel(this);
    _myPanel->SetBackgroundColour(*wxWHITE);

    wxButton* _saveFile;
    wxButton* _loadFile;
    wxButton* _loadImage;
    wxButton* _addFrame;
    wxButton* _delFrame;
    wxButton* _addShape;
    wxButton* _nextFrame;
    wxButton* _playFrame;
    wxButton* _prevFrame;
    wxButton* _delLastShape;

    _saveFile = new wxButton(this, ID_saveFile, "SAVE");
    _loadFile = new wxButton(this, ID_loadFile, "LOAD");
    _loadImage = new wxButton(this,ID_loadImage, "LOAD BACKGROUND");
    _addFrame = new wxButton(this, ID_addFrame, "ADD FRAME");
    _delFrame = new wxButton(this, ID_delFrame, "DELETE FRAME");
    _addShape = new wxButton(this, ID_addShape, "ADD SHAPE");
    _delLastShape = new wxButton(this, ID_delLastShape, "DELETE LAST SHAPE");
    _nextFrame = new wxButton(this, ID_nextFrame, "->");
    _playFrame = new wxButton(this, ID_playFrame, ">");
    _prevFrame = new wxButton(this, ID_prevFrame, "<-");

    copyPrevFrame = new wxCheckBox(this, ID_copyPrevFrame, "Copy previous frame");
    copyBackground = new wxCheckBox(this, ID_copyPrevBackground, "Copy previous background");
    ScrollBarBrightness = new wxScrollBar(this, ID_scrollBarBrightness, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    ScrollBarBrightness->SetScrollbar(100, 10, 200, 10);

    wxStaticText* transparencyText = new wxStaticText(this, wxID_ANY, "Adjust transparency of previous frame", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    ScrollBarTransparent = new wxScrollBar(this, ID_scrollBarTransparent, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    ScrollBarTransparent->SetScrollbar(20, 10, 100, 10);

    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
    sizer1->Add(_saveFile, 1, wxEXPAND | wxTOP, 5);
    sizer1->Add(_loadFile, 1, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(_addFrame, 1, wxEXPAND | wxTOP, 5);
    sizer2->Add(_delFrame, 1, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
    sizer3->Add(copyPrevFrame, 1, wxEXPAND | wxTOP, 5);
    sizer3->Add(copyBackground,1, wxEXPAND | wxTOP, 5);
    sizer3->Add(_addShape, 1, wxEXPAND | wxTOP, 10);
    sizer3->Add(_delLastShape, 1, wxEXPAND | wxTOP, 10);
    sizer3->AddStretchSpacer();
    sizer3->Add(transparencyText,0, wxALIGN_CENTER_HORIZONTAL, 5);
    sizer3->Add(ScrollBarTransparent, 0, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer4 = new wxBoxSizer(wxVERTICAL);
    sizer4->Add(_loadImage,1,wxEXPAND | wxTOP, 10);
    sizer4->Add(ScrollBarBrightness,0, wxEXPAND | wxTOP, 10);
    ScrollBarBrightness->Hide();

    wxBoxSizer* sizer5 = new wxBoxSizer(wxHORIZONTAL);
    sizer5->Add(_prevFrame, 1, wxEXPAND | wxTOP, 5);
    sizer5->Add(_playFrame, 1, wxEXPAND | wxTOP, 5);
    sizer5->Add(_nextFrame, 1, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer0 = new wxBoxSizer(wxVERTICAL);
    sizer0->Add(sizer1, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer2, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer3, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer4, 0, wxEXPAND | wxALL, 5);
    sizer0->AddStretchSpacer();


    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(_myPanel, 8, wxEXPAND | wxALL, 5);
    mainSizer->Add(sizer0, 2, wxEXPAND | wxALL, 5);

    shapePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    shapePanel->Hide();
    wxBoxSizer* shapeSizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString shapeChoices;
    shapeChoices.Add("Line");
    shapeChoices.Add("Polyline");
    shapeChoices.Add("Curve");
    shapeChoices.Add("Circle");
    shapeChoices.Add("Ellipse");
    shapeChoices.Add("Square");
    shapeChoices.Add("Triangle");

    shapeChoice = new wxChoice(shapePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, shapeChoices);
    shapeChoice->SetSelection(0);
    shapeSizer->Add(shapeChoice, 0, wxALL | wxEXPAND, 10);

    wxStaticText* colorLabel = new wxStaticText(shapePanel, wxID_ANY, "Choose Border Color:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    shapeSizer->Add(colorLabel, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    colorPicker = new wxColourPickerCtrl(shapePanel, wxID_ANY);
    shapeSizer->Add(colorPicker, 0, wxALL | wxEXPAND, 5);

    fillCheckBox = new wxCheckBox(shapePanel, ID_checkbox, "Filled");
    shapeSizer->Add(fillCheckBox, 0, wxALIGN_CENTER | wxALL, 5);

    fillColorLabel = new wxStaticText(shapePanel, wxID_ANY, "Choose Fill Color:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    fillColorPicker = new wxColourPickerCtrl(shapePanel, wxID_ANY);

    shapeSizer->Add(fillColorLabel, 0, wxALIGN_CENTER | wxALL, 5);
    shapeSizer->Add(fillColorPicker, 0, wxALL | wxEXPAND, 5);
    fillCheckBox->Bind(wxEVT_CHECKBOX, &MainFrame::OnFillCheckBoxChanged, this);

    shapePanel->SetSizerAndFit(shapeSizer);

    sizer0->Add(shapePanel, 0, wxEXPAND | wxALL, 5);
    sizer0->AddStretchSpacer();
    sizer0->AddStretchSpacer();
    sizer0->AddStretchSpacer();
    sizer0->Add(sizer5, 0, wxEXPAND | wxALL, 5);   //Fixed debug assertions

    SetSizerAndFit(mainSizer);

    this->SetInitialSize(wxSize(1450,950));
    this->SetMinSize(wxSize(1450,950));
    this->SetMaxSize(wxSize(-1,-1));
    Centre();

    Bind(wxEVT_CHECKBOX, &MainFrame::OnFillCheckBoxChanged, this, ID_checkbox);
    Bind(wxEVT_CHECKBOX, &MainFrame::fun_copyPrevFrame, this, ID_copyPrevFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_saveAnimationFile, this, ID_saveFile);
    Bind(wxEVT_BUTTON, &MainFrame::fun_loadAnimationFile, this, ID_loadFile);
    Bind(wxEVT_BUTTON, &MainFrame::fun_loadImage, this, ID_loadImage);
    Bind(wxEVT_BUTTON, &MainFrame::fun_addFrame, this, ID_addFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_delFrame, this, ID_delFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_addShape, this, ID_addShape);
    Bind(wxEVT_BUTTON, &MainFrame::fun_delShape, this, ID_delLastShape);
    Bind(wxEVT_BUTTON, &MainFrame::fun_nextFrame, this, ID_nextFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_playFrame, this, ID_playFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_prevFrame, this, ID_prevFrame);
    Bind(wxEVT_CHOICE, &MainFrame::UpdateShapeInPanel, this);
    Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::UpdateShapeInPanel, this);
    Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::UpdateShapeInPanel, this);
    Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::OnScrollBrightness, this, ID_scrollBarBrightness);
    Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::OnScrollTransparent, this, ID_scrollBarTransparent);
}


void MainFrame::fun_saveAnimationFile(wxCommandEvent& e) {
    wxFileDialog saveFileDialog(this, _("Save animation file"), "", "",
        "Image files (*.anim)|*.anim", wxFD_SAVE);

    if(saveFileDialog.ShowModal() == wxID_OK)
        _myPanel->cfg->saveFramesToFile(saveFileDialog.GetPath());
}
void MainFrame::fun_loadAnimationFile(wxCommandEvent& e) {
    wxFileDialog openFileDialog(this, _("Open animation file"), "", "",
        "Image files (*.anim)|*.anim", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_OK)
        _myPanel->cfg->loadFramesFromFile(openFileDialog.GetPath());

    _myPanel->Refresh();
}

void MainFrame::fun_loadImage(wxCommandEvent& e) {

	ScrollBarBrightness->Show();
	ScrollBarBrightness->SetScrollbar(100, 10, 200, 10);
    _myPanel->cfg->setBrightness(100);
    wxFileDialog wxOpenFileDialog(this, _("Open Image file"), "", "",
                                  "Image files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp",
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (wxOpenFileDialog.ShowModal() == wxID_OK) {
        wxString fileName = wxOpenFileDialog.GetPath();
        _myPanel->cfg->loadBackground(fileName);
        _myPanel->Refresh();
    }
	this->Layout();
}

void MainFrame::fun_addFrame(wxCommandEvent& e) {

    _myPanel->cfg->addFrame(copyPrevFrame->GetValue(), copyBackground->GetValue());
    _myPanel->Refresh();
}

void MainFrame::fun_delFrame(wxCommandEvent& e) {
    _myPanel->cfg->deleteFrame();
    _myPanel->Refresh();
}
void MainFrame::fun_addShape(wxCommandEvent& e) {
	MainFrame::UpdateShapeInPanel(e);

	if (!shapePanel->IsShown()) {
		shapePanel->Show();
		fillColorLabel->Hide();
		fillColorPicker->Hide();
		Layout();
	}
	else {
		shapePanel->Hide();
		Layout();
	}
}

void MainFrame::fun_delShape(wxCommandEvent& e) {
	_myPanel->cfg->deleteLastShape();
    _myPanel->Refresh();
}

void  MainFrame::fun_nextFrame(wxCommandEvent &e){
    _myPanel->cfg->nextFrame();
    _myPanel->Refresh();
}

void MainFrame::fun_playFrame(wxCommandEvent& e) {
	std::cout << "play Frame\n";
    _myPanel->PlayAnimation();
}
void MainFrame::fun_prevFrame(wxCommandEvent& e) {
    _myPanel->cfg->previousFrame();
    _myPanel->Refresh();
}
void MainFrame::OnFillCheckBoxChanged(wxCommandEvent& e) {
	MainFrame::UpdateShapeInPanel(e);
	bool isChecked = fillCheckBox->IsChecked();
	fillColorLabel->Show(isChecked);
	fillColorPicker->Show(isChecked);
	shapePanel->Layout();
}
void MainFrame::UpdateShapeInPanel(wxCommandEvent& e) {
	wxString shape = shapeChoice->GetStringSelection();
	wxColour borderColor = colorPicker->GetColour();
	bool filled = fillCheckBox->IsChecked();
	wxColour fillColor(255, 255, 255, 0);

	if (filled) {
		fillColor = fillColorPicker->GetColour();
	}

	_myPanel->SetShape(shape, borderColor, filled, fillColor);
}



void MainFrame::OnScrollBrightness(wxScrollEvent& e) {

    std::cout << ScrollBarBrightness->GetThumbPosition() << std::endl;
    _myPanel->cfg->setBrightness(ScrollBarBrightness->GetThumbPosition());
    _myPanel->Refresh();
}

void MainFrame::OnScrollTransparent(wxScrollEvent& e) {
    _myPanel->cfg->setOpacity(ScrollBarTransparent->GetThumbPosition());
    //std::cout << ScrollBarTransparent->GetThumbPosition() << std::endl;
    _myPanel->Refresh();
}

void MainFrame::fun_copyPrevFrame(wxCommandEvent& e) {
	if(copyPrevFrame->GetValue())
		std::cout << "User wants to copy previous frame!\n";
}

