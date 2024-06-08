//
// Created by Bartłomiej Obrochta on 24/05/2024.
//


#pragma warning(disable: 4996) // Visual Studio: warning C4996: 'XXX': This function or variable may be unsafe. <- wxcrt.h
#include "ConfigClass.h"
#include "Frame.h"
#include "Parser.h"
#include <wx/filename.h>

ConfigClass::ConfigClass() :_firstPoint(wxPoint(0, 0)), _secondPoint(wxPoint(0, 0)), _type("Line"), _borderColour(0, 0, 0), _fillColour(0, 0, 0), _isFilled(true), _backgroundLayer(wxBitmap(1200, 900, 32)), _middleLayer(wxBitmap(1200, 900, 32)), _currentLayer(wxBitmap(1200, 900, 32)), _middleOpacity(20), _backgroundBirghtness(100), _frameIterator(0)
{

	_middleLayer.UseAlpha(true);
	_currentLayer.UseAlpha(true);

	_frames.emplace_back();
	prepareBackgroundLayer();
}

void ConfigClass::saveShape()
{
	_frames[_frameIterator].addShape(_firstPoint, _secondPoint, _type, _borderColour, _isFilled, _fillColour);
	prepareCurrentLayer();
}

void ConfigClass::addFrame(bool copyFrame, bool copyBackground) {

	if (_frameIterator < _frames.size() - 1) {
		_frames.insert(_frames.begin() + _frameIterator + 1, Frame());
	}
	else {
		_frames.emplace_back();
	}
	_frameIterator++;

	if (copyFrame)
	{
		auto previousShapes = _frames[_frameIterator - 1].getShapes();
		_frames[_frameIterator].setShapes(previousShapes);
	}
	if (copyBackground)
	{
		auto previousBgPath = _frames[_frameIterator - 1].getBgPath();
		auto previousBitmap = _frames[_frameIterator - 1].getBitmap();
		_frames[_frameIterator].setBgPath(previousBgPath);
		//It copies the loaded bitmap instead of loading it again - dunno if it improves performance but i think it should?
		_frames[_frameIterator].setBitmap(previousBitmap);

	}
	prepareBitmaps();
}

void ConfigClass::addFrame() {
	if (_frameIterator < _frames.size() - 1) {
		_frames.insert(_frames.begin() + _frameIterator + 1, Frame());
	}
	else {
		_frames.emplace_back();
	}
	_frameIterator++;
	prepareBitmaps();
}




void ConfigClass::deleteFrame()
{
	if (_frames.empty()) {
		return; // No frames to delete
	}

	_frames.erase(_frames.begin() + _frameIterator);
	_frameIterator--;
	if (_frames.empty()) {
		wxBell();
		_frames.emplace_back();
		_frameIterator = 0;
	}
	else if (_frameIterator >= _frames.size()) {
		// Adjust iterator if it goes out of bounds
		_frameIterator = _frames.size() - 1;
	}
	prepareBitmaps();
}

void ConfigClass::deleteLastShape()
{
	_frames[_frameIterator].popLastShape();
	prepareCurrentLayer();
}



void ConfigClass::nextFrame() {
	if (_frameIterator < _frames.size() - 1) {
		_frameIterator++;
	}
	else
	{
		wxBell();
	}
	prepareBitmaps();
}

void ConfigClass::previousFrame() {
	if (_frameIterator > 0) {
		_frameIterator--;
	}
	else
	{
		wxBell();
	}
	prepareBitmaps();
}

/// @brief Temporary function for transforming into frame class
/*static std::vector<Frame> asFrameVec(wxString path, std::vector<Frame> frames) {
	std::vector<Frame> result(frames.size());
	std::transform(frames.begin(), frames.end(), result.begin(),
		[path](std::vector<Shape> shapes) { return Frame(path, shapes); });
	return result;
}*/

void ConfigClass::copyImagesToProjectDirectory(const wxString& projectDirectory, const wxString& animName) {
	// Ensure the img directory exists
	wxString imgDirectory = projectDirectory + "/img";
	if (!wxFileName::DirExists(imgDirectory)) {
		if (!wxFileName::Mkdir(imgDirectory, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
			throw std::runtime_error("Couldn't create directory " + imgDirectory.ToStdString());
		}
	}

	for (size_t i = 0; i < _frames.size(); i++) {
		const wxString& path = _frames[i].getBgPath();
		wxString newPath = projectDirectory + wxString::Format("/img/%s%08zu.jpg", animName, i);

		if (!_frames[i].getBitmap().SaveFile(newPath, wxBITMAP_TYPE_JPEG))
			throw std::runtime_error("Couldn't save bitmap to " + newPath);

		_frames[i].setBgPath(newPath);
	}
}

void ConfigClass::loadFramesFromFile(const wxString& path) {
	Parser p;
	p.readFile(path);
	auto frames = p.getFrames();

	_frames.clear();
	for (auto& elem : frames)
	{
		elem.loadBitmap();
		_frames.push_back(elem);
	}
	_frameIterator = 0;
}

void ConfigClass::saveFramesToFile(const wxString& path) {
	//std::vector<Frame> frames = asFrameVec(_backgroundPath, _frames);

	copyImagesToProjectDirectory(path.BeforeLast('/'), path.AfterLast('/').BeforeLast('.'));

	Parser p;
	p.setFrames(_frames);
	p.saveToFile(path);
}




void ConfigClass::setPoint1(const wxPoint& p1) { _firstPoint = p1; }
wxPoint ConfigClass::getPoint1() const { return _firstPoint; }

void ConfigClass::setPoint2(const wxPoint& p2) { _secondPoint = p2; }
wxPoint ConfigClass::getPoint2() const { return _secondPoint; }

void ConfigClass::setType(wxString type) { _type = type; }
wxString ConfigClass::getType() { return _type; }

void ConfigClass::setBorderColour(wxColour borderColor) { _borderColour = borderColor; }
wxColour ConfigClass::getBorderColour() { return _borderColour; }

void ConfigClass::setFillColour(wxColour fillColour) { _fillColour = fillColour; }
wxColour ConfigClass::getFillColour() { return _fillColour; }

void ConfigClass::setIsFilled(bool filled) { _isFilled = filled; }
bool ConfigClass::getIsFilled() { return _isFilled; }


//void ConfigClass::setCurrentFrame(Frame frame) { _frames[_frameIterator].setShapes(frame.getShapes()); }
Frame ConfigClass::getCurrentFrame() { return  _frames[_frameIterator]; }


int ConfigClass::getFrameNumber() { return _frames.size(); }

void ConfigClass::setFrameIterator(int iterator) {
	if (iterator < _frames.size())
		_frameIterator = iterator;
}


void ConfigClass::setBrightness(int pos) { _backgroundBirghtness = pos; prepareBackgroundLayer(); }
int ConfigClass::getBrightness() { return _backgroundBirghtness; }

void ConfigClass::setOpacity(int pos) { _middleOpacity = pos; prepareMiddleLayer(); }
int ConfigClass::getOpacity() { return _middleOpacity; }



void ConfigClass::prepareBitmaps()
{
	prepareBackgroundLayer();

	prepareMiddleLayer();

	prepareCurrentLayer();
}



void ConfigClass::prepareBackgroundLayer()
{
	_backgroundLayer = _frames[_frameIterator].getBitmap();
	RescaleBackground();
	AdjustBackgroundBrightness();
}

//Helper function;
int clamp(int value, int min, int max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

void ConfigClass::RescaleBackground()
{
	int panelWidth = 1200;
	int panelHeight = 900;
	if (_backgroundLayer.IsOk()) {
		int bitmapWidth = _backgroundLayer.GetWidth();
		int bitmapHeight = _backgroundLayer.GetHeight();

		double bitmapAspectRatio = static_cast<double>(bitmapWidth) / bitmapHeight;
		double panelAspectRatio = static_cast<double>(panelWidth) / panelHeight;

		if (bitmapAspectRatio > panelAspectRatio) {
			// Image is wider relative to the panel
			bitmapWidth = panelWidth;
			bitmapHeight = static_cast<int>(panelWidth / bitmapAspectRatio);
		}
		else {
			// Image is taller relative to the panel
			bitmapHeight = panelHeight;
			bitmapWidth = static_cast<int>(panelHeight * bitmapAspectRatio);
		}


		wxImage image = _backgroundLayer.ConvertToImage();
		image.Rescale(bitmapWidth, bitmapHeight, wxIMAGE_QUALITY_HIGH);
		_backgroundLayer = wxBitmap(image);
	}
}

void ConfigClass::AdjustBackgroundBrightness()
{
	double s = _backgroundBirghtness / 100.0;
	if (_backgroundLayer.IsOk()) {
		wxImage image = _backgroundLayer.ConvertToImage();
		unsigned char* data = image.GetData();
		int pixelCount = image.GetWidth() * image.GetHeight();

		for (int i = 0; i < pixelCount; ++i) {
			int r = data[i * 3];
			int g = data[i * 3 + 1];
			int b = data[i * 3 + 2];

			r = clamp(r + (s - 1) * 255, 0, 255);
			g = clamp(g + (s - 1) * 255, 0, 255);
			b = clamp(b + (s - 1) * 255, 0, 255);

			data[i * 3] = r;
			data[i * 3 + 1] = g;
			data[i * 3 + 2] = b;
		}
		_backgroundLayer = wxBitmap(image);
	}
}


void ConfigClass::AdjustMiddleOpacity()
{
	if (_middleOpacity < 0) _middleOpacity = 0;
	if (_middleOpacity > 100) _middleOpacity = 100;

	unsigned char alphaValue = static_cast<unsigned char>(_middleOpacity * 2.55); // Convert 0-100 to 0-255

	wxImage image = _middleLayer.ConvertToImage();
	if (!image.HasAlpha())
	{
		image.InitAlpha();
	}

	int width = image.GetWidth();
	int height = image.GetHeight();

	// Loop through each pixel
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// Only modify the alpha value if the pixel is not fully transparent
			if (image.GetAlpha(x, y) != 0)
			{
				image.SetAlpha(x, y, alphaValue);
			}
		}
	}
	_middleLayer = wxBitmap(image);
}

void ConfigClass::prepareMiddleLayer()
{
	_middleLayer = wxBitmap(1200, 900, 32);
	_middleLayer.UseAlpha(true);

	wxMemoryDC memDC;
	memDC.SelectObject(_middleLayer);
	memDC.SetBackground(*wxTRANSPARENT_BRUSH);
	memDC.Clear();

	auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(memDC));

	if (_frameIterator > 0 && _frames.size() > 1)
	{
		for (auto& elem : _frames[_frameIterator - 1].getShapes())
		{
			elem.drawShape(gc);
		}

		AdjustMiddleOpacity();
	}
	memDC.SelectObject(wxNullBitmap);

}

void ConfigClass::prepareCurrentLayer()
{

	_currentLayer = wxBitmap(1200, 900, 32);
	_currentLayer.UseAlpha(true);

	wxMemoryDC memDC;
	memDC.SelectObject(_currentLayer);
	memDC.SetBackground(*wxTRANSPARENT_BRUSH);
	memDC.Clear();

	auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(memDC));

	for (auto& elem : _frames[_frameIterator].getShapes())
	{
		elem.drawShape(gc);
	}
	memDC.SelectObject(wxNullBitmap);
}