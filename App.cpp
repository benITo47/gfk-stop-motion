#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame() : wxFrame(NULL, wxID_ANY, "Stop motion po roku w Rosji", wxDefaultPosition, wxDefaultSize) {}
};

class App : public wxApp {
public:
	bool OnInit() {
#ifdef WIN32
		SetProcessDPIAware();
#endif
		MainFrame* frame = new MainFrame();

		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);