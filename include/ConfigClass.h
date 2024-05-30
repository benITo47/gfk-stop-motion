//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#ifndef STOP_MOTION_CONFIGCLASS_H
#define STOP_MOTION_CONFIGCLASS_H

#include "MyPanel.h"
#include "Shape.h"


class ConfigClass {
public:

    //Constructor, sets member variables to predefined initial values;
    ConfigClass();

    //Saves currently drawn shape into current working frame (_frames[_frameIterator])
    //Saved shape is based on member variables
    void saveShape();

    //Adds new frame to _frames, without copying the existing data to new frame
    void addFrame() ;

    void addCopyFrame();

    //Deletes the current frame
    void deleteFrame();

    void deleteLastShape(); //Pops back shape from _Frames, it;s no longer drawn.
    //Changes current frame  to next frame
    void nextFrame() ;

    //Changes current frame to previous frame
    void previousFrame();

    //TO BE ADDED
    void loadFramesFromFile();

    //TO BE ADDED
    void saveFramesToFile();

    //MEMBER VARIABLE SETTER AND GETTERS
    //FUNCTION NAMES ARE PRETTY SELF-EXPLANATORY
    //--------------------------------------------------
    void setPoint1(const wxPoint& p1) ;
    wxPoint getPoint1() const ;
    //--------------------------------------------------
    void setPoint2(const wxPoint& p2);
    wxPoint getPoint2() const ;
    //--------------------------------------------------
    void setType(wxString type);
    wxString getType();
    //--------------------------------------------------
    void setBorderColour(wxColour borderColor);
    wxColour getBorderColour();
    //--------------------------------------------------
    void setFillColour(wxColour fillColour);
    wxColour getFillColour();
    //--------------------------------------------------
    void setIsFilled(bool filled);
    bool getIsFilled();
    //--------------------------------------------------
    void setBackgroundBitmap(const wxBitmap& bitmap);
    wxBitmap getBackgroundBitmap();
    //--------------------------------------------------
    void setBackgroundPath(wxString path);
    wxString getBackgroundPath();
    //--------------------------------------------------
    void setCurrentFrame(std::vector<Shape> frame);
    std::vector<Shape> getCurrentFrame();
    //--------------------------------------------------
    int getFrameNumber();
    //--------------------------------------------------
    void setFrameIterator(int iterator);
    //--------------------------------------------------
    void setBackgroundBitmapCopy(const wxBitmap& bitmap);
    wxBitmap getBackgroundBitmapCopy();
    //--------------------------------------------------
    void setThumbPos(int pos);
    int getThumbPos();
    //--------------------------------------------------


private:


    //Blueprint for data - based on those variables, the Shape objects are created and drawn;

    wxPoint _firstPoint;    //First point of the shape
    wxPoint _secondPoint;   //Second point of the shape
    wxString _type;         //Type of the shape  //should be enum  ?
    wxColour _borderColour; //Colour of shape's outline
    wxColour _fillColour;   //Colour of shape's fill
    bool _isFilled;          // Should the shape be filled or transparent

    wxBitmap _backgroundBitmap; //Bitmap used as a background
    wxBitmap _backgroundBitmapCopy;
    wxString _backgroundPath;   //Path to the user loaded bitmap

    std::vector<std::vector<Shape>> _frames;    //Vector of Frames, for saving and playing;
    int _frameIterator;                         //Iterator over the _frames vector

    int _thumbPos = 0;
    //For now unused, as the data handling responsibiites of _currentFrame have been moved to _frames[_frameIterator]



};



#endif //STOP_MOTION_CONFIGCLASS_H
