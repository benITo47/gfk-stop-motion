#include "GUI.h"
#include "util.h"
#include <thread>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stop motion po roku w Rosji", wxDefaultPosition, wxDefaultSize) {
	_myPanel = new MyPanel(this);
	_myPanel->SetBackgroundColour(*wxWHITE);

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

	// Toolbar controls start
	wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	scrolledWindow->SetScrollRate(5, 5);

	wxButton* _loadImage;
	wxButton* _addFrame;
	wxButton* _delFrame;
	wxButton* _nextFrame;
	wxButton* _prevFrame;
	wxButton* _delLastShape;
	wxButton* _delAll;

	_loadImage = new wxButton(scrolledWindow, ID_loadImage, "Load background");
	_addFrame = new wxButton(scrolledWindow, ID_addFrame, "Add frame");
	_delFrame = new wxButton(scrolledWindow, ID_delFrame, "Delete frame");
	_delLastShape = new wxButton(scrolledWindow, ID_delLastShape, "Delete last shape");
	_delAll = new wxButton(scrolledWindow, ID_delAll, "Delete all shapes");
	_nextFrame = new wxButton(scrolledWindow, ID_nextFrame, "->");
	_playFrame = new wxButton(scrolledWindow, ID_playFrame, ">");
	_prevFrame = new wxButton(scrolledWindow, ID_prevFrame, "<-");

	_copyPrevFrame = new wxCheckBox(scrolledWindow, ID_copyPrevFrame, "Copy shapes");
	_copyBackground = new wxCheckBox(scrolledWindow, ID_copyPrevBackground, "Copy background");
	_scrollBarBrightness = new wxSlider(scrolledWindow, ID_scrollBarBrightness, 100, 0, 200);

	wxStaticText* transparencyText = new wxStaticText(scrolledWindow, wxID_ANY, "Middle layer opacity", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	_scrollBarTransparent = new wxSlider(scrolledWindow, ID_scrollBarTransparent, 20, 0, 100);
	_loadedBackgroundLabel = new wxStaticText(scrolledWindow, wxID_ANY, "Background brightness", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);


	// Shape panel begin
	_shapePanel = new wxPanel(scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
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
	// Shape panel end

	counterDisplay = new wxStaticText(scrolledWindow, wxID_ANY, "Current frame:\n1/1", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

	wxStaticText* valuePlay = new wxStaticText(scrolledWindow, wxID_ANY, "Animation speed: ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	spinCtrl = new wxSpinCtrlDouble(scrolledWindow, ID_spinCtrl, "100.0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 200, 100, 1);


	// Layout defined here
	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxVERTICAL);

	// Add/remove frame
	wxGridSizer* frameSizer = new wxGridSizer(1, 2, 5, 5);
	frameSizer->Add(_addFrame, 0, wxEXPAND | wxALL, 0);
	frameSizer->Add(_delFrame, 0, wxEXPAND | wxALL, 0);
	toolbarSizer->Add(frameSizer, 0, wxEXPAND | wxALL, 5);

	// Frame adding params
	toolbarSizer->Add(_copyPrevFrame, 0, wxEXPAND | wxALL, 5);
	toolbarSizer->Add(_copyBackground, 0, wxEXPAND | wxALL, 5);

	// Shape panel
	toolbarSizer->Add(_shapePanel, 0, wxEXPAND | wxALL, 5);

	// Shape deletion 
	wxGridSizer* deleteSizer = new wxGridSizer(1, 2, 5, 5);
	deleteSizer->Add(_delLastShape, 0, wxEXPAND | wxALL, 0);
	deleteSizer->Add(_delAll, 0, wxEXPAND | wxALL, 0);
	toolbarSizer->Add(deleteSizer, 0, wxEXPAND | wxALL, 5);

	// Transparency control
	toolbarSizer->Add(transparencyText, 0, wxEXPAND | wxALL, 5);
	toolbarSizer->Add(_scrollBarTransparent, 0, wxEXPAND | wxALL, 5);

	// Background handling
	toolbarSizer->Add(_loadImage, 0, wxEXPAND | wxALL, 5);
	toolbarSizer->Add(_loadedBackgroundLabel, 0, wxEXPAND | wxALL, 5);
	toolbarSizer->Add(_scrollBarBrightness, 0, wxEXPAND | wxALL, 5);

	toolbarSizer->AddStretchSpacer();

	// Animation speed
	toolbarSizer->Add(valuePlay, 0, wxEXPAND, 5);
	toolbarSizer->Add(spinCtrl, 0, wxEXPAND, 5);

	// Animation controls and frame no
	wxGridSizer* animSizer = new wxGridSizer(1, 3, 5, 5);
	animSizer->Add(_prevFrame, 0, wxEXPAND, 0);
	animSizer->Add(_playFrame, 0, wxEXPAND, 0);
	animSizer->Add(_nextFrame, 0, wxEXPAND, 0);
	toolbarSizer->Add(animSizer, 0, wxEXPAND, 5);
	toolbarSizer->Add(counterDisplay, 0, wxALIGN_CENTER, 5);

	scrolledWindow->SetSizer(toolbarSizer);
	toolbarSizer->Fit(scrolledWindow);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(_myPanel, 1, wxEXPAND | wxALL, 0);
	mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 0);

	SetSizerAndFit(mainSizer);

	this->SetInitialSize(wxSize(1700, 950));
	this->SetMinSize(wxSize(1700, 950));
	this->SetMaxSize(wxSize(1700, 950));
	Centre();

	// Bind events
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
	Bind(wxEVT_BUTTON, &MainFrame::deleteAllShapes, this, ID_delAll);
	Bind(wxEVT_BUTTON, &MainFrame::nextFrame, this, ID_nextFrame);
	Bind(wxEVT_BUTTON, &MainFrame::playFrame, this, ID_playFrame);
	Bind(wxEVT_BUTTON, &MainFrame::prevFrame, this, ID_prevFrame);
	Bind(wxEVT_SPINCTRLDOUBLE, &MainFrame::OnSpinCtrl, this, ID_spinCtrl);
	Bind(wxEVT_CHOICE, &MainFrame::updateShapeInPanel, this);
	Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::updateShapeInPanel, this);
	Bind(wxEVT_COLOURPICKER_CHANGED, &MainFrame::updateShapeInPanel, this);

	// Binding all slider events for onScrollBrightness
	Bind(wxEVT_SCROLL_LINEUP, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_LINEDOWN, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_PAGEUP, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_PAGEDOWN, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_THUMBRELEASE, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);
	Bind(wxEVT_SCROLL_CHANGED, &MainFrame::onScrollBrightness, this, ID_scrollBarBrightness);

	// Binding all slider events for onScrollTransparent
	Bind(wxEVT_SCROLL_LINEUP, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_LINEDOWN, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_PAGEUP, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_PAGEDOWN, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_THUMBRELEASE, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
	Bind(wxEVT_SCROLL_CHANGED, &MainFrame::onScrollTransparent, this, ID_scrollBarTransparent);
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

	changeTextCounter();
	_myPanel->Refresh();
}
void MainFrame::newProject(wxCommandEvent& e) {
	int answer = wxMessageBox("Are you sure you want to start new project? Changes won't be saved", "Confirm Reset", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	if (answer == wxYES)
		_myPanel->_cfg->resetProject();

	_myPanel->Refresh();
}

void MainFrame::loadImage(wxCommandEvent& e) {
	_scrollBarBrightness->SetScrollbar(100, 10, 200, 10);
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

	changeTextCounter();
}

void MainFrame::delFrame(wxCommandEvent& e) {
	_myPanel->_cfg->deleteFrame();
	_myPanel->Refresh();

	changeTextCounter();
}

void MainFrame::delShape(wxCommandEvent& e) {
	_myPanel->_cfg->deleteLastShape();
	_myPanel->Refresh();
}

void  MainFrame::nextFrame(wxCommandEvent& e) {
	_myPanel->_cfg->nextFrame();
	_myPanel->Refresh();

	changeTextCounter();
}

void MainFrame::playFrame(wxCommandEvent& e) {

	if (_playFrame->GetLabel() == ">") {
		if (_myPanel->_cfg->getFrameNumber() - 1)
		{
			_playFrame->SetLabel("x");
			_myPanel->stopFlag = false;
			_myPanel->endAnimation = false;
			_myPanel->playAnimation();
		}
	}
	else {
		_playFrame->SetLabel(">");
		_myPanel->stopFlag = true;
		_myPanel->prevAnimation = true;
	}

	if (_myPanel->endAnimation) {
		_playFrame->SetLabel(">");
	}

	changeTextCounter();
}
void MainFrame::prevFrame(wxCommandEvent& e) {
	_myPanel->_cfg->previousFrame();
	_myPanel->Refresh();

	changeTextCounter();
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
	std::cout << _scrollBarBrightness->GetValue() << std::endl;
	_myPanel->_cfg->setBrightness(_scrollBarBrightness->GetValue());
	_myPanel->Refresh();
}

void MainFrame::onScrollTransparent(wxScrollEvent& e) {
	_myPanel->_cfg->setOpacity(_scrollBarTransparent->GetValue());
	_myPanel->Refresh();
}

void MainFrame::copyPrevFrame(wxCommandEvent& e) {
	if (_copyPrevFrame->GetValue())
		std::cout << "User wants to copy previous frame!\n";
}

void MainFrame::onExit(wxCommandEvent& e) {
	wxCloseEvent closeEvent(wxEVT_CLOSE_WINDOW, GetId());
	onClose(closeEvent);
}

void MainFrame::onAbout(wxCommandEvent& e) {
	wxMessageBox("This application, named Stop Motion, is a computer graphics project created by Daniel Czapla, Bartlomiej Obrochta, and Franciszek Urbanski.\n The project allows adding and removing new shapes available on the drawing panel. Drawing is done by selecting two points on the panel, choosing a shape, its color and filling it with another one. It is possible to delete the last added shapes, load your own background, add(delete) frames and play frames as an animation.",
		"About Stop Motion", wxOK | wxICON_INFORMATION);
}

void MainFrame::onClose(wxCloseEvent& e) {
	int answer = wxMessageBox("Are you sure you want to exit?", "Confirm Exit", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	if (answer == wxYES)
		Destroy();
	else
		e.Veto();
}

void MainFrame::deleteAllShapes(wxCommandEvent& e) {
	_myPanel->_cfg->deleteShapes();
	_myPanel->Refresh();
}

void MainFrame::changeTextCounter() {
	wxString s = wxString::Format("Current frame:\n%d/%d", _myPanel->_cfg->getFrameIterator() + 1, _myPanel->_cfg->getFrameNumber());
	counterDisplay->SetLabel(s);
}

void MainFrame::OnSpinCtrl(wxSpinDoubleEvent& e) {
	_myPanel->_cfg->setSpeedAnimation(spinCtrl->GetValue());
}