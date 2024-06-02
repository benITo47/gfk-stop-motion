//
// Created by Bartłomiej Obrochta on 24/05/2024.
//

#ifndef STOP_MOTION_CONFIGCLASS_H
#define STOP_MOTION_CONFIGCLASS_H

#include "MyPanel.h"
#include "Frame.h"
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
    void addFrame(bool copyFrame, bool copyBackground);


    //Deletes the current frame
    void deleteFrame();

    void deleteLastShape(); //Pops back shape from _Frames, it;s no longer drawn.
    //Changes current frame  to next frame
    void nextFrame() ;

    //Changes current frame to previous frame
    void previousFrame();

    void loadFramesFromFile(const wxString& path);
    void saveFramesToFile(const wxString& path);

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


    Frame  getCurrentFrame();
    //--------------------------------------------------
    int getFrameNumber();
    //--------------------------------------------------
    void setFrameIterator(int iterator);


    void loadBackground(wxString filePath)
    {
        _frames[_frameIterator].setBgPath(filePath);
        _frames[_frameIterator].loadBitmap();
        prepareBackgroundLayer();
    }






    void setBrightness(int pos);
    int getBrightness();
    //--------------------------------------------------
    void setOpacity(int pos);
    int getOpacity();


    void prepareBitmaps();

    void prepareBackgroundLayer();
    void AdjustBackgroundBrightness();

    void AdjustMiddleOpacity();

    void prepareMiddleLayer();
    void prepareCurrentLayer();

    wxBitmap getBackgroundBitmap(){return _backgroundLayer;}
    wxBitmap getMiddleBitmap(){return _middleLayer;}
    wxBitmap getCurrentBitmap(){return  _currentLayer;}
private:


    //Blueprint for data - based on those variables, the Shape objects are created and drawn;



    wxPoint _firstPoint;    //First point of the shape
    wxPoint _secondPoint;   //Second point of the shape
    wxString _type;         //Type of the shape  //should be enum  ?
    wxColour _borderColour; //Colour of shape's outline
    wxColour _fillColour;   //Colour of shape's fill
    bool _isFilled;          // Should the shape be filled or transparent

    wxBitmap _backgroundLayer;
    wxBitmap _middleLayer;
    wxBitmap _currentLayer;

    int _backgroundBirghtness;
    int _middleOpacity;


    std::vector<Frame>  _frames;    //Vector of Frames, for saving and playing;
    int _frameIterator;                         //Iterator over the _frames vector




    //For now unused, as the data handling responsibiites of _currentFrame have been moved to _frames[_frameIterator]



};



#endif //STOP_MOTION_CONFIGCLASS_H
