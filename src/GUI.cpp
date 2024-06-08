#include "GUI.h"
#include "util.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stop motion po roku w Rosji", wxDefaultPosition, wxDefaultSize) {
    _myPanel = new MyPanel(this);
    _myPanel->SetBackgroundColour(*wxWHITE);

    wxButton* _loadImage;
    wxButton* _addFrame;
    wxButton* _delFrame;
    wxButton* _nextFrame;
    wxButton* _playFrame;
    wxButton* _prevFrame;
    wxButton* _delLastShape;
    wxButton* _delAll;

    _loadImage = new wxButton(this, ID_loadImage, "Load background");
    _addFrame = new wxButton(this, ID_addFrame, "Add frame");
    _delFrame = new wxButton(this, ID_delFrame, "Delete frame");
    _delLastShape = new wxButton(this, ID_delLastShape, "Delete last shape");
    _delAll = new wxButton(this, ID_delAll, "Delete all shapes");
    _nextFrame = new wxButton(this, ID_nextFrame, "->");
    _playFrame = new wxButton(this, ID_playFrame, ">");
    _prevFrame = new wxButton(this, ID_prevFrame, "<-");

    wxMenu* menuFile = new wxMenu();
    menuFile->Append(ID_newProject, "&New project", "");
    menuFile->Append(ID_saveFile, "&Save to file", "");
    menuFile->Append(ID_loadFile, "&Load from file", "");
    menuFile->Append(ID_exit, "&Exit", "Quit this program");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(ID_about, "&About", "Show about dialog");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    _copyPrevFrame = new wxCheckBox(this, ID_copyPrevFrame, "Copy shapes");
    _copyBackground = new wxCheckBox(this, ID_copyPrevBackground, "Copy background");
    _scrollBarBrightness = new wxScrollBar(this, ID_scrollBarBrightness, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    _scrollBarBrightness->SetScrollbar(100, 10, 200, 10);

    wxStaticText* transparencyText = new wxStaticText(this, wxID_ANY, "Middle layer opacity", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    _scrollBarTransparent = new wxScrollBar(this, ID_scrollBarTransparent, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    _scrollBarTransparent->SetScrollbar(20, 10, 100, 10);

    _loadedBackgroundLabel = new wxStaticText(this, wxID_ANY, "Background brightness", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(_addFrame, 1, wxEXPAND | wxTOP, 5);
    sizer2->Add(_delFrame, 1, wxEXPAND | wxTOP, 5);

    _shapePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    wxBoxSizer* shapeSizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString shapeChoices;
    shapeChoices.Add("Line");
    shapeChoices.Add("Polyline");
    shapeChoices.Add("Curve");
    shapeChoices.Add("Circle");
    shapeChoices.Add("Ellipse");
    shapeChoices.Add("Square");
    shapeChoices.Add("Triangle");

    _shapeChoice = new wxChoice(_shapePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, shapeChoices);
    _shapeChoice->SetSelection(0);
    shapeSizer->Add(_shapeChoice, 0, wxALL | wxEXPAND, 10);

    wxStaticText* colorLabel = new wxStaticText(_shapePanel, wxID_ANY, "Border color", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    shapeSizer->Add(colorLabel, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    _colorPicker = new wxColourPickerCtrl(_shapePanel, wxID_ANY);
    shapeSizer->Add(_colorPicker, 0, wxALL | wxEXPAND, 5);

    _fillCheckBox = new wxCheckBox(_shapePanel, ID_checkbox, "Filled");
    shapeSizer->Add(_fillCheckBox, 0, wxALIGN_CENTER | wxALL, 5);
    _fillCheckBox->SetValue(true);

    _fillColorLabel = new wxStaticText(_shapePanel, wxID_ANY, "Fill color:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    _fillColorPicker = new wxColourPickerCtrl(_shapePanel, wxID_ANY);

    shapeSizer->Add(_fillColorLabel, 0, wxALIGN_CENTER | wxALL, 5);
    shapeSizer->Add(_fillColorPicker, 0, wxALL | wxEXPAND, 5);
    _fillCheckBox->Bind(wxEVT_CHECKBOX, &MainFrame::onFillCheckBoxChanged, this);

    _shapePanel->SetSizerAndFit(shapeSizer);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
    sizer3->Add(_shapePanel, 0, wxEXPAND | wxALL, 5);
    sizer3->Add(_copyPrevFrame, 1, wxEXPAND | wxTOP, 5);
    sizer3->Add(_copyBackground, 1, wxEXPAND | wxTOP, 5);
    sizer3->Add(_delLastShape, 1, wxEXPAND | wxTOP, 10);
    sizer3->Add(_delAll, 1, wxEXPAND | wxTOP, 10);
    sizer3->AddStretchSpacer();
    sizer3->Add(transparencyText, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    sizer3->Add(_scrollBarTransparent, 0, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer4 = new wxBoxSizer(wxVERTICAL);
    sizer4->Add(_loadImage, 1, wxEXPAND | wxTOP, 10);
    sizer4->Add(_loadedBackgroundLabel, 0, wxEXPAND | wxTOP, 10);
    sizer4->Add(_scrollBarBrightness, 0, wxEXPAND | wxTOP, 10);
    _loadedBackgroundLabel->Hide();
    _scrollBarBrightness->Hide();

    wxBoxSizer* sizer5 = new wxBoxSizer(wxHORIZONTAL);
    sizer5->Add(_prevFrame, 1, wxEXPAND | wxTOP, 5);
    sizer5->Add(_playFrame, 1, wxEXPAND | wxTOP, 5);
    sizer5->Add(_nextFrame, 1, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer0 = new wxBoxSizer(wxVERTICAL);
    //sizer0->Add(sizer1, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer2, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer3, 0, wxEXPAND | wxALL, 5);
    sizer0->Add(sizer4, 0, wxEXPAND | wxALL, 5);
    sizer0->AddStretchSpacer();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(_myPanel, 8, wxEXPAND | wxALL, 5);
    mainSizer->Add(sizer0, 2, wxEXPAND | wxALL, 5);

    sizer0->AddStretchSpacer();
    sizer0->AddStretchSpacer();
    sizer0->AddStretchSpacer();
    sizer0->Add(sizer5, 0, wxEXPAND | wxALL, 5);   //Fixed debug assertions

    SetSizerAndFit(mainSizer);

    this->SetInitialSize(wxSize(1550, 950));
    this->SetMinSize(wxSize(1550, 950));
    this->SetMaxSize(wxSize(1550, 950));
    Centre();

    Bind(wxEVT_MENU, &MainFrame::saveAnimationFile, this, ID_saveFile);
    Bind(wxEVT_MENU, &MainFrame::loadAnimationFile, this, ID_loadFile);
    Bind(wxEVT_MENU, &MainFrame::newProject, this, ID_newProject);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
    Bind(wxEVT_MENU, &MainFrame::onExit, this, ID_exit);
    Bind(wxEVT_MENU, &MainFrame::onAbout, this, ID_about);
    Bind(wxEVT_CHECKBOX, &MainFrame::onFillCheckBoxChanged, this, ID_checkbox);
    Bind(wxEVT_CHECKBOX, &MainFrame::copyPrevFrame, this, ID_copyPrevFrame);
    Bind(wxEVT_BUTTON, &MainFrame::loadImage, this, ID_loadImage);
    Bind(wxEVT_BUTTON, &MainFrame::addFrame, this, ID_addFrame);
    Bind(wxEVT_BUTTON, &MainFrame::delFrame, this, ID_delFrame);
    Bind(wxEVT_BUTTON, &MainFrame::delShape, this, ID_delLastShape);
    Bind(wxEVT_BUTTON, &MainFrame::deleteAllData, this, ID_delAll);
    Bind(wxEVT_BUTTON, &MainFrame::nextFrame, this, ID_nextFrame);
    Bind(wxEVT_BUTTON, &MainFrame::playFrame, this, ID_playFrame);
    Bind(wxEVT_BUTTON, &MainFrame::prevFrame, this, ID_prevFrame);
    Bind(wxEVT_CHOICE, &MainFrame::updateShapeInPanel, this);
    Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::updateShapeInPanel, this);
    Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::updateShapeInPanel, this);
    Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
    Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
}


void MainFrame::saveAnimationFile(wxCommandEvent& e) {
    wxFileDialog saveFileDialog(this, _("Save animation file"), "", "",
        "Animation files (*.anim)|*.anim", wxFD_SAVE);

    if (saveFileDialog.ShowModal() == wxID_OK)
        _myPanel->_cfg->saveFramesToFile(toUnixPath(saveFileDialog.GetPath()));
}
void MainFrame::loadAnimationFile(wxCommandEvent& e) {
    wxFileDialog openFileDialog(this, _("Open animation file"), "", "",
        "Animation files (*.anim)|*.anim", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK)
        _myPanel->_cfg->loadFramesFromFile(toUnixPath(openFileDialog.GetPath()));

    _myPanel->Refresh();
}
void MainFrame::newProject(wxCommandEvent& e) {
    // ToDo
}

void MainFrame::loadImage(wxCommandEvent& e) {
    _loadedBackgroundLabel->Show();
    _scrollBarBrightness->Show();
    _scrollBarBrightness->SetScrollbar(100, 10, 200, 10);
    _myPanel->_cfg->setBrightness(100);
    wxFileDialog wxOpenFileDialog(this, _("Open Image file"), "", "",
        "Image files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (wxOpenFileDialog.ShowModal() == wxID_OK) {
        wxString fileName = toUnixPath(wxOpenFileDialog.GetPath());
        _myPanel->_cfg->loadBackground(fileName);
        _myPanel->Refresh();
    }
    this->Layout();
}

void MainFrame::addFrame(wxCommandEvent& e) {

    _myPanel->_cfg->addFrame(_copyPrevFrame->GetValue(), _copyBackground->GetValue());
    _myPanel->Refresh();
}

void MainFrame::delFrame(wxCommandEvent& e) {
    _myPanel->_cfg->deleteFrame();
    _myPanel->Refresh();
}

void MainFrame::delShape(wxCommandEvent& e) {
    _myPanel->_cfg->deleteLastShape();
    _myPanel->Refresh();
}

void  MainFrame::nextFrame(wxCommandEvent& e) {
    _myPanel->_cfg->nextFrame();
    _myPanel->Refresh();
}

void MainFrame::playFrame(wxCommandEvent& e) {
    std::cout << "play Frame\n";
    _myPanel->playAnimation();
}
void MainFrame::prevFrame(wxCommandEvent& e) {
    _myPanel->_cfg->previousFrame();
    _myPanel->Refresh();
}
void MainFrame::onFillCheckBoxChanged(wxCommandEvent& e) {
    MainFrame::updateShapeInPanel(e);
    bool isChecked = _fillCheckBox->IsChecked();
    _fillColorLabel->Show(isChecked);
    _fillColorPicker->Show(isChecked);
    _shapePanel->Layout();
}
void MainFrame::updateShapeInPanel(wxCommandEvent& e) {
    wxString shape = _shapeChoice->GetStringSelection();
    wxColour borderColor = _colorPicker->GetColour();
    bool filled = _fillCheckBox->IsChecked();
    wxColour fillColor(255, 255, 255, 0);

    if (filled) {
        fillColor = _fillColorPicker->GetColour();
    }

    _myPanel->setShape(shape, borderColor, filled, fillColor);
}

void MainFrame::onScrollBrightness(wxScrollEvent& e) {

    std::cout << _scrollBarBrightness->GetThumbPosition() << std::endl;
    _myPanel->_cfg->setBrightness(_scrollBarBrightness->GetThumbPosition());
    _myPanel->Refresh();
}

void MainFrame::onScrollTransparent(wxScrollEvent& e) {
    _myPanel->_cfg->setOpacity(_scrollBarTransparent->GetThumbPosition());
    //std::cout << _scrollBarTransparent->GetThumbPosition() << std::endl;
    _myPanel->Refresh();
}

void MainFrame::copyPrevFrame(wxCommandEvent& e) {
    if (_copyPrevFrame->GetValue())
        std::cout << "User wants to copy previous frame!\n";
}

void MainFrame::onExit(wxCommandEvent& e)
{
    Close(true);
}

void MainFrame::onAbout(wxCommandEvent& e)
{
    wxMessageBox("This application, named Stop Motion, is a computer graphics project created by Daniel Czapla, Bartlomiej Obrochta, and Franciszek Urbanski.\n The project allows adding and removing new shapes available on the drawing panel. Drawing is done by selecting two points on the panel, choosing a shape, its color and filling it with another one. It is possible to delete the last added shapes, load your own background, add(delete) frames and play frames as an animation.",
        "About Stop Motion", wxOK | wxICON_INFORMATION);
}

void MainFrame::onClose(wxCloseEvent& e)
{
    int answer = wxMessageBox("Are you sure you want to exit?", "Confirm Exit", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    if (answer == wxYES)
        e.Skip();
    else
        e.Veto();
}


void MainFrame::deleteAllData(wxCommandEvent& e) {
    std::cout << "Implement logic for clearing all data\n";
}