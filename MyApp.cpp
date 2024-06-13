#include <wx/wx.h>
#include "GUI.h"

class App : public wxApp {
public:
	bool OnInit() {
#ifdef WIN32
		SetProcessDPIAware();
#endif
		MainFrame* frame = new MainFrame();
        wxImage::AddHandler(new wxJPEGHandler);
        wxImage::AddHandler(new wxPNGHandler);

        frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);