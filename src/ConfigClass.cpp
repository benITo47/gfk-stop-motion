//
// Created by Bartłomiej Obrochta on 24/05/2024.
//


#pragma warning(disable: 4996) // Visual Studio: warning C4996: 'XXX': This function or variable may be unsafe. <- wxcrt.h
#include "ConfigClass.h"
#include "Frame.h"
#include "Parser.h"




ConfigClass::ConfigClass() :_firstPoint(wxPoint(0, 0)), _secondPoint(wxPoint(0, 0)), _type("Line"), _borderColour(0, 0, 0), _fillColour(0, 0, 0), _isFilled(false), _middleLayer(wxBitmap(1200,900,32)), _currentLayer(wxBitmap(1200,900,32)), _frameIterator(0)
{
    _middleLayer.UseAlpha(true);
    _currentLayer.UseAlpha(true);

	_frames.emplace_back();
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

    if(copyFrame)
    {
        auto previousShapes = _frames[_frameIterator - 1].getShapes();
        _frames[_frameIterator].setShapes(previousShapes);
    }
    if(copyBackground)
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

void ConfigClass::loadFramesFromFile(const wxString& path) {
	Parser p;
	p.readFile(path);
	auto frames = p.getFrames();

    _frames.clear();
    for(auto& elem : frames)
    {
        elem.loadBitmap();
        _frames.push_back(elem);
    }
    _frameIterator = 0;
    /*
       _backgroundPath = frames[0].getBgPath();

       wxString ext = _backgroundPath.AfterLast('.').Lower();

       wxBitmapType format = wxBITMAP_TYPE_ANY;
       if (ext == "png")
           format = wxBITMAP_TYPE_PNG;
       else if (ext == "jpg" || ext == "jpeg")
           format = wxBITMAP_TYPE_JPEG;
       else if (ext == "bmp")
           format = wxBITMAP_TYPE_BMP;

       wxImage image;
       if (image.LoadFile(_backgroundPath, format)) {
           wxBitmap bitmap(image);
           _backgroundBitmap = bitmap;
           _backgroundBitmapCopy = bitmap;
       }
       else {
           wxLogError("Could not load image file '%s'.", _backgroundPath);
       }

       _frames.clear();
       _frames = frames;

       std::transform(frames.begin(), frames.end(), _frames.begin(),
           [](const Frame& f) { return f.getShapes(); });
   */

}

void ConfigClass::saveFramesToFile(const wxString& path) {
	//std::vector<Frame> frames = asFrameVec(_backgroundPath, _frames);

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


void ConfigClass::setBrightness(int pos) { _backgroundBirghtness = pos; }
int ConfigClass::getBrightness() { return _backgroundBirghtness; }

void ConfigClass::setOpacity(int pos) { _middleOpacity = pos; AdjustMiddleOpacity();}
int ConfigClass::getOpacity() { return _middleOpacity; }



void ConfigClass::prepareBitmaps()
{

    prepareMiddleLayer();

    prepareCurrentLayer();
}


void ConfigClass::AdjustMiddleOpacity()
{
    // Ensure opacity is in the range 0-100
    if (_middleOpacity < 0) _middleOpacity = 0;
    if (_middleOpacity > 100) _middleOpacity = 100;

    unsigned char alphaValue = static_cast<unsigned char>(_middleOpacity * 2.55); // Convert 0-100 to 0-255

    wxImage image = _middleLayer.ConvertToImage();
    unsigned char* alpha = image.GetAlpha();

    if (!alpha)
    {
        image.InitAlpha();
        alpha = image.GetAlpha();
    }

    int size = image.GetWidth() * image.GetHeight();
    for (int i = 0; i < size; ++i)
    {
        alpha[i] = alphaValue;
    }

    _middleLayer = wxBitmap(image);
}

void ConfigClass::prepareMiddleLayer()
{
    _middleLayer = wxBitmap(1200,900,32);
    _middleLayer.UseAlpha(true);

    wxMemoryDC memDC;
    memDC.SelectObject(_middleLayer);
    memDC.SetBackground(*wxTRANSPARENT_BRUSH);
    memDC.Clear();

    if(_frameIterator > 0 && _frames.size() > 1)
    {
        for(auto& elem: _frames[_frameIterator - 1].getShapes())
        {
            elem.drawShape(memDC);
        }

        //AdjustMiddleOpacity();
    }
    memDC.SelectObject(wxNullBitmap);

}

void ConfigClass::prepareCurrentLayer()
{

    _currentLayer = wxBitmap(1200,900,32);
    _currentLayer.UseAlpha(true);

    wxMemoryDC memDC;
    memDC.SelectObject(_currentLayer);
    memDC.SetBackground(*wxTRANSPARENT_BRUSH);
    memDC.Clear();

    for(auto& elem: _frames[_frameIterator].getShapes())
    {
        elem.drawShape(memDC);
    }
    memDC.SelectObject(wxNullBitmap);
}