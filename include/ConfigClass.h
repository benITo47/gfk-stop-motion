//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#ifndef STOP_MOTION_CONFIGCLASS_H
#define STOP_MOTION_CONFIGCLASS_H

#include "MyPanel.h"
#include "Shape.h"


class ConfigClass {
public:

    ConfigClass():_firstPoint(wxPoint(0,0)), _secondPoint(wxPoint(0,0)), _type("Line"), _borderColour(0,0,0), _fillColour(0,0,0), _isFilled(false){}

    void saveShape()
    {
        _currentFrame.emplace_back(_type,_borderColour, _isFilled, _fillColour, _firstPoint, _secondPoint);
    }

    void setPoint1(const wxPoint& p1) { _firstPoint = p1; }
    wxPoint getPoint1() const { return _firstPoint; }

    void setPoint2(const wxPoint& p2) { _secondPoint = p2; }
    wxPoint getPoint2() const { return _secondPoint; }

    void setType(wxString type){_type = type;}
    wxString getType(){return _type;}

    void setBorderColour(wxColour borderColor){ _borderColour = borderColor;}
    wxColour getBorderColour(){return _borderColour;}

    void setFillColour(wxColour fillColour){_fillColour = fillColour;}
    wxColour getFillColour(){return _fillColour;}

    void setIsFilled(bool filled){_isFilled = filled;}
    bool getIsFilled(){return _isFilled;}

    void setBackgroundBitmap(const wxBitmap& bitmap){_backgroundBitmap = wxBitmap(bitmap);}
    wxBitmap getBackgroundBitmap(){return _backgroundBitmap;}

    void setBackgroundPath(wxString path){_backgroundPath = path;}
    wxString getBackgroundPath(){return _backgroundPath;}

    void setCurrentFrame(std::vector<Shape> frame){_currentFrame = frame;}
    std::vector<Shape> getCurrentFrame(){return  _currentFrame;}

private:


    //Blueprint for data - based on those variables, the Shape objects are created and drawn;

    wxPoint _firstPoint;    //First point of the shape
    wxPoint _secondPoint;   //Second point of the shape
    wxString _type;         //Type of the shape  //should be enum  ?
    wxColour _borderColour; //Colour of shape's outline
    wxColour _fillColour;   //Colour of shape's fill
    bool _isFilled;          // Should the shape be filled or transparent

    wxBitmap _backgroundBitmap; //Bitmap used as a background
    wxString _backgroundPath;   //Path to the user loaded bitmap

    std::vector<Shape> _currentFrame;  //Current Frame - "working space"

    std::vector<std::vector<Shape>> _frames;    //Vector of Frames, for saving and playing;
    int _frameIterator; //Iterator over the _frames vector



};



#endif //STOP_MOTION_CONFIGCLASS_H
