#include "GUI.h"
#include "ShapeDialog.h"

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Stop motion po roku w Rosji", wxDefaultPosition, wxDefaultSize) {
	_myPanel = new MyPanel(this);
	_myPanel->SetBackgroundColour(*wxWHITE);

	wxButton* _saveFile;
	wxButton* _loadFile;
	wxButton* _addFrame;
	wxButton* _delFrame;
	wxButton* _addShape;
	wxButton* _nextFrame;
	wxButton* _playFrame;
	wxButton* _prevFrame;

	_saveFile = new wxButton(this, ID_saveFile, "SAVE");
	_loadFile = new wxButton(this, ID_loadFile, "LOAD");
	_addFrame = new wxButton(this, ID_addFrame, "ADD FRAME");
	_delFrame = new wxButton(this, ID_delFrame, "DELETE FRAME");
	_addShape = new wxButton(this, ID_addShape, "ADD SHAPE");
	_nextFrame = new wxButton(this, ID_nextFrame, "->");
	_playFrame = new wxButton(this, ID_playFrame, ">");
	_prevFrame = new wxButton(this, ID_prevFrame, "<-");

	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	sizer1->Add(_saveFile, 1, wxEXPAND | wxTOP, 5);
	sizer1->Add(_loadFile, 1, wxEXPAND | wxTOP, 5);

	wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	sizer2->Add(_addFrame, 1, wxEXPAND | wxTOP, 5);
	sizer2->Add(_delFrame, 1, wxEXPAND | wxTOP, 5);

	wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
	sizer3->Add(_addShape, 1, wxEXPAND | wxTOP, 10);

	wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);
	sizer4->Add(_nextFrame, 1, wxEXPAND | wxTOP, 5);
	sizer4->Add(_playFrame, 1, wxEXPAND | wxTOP, 5);
	sizer4->Add(_prevFrame, 1, wxEXPAND | wxTOP, 5);

	wxBoxSizer* sizer0 = new wxBoxSizer(wxVERTICAL);
	sizer0->Add(sizer1, 0, wxEXPAND | wxALL, 5);
	sizer0->Add(sizer2, 0, wxEXPAND | wxALL, 5);
	sizer0->Add(sizer3, 0, wxEXPAND | wxALL, 5);
	sizer0->AddStretchSpacer(); 
	sizer0->Add(sizer4, 0, wxEXPAND | wxALIGN_BOTTOM | wxALL, 5);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(_myPanel, 7, wxEXPAND | wxALL, 5);
	mainSizer->Add(sizer0, 3, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
	SetMinSize(wxSize(800, 600));
	Centre();

	Bind(wxEVT_BUTTON, &MainFrame::fun_saveFile, this, ID_saveFile);
	Bind(wxEVT_BUTTON, &MainFrame::fun_loadFile, this, ID_loadFile);
	Bind(wxEVT_BUTTON, &MainFrame::fun_addFrame, this, ID_addFrame);
	Bind(wxEVT_BUTTON, &MainFrame::fun_delFrame, this, ID_delFrame);
	Bind(wxEVT_BUTTON, &MainFrame::fun_addShape, this, ID_addShape);
	Bind(wxEVT_BUTTON, &MainFrame::fun_nextFrame, this, ID_nextFrame);
	Bind(wxEVT_BUTTON, &MainFrame::fun_playFrame, this, ID_playFrame);
	Bind(wxEVT_BUTTON, &MainFrame::fun_prevFrame, this, ID_prevFrame);
}

void MainFrame::fun_saveFile(wxCommandEvent& e) {
	std::cout << "save file\n";
}
void MainFrame::fun_loadFile(wxCommandEvent& e) {
	std::cout << "load file\n";
}
void MainFrame::fun_addFrame(wxCommandEvent& e) {
	std::cout << "add Frame\n";
	_myPanel->_framesCounter++;
}
void MainFrame::fun_delFrame(wxCommandEvent& e) {
	std::cout << "del Frame\n";
	if (_myPanel->_framesCounter)
		_myPanel->_framesCounter--;
}
void MainFrame::fun_addShape(wxCommandEvent& e) {
	ShapeDialog dlg(this);
	if (dlg.ShowModal() == wxID_OK) {
		wxString shape = dlg.GetSelectedShape();
		wxColour color = dlg.GetSelectedColor();
		bool filled = dlg.IsFilled();

		_myPanel->SetShape(shape,color,filled);
		_myPanel->_currFramesCounter++;

		std::cout << "User chose: "
			<< shape << " " << "Color:" << color.GetRGB() << " " << "filled: " << filled << std::endl;
	}
}
void MainFrame::fun_nextFrame(wxCommandEvent& e) {
	std::cout << "next Frame\n";
}
void MainFrame::fun_playFrame(wxCommandEvent& e) {
	std::cout << "play Frame\n";
}
void MainFrame::fun_prevFrame(wxCommandEvent& e) {
	std::cout << "prev Frame\n";
}