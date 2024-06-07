#include "GUI.h"

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

    copyPrevFrame = new wxCheckBox(this, ID_copyPrevFrame, "Copy shapes");
    copyBackground = new wxCheckBox(this, ID_copyPrevBackground, "Copy background");
    ScrollBarBrightness = new wxScrollBar(this, ID_scrollBarBrightness, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    ScrollBarBrightness->SetScrollbar(100, 10, 200, 10);

    wxStaticText* transparencyText = new wxStaticText(this, wxID_ANY, "Middle layer opacity", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    ScrollBarTransparent = new wxScrollBar(this, ID_scrollBarTransparent, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    ScrollBarTransparent->SetScrollbar(20, 10, 100, 10);

    loadedBackgroundLabel = new wxStaticText(this, wxID_ANY, "Background brightness", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(_addFrame, 1, wxEXPAND | wxTOP, 5);
    sizer2->Add(_delFrame, 1, wxEXPAND | wxTOP, 5);

    shapePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
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

    wxStaticText* colorLabel = new wxStaticText(shapePanel, wxID_ANY, "Border color", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    shapeSizer->Add(colorLabel, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    colorPicker = new wxColourPickerCtrl(shapePanel, wxID_ANY);
    shapeSizer->Add(colorPicker, 0, wxALL | wxEXPAND, 5);

    fillCheckBox = new wxCheckBox(shapePanel, ID_checkbox, "Filled");
    shapeSizer->Add(fillCheckBox, 0, wxALIGN_CENTER | wxALL, 5);
    fillCheckBox->SetValue(true);

    fillColorLabel = new wxStaticText(shapePanel, wxID_ANY, "Fill color:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    fillColorPicker = new wxColourPickerCtrl(shapePanel, wxID_ANY);

    shapeSizer->Add(fillColorLabel, 0, wxALIGN_CENTER | wxALL, 5);
    shapeSizer->Add(fillColorPicker, 0, wxALL | wxEXPAND, 5);
    fillCheckBox->Bind(wxEVT_CHECKBOX, &MainFrame::OnFillCheckBoxChanged, this);

    shapePanel->SetSizerAndFit(shapeSizer);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
    sizer3->Add(shapePanel, 0, wxEXPAND | wxALL, 5);
    sizer3->Add(copyPrevFrame, 1, wxEXPAND | wxTOP, 5);
    sizer3->Add(copyBackground, 1, wxEXPAND | wxTOP, 5);
    sizer3->Add(_delLastShape, 1, wxEXPAND | wxTOP, 10);
    sizer3->Add(_delAll, 1, wxEXPAND | wxTOP, 10);
    sizer3->AddStretchSpacer();
    sizer3->Add(transparencyText, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    sizer3->Add(ScrollBarTransparent, 0, wxEXPAND | wxTOP, 5);

    wxBoxSizer* sizer4 = new wxBoxSizer(wxVERTICAL);
    sizer4->Add(_loadImage, 1, wxEXPAND | wxTOP, 10);
    sizer4->Add(loadedBackgroundLabel, 0, wxEXPAND | wxTOP, 10);
    sizer4->Add(ScrollBarBrightness, 0, wxEXPAND | wxTOP, 10);
    loadedBackgroundLabel->Hide();
    ScrollBarBrightness->Hide();

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

    Bind(wxEVT_MENU, &MainFrame::fun_saveAnimationFile, this, ID_saveFile);
    Bind(wxEVT_MENU, &MainFrame::fun_loadAnimationFile, this, ID_loadFile);
    Bind(wxEVT_MENU, &MainFrame::newProject, this, ID_newProject);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, ID_exit);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, ID_about);
    Bind(wxEVT_CHECKBOX, &MainFrame::OnFillCheckBoxChanged, this, ID_checkbox);
    Bind(wxEVT_CHECKBOX, &MainFrame::fun_copyPrevFrame, this, ID_copyPrevFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_loadImage, this, ID_loadImage);
    Bind(wxEVT_BUTTON, &MainFrame::fun_addFrame, this, ID_addFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_delFrame, this, ID_delFrame);
    Bind(wxEVT_BUTTON, &MainFrame::fun_delShape, this, ID_delLastShape);
    Bind(wxEVT_BUTTON, &MainFrame::DeleteAllData, this, ID_delAll);
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

    if (saveFileDialog.ShowModal() == wxID_OK)
        _myPanel->cfg->saveFramesToFile(saveFileDialog.GetPath());
}
void MainFrame::fun_loadAnimationFile(wxCommandEvent& e) {
    wxFileDialog openFileDialog(this, _("Open animation file"), "", "",
        "Image files (*.anim)|*.anim", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK)
        _myPanel->cfg->loadFramesFromFile(openFileDialog.GetPath());

    _myPanel->Refresh();
}
void MainFrame::newProject(wxCommandEvent& e) {

}

void MainFrame::fun_loadImage(wxCommandEvent& e) {
    loadedBackgroundLabel->Show();
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

void MainFrame::fun_delShape(wxCommandEvent& e) {
    _myPanel->cfg->deleteLastShape();
    _myPanel->Refresh();
}

void  MainFrame::fun_nextFrame(wxCommandEvent& e) {
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
    if (copyPrevFrame->GetValue())
        std::cout << "User wants to copy previous frame!\n";
}

void MainFrame::OnExit(wxCommandEvent& e)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& e)
{
    wxMessageBox("This application, named Stop Motion, is a computer graphics project created by Daniel Czapla, Bartlomiej Obrochta, and Franciszek Urbanski.\n The project allows adding and removing new shapes available on the drawing panel. Drawing is done by selecting two points on the panel, choosing a shape, its color and filling it with another one. It is possible to delete the last added shapes, load your own background, add(delete) frames and play frames as an animation.",
        "About Stop Motion", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnClose(wxCloseEvent& e)
{
    int answer = wxMessageBox("Are you sure you want to exit?", "Confirm Exit", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    if (answer == wxYES)
        e.Skip();
    else
        e.Veto();
}


void MainFrame::DeleteAllData(wxCommandEvent& e) {
    std::cout << "Implement logic for clearing all data\n";
}