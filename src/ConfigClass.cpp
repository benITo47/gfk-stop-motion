//
// Created by Bartłomiej Obrochta on 24/05/2024.
//


#pragma warning(disable: 4996) // Visual Studio: warning C4996: 'XXX': This function or variable may be unsafe. <- wxcrt.h
#include <fstream>
#include "ConfigClass.h"



ConfigClass::ConfigClass():_firstPoint(wxPoint(0,0)), _secondPoint(wxPoint(0,0)), _type("Line"), _borderColour(0,0,0), _fillColour(0,0,0), _isFilled(false), _frameIterator(0)
{
    _frames.emplace_back();
}

void ConfigClass::saveShape()
{
    _frames[_frameIterator].emplace_back( _firstPoint, _secondPoint,_type,_borderColour, _isFilled, _fillColour);
}

void ConfigClass::addFrame() {
    if (_frameIterator < _frames.size() - 1) {
        _frames.insert(_frames.begin() + _frameIterator + 1, std::vector<Shape>());
    } else {
        _frames.emplace_back();
    }
    _frameIterator++;
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
    } else if (_frameIterator >= _frames.size()) {
        // Adjust iterator if it goes out of bounds
        _frameIterator = _frames.size() - 1;
    }
}

void ConfigClass::nextFrame() {
    if (_frameIterator < _frames.size() - 1) {
        _frameIterator++;
    }
    else
    {
        wxBell();
    }
}

void ConfigClass::previousFrame() {
    if (_frameIterator > 0) {
        _frameIterator--;
    }
    else
    {
        wxBell();
    }
}

void ConfigClass::setPoint1(const wxPoint& p1) { _firstPoint = p1; }
wxPoint ConfigClass::getPoint1() const { return _firstPoint; }

void ConfigClass::setPoint2(const wxPoint& p2) { _secondPoint = p2; }
wxPoint ConfigClass::getPoint2() const { return _secondPoint; }

void ConfigClass::setType(wxString type){_type = type;}
wxString ConfigClass::getType(){return _type;}

void ConfigClass::setBorderColour(wxColour borderColor){ _borderColour = borderColor;}
wxColour ConfigClass::getBorderColour(){return _borderColour;}

void ConfigClass::setFillColour(wxColour fillColour){_fillColour = fillColour;}
wxColour ConfigClass::getFillColour(){return _fillColour;}

void ConfigClass::setIsFilled(bool filled){_isFilled = filled;}
bool ConfigClass::getIsFilled(){return _isFilled;}

void ConfigClass::setBackgroundBitmap(const wxBitmap& bitmap){_backgroundBitmap = wxBitmap(bitmap);}
wxBitmap ConfigClass::getBackgroundBitmap(){return _backgroundBitmap;}

void ConfigClass::setBackgroundPath(wxString path){_backgroundPath = path;}
wxString ConfigClass::getBackgroundPath(){return _backgroundPath;}

void ConfigClass::setCurrentFrame(std::vector<Shape> frame){_frames[_frameIterator] = frame;}
std::vector<Shape> ConfigClass::getCurrentFrame(){return  _frames[_frameIterator];}
