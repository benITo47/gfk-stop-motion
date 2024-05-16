#include <wx/wx.h>
#include "GUI.h"

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

int main(int argc, char* argv[]) {
	App app;
	wxApp::SetInstance(&app);
	wxEntryStart(argc, argv);
	wxTheApp->OnInit();
	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
	return 0;
}