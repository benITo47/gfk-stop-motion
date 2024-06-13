#ifndef STOP_MOTION_CONFIGCLASS_H
#define STOP_MOTION_CONFIGCLASS_H

#include "MyPanel.h"
#include "Frame.h"
#include "Shape.h"


class ConfigClass {
public:

    /**
     * @brief Constructor of ConfigClass - initializes all member variables to a neutral state.
     */
    ConfigClass();

    /**
     * @brief Saves the shape object described by member variables onto the current frame.
     *
     * This function saves the shape, which is defined by the current member variables of the
     * ConfigClass, onto the frame that is currently being pointed to by the frame iterator.
     */
    void saveShape();

    /**
     * @brief Adds a new frame.
     * @param copyFrame If true, shapes from the previous frame will be copied to the new frame.
     * @param copyBackground If true, the background from the previous frame will be copied to the new frame.
     *
     * This function creates a new frame. The new frame can optionally copy shapes and/or the background
     * from the previous frame depending on the parameters passed.
     */
    void addFrame(bool copyFrame, bool copyBackground);

    /**
     * @brief Deletes the currently used frame.
     *
     * This function deletes the frame that is currently selected or in use. The frame iterator
     * will be adjusted accordingly to point to a valid frame. If called when only one frame is alive - it will clear it
     * Will call prepareBitmaps() to adjust the drawn bitmaps;
     */
    void deleteFrame();

    /**
   * @brief Deletes the last drawn shape from the current frame.
   *
   * This function removes the most recently drawn shape from the current frame and
   * calls `prepareBitmaps()` to adjust the drawn bitmaps.
   */
    void deleteLastShape();

    /**
     * @brief Moves the iterator to the next frame if possible.
     *
     * If there is a next frame, this function advances the iterator to the next frame and
     * calls `prepareBitmaps()` to adjust the drawn bitmaps.
     */
    void nextFrame();

    /**
     * @brief Moves the iterator to the previous frame if possible.
     *
     * If there is a previous frame, this function moves the iterator to the previous frame and
     * calls `prepareBitmaps()` to adjust the drawn bitmaps.
     */
    void previousFrame();

    /**
     * @brief
     * @param projectDirectory
     * @param animName
     */
    void copyImagesToProjectDirectory(const wxString& projectDirectory, const wxString& animName);

    /**
     * @brief Loads animation from a file.
     * @param path The file path from which to load the animation.
     *
     * This function reads the animation data from the specified file path and
     * loads the frames into the project.
    */
    void loadFramesFromFile(const wxString& path);

    /**
    * @brief Saves animation to a file.
    * @param path The file path to which the animation will be saved.
    *
    * This function writes the current animation data to the specified file path,
    * preserving all frames and their bitmaps.
    */
    void saveFramesToFile(const wxString& path);

    /**
    * @brief Deletes all shapes from the current frame while keeping the background untouched.
    *
    * This function removes all shapes from the current frame. The background remains unchanged.
    * It calls `prepareCurrentLayer()` to adjust the drawn bitmaps.
    */
    void deleteShapes();

    /**
    * @brief Resets the project by clearing all frames.
    *
    *This function removes all frames, effectively resetting the project to its initial state.
    */
    void resetProject();

    /**
    * @brief Loads a bitmap into the current frame using Frame member functions.
    * @param filePath The file path of the bitmap to load.
    *
    * This function serves as a wrapper to load a bitmap into the specified frame.
    * It calls `prepareBackgroundLayer()` to adjust the background layer of the frame.
    */
    void loadBackground(wxString filePath);

    /**
    * @brief Prepares all bitmaps to be drawn.
    *
    * This function prepares the bitmaps for drawing by calling the following functions:
    * - `prepareBackgroundLayer()`
    * - `prepareMiddleLayer()`
    * - `prepareCurrentLayer()`
    */
    void prepareBitmaps();

    /**
    * @brief Prepares the background layer for drawing.
    *
    * This function gets the bitmap of the current frame, rescales it, and adjusts its brightness.
    */
    void prepareBackgroundLayer();

    /**
    * @brief Rescales the background bitmap to fit the panel size while maintaining aspect ratio.
    *
    * This function rescales the background bitmap to fit within a panel of fixed dimensions
    * (1200x900) while maintaining the original aspect ratio of the bitmap.
    */
    void RescaleBackground();

    /**
    * @brief Adjusts the brightness of the background bitmap.
    *
    * This function modifies the brightness of the background bitmap based on the
    * _backgroundBrightness member variable, where 100 represents no change.
    */
    void AdjustBackgroundBrightness();



    /**
    * @brief Adjusts the opacity of the middle layer bitmap.
    *
    * This function modifies the alpha values of the middle layer bitmap based on the
    * _middleOpacity member variable, which ranges from 0 to 100.
    */
    void AdjustMiddleOpacity();

    /**
    * @brief Prepares the middle layer for drawing.
    *
    * This function creates a new bitmap for the middle layer, initializes it with
    * transparency, and draws shapes from the previous frame onto it. It then adjusts
    * the opacity of the middle layer.
    */
    void prepareMiddleLayer();

    /**
    * @brief Prepares the current layer for drawing.
    *
    * This function creates a new bitmap for the current layer, initializes it with
    * transparency, and draws shapes from the current frame onto it.
    */
    void prepareCurrentLayer();


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
    Frame  getCurrentFrame();
    //--------------------------------------------------
    int getFrameNumber();
    //--------------------------------------------------
    void setFrameIterator(int iterator);
    int getFrameIterator();
    //--------------------------------------------------
    void setBrightness(int pos);
    int getBrightness();
    //--------------------------------------------------
    void setOpacity(int pos);
    int getOpacity();
    //--------------------------------------------------
    void setSpeedAnimation(int s);
    int getSpeedAnimation();
    //--------------------------------------------------
    wxBitmap getBackgroundBitmap(){return _backgroundLayer;}
    wxBitmap getMiddleBitmap(){return _middleLayer;}
    wxBitmap getCurrentBitmap(){return  _currentLayer;}
private:


    //Blueprint for data - based on those variables, the Shape objects are created and drawn;
    wxPoint _firstPoint;    //First point of the shape
    wxPoint _secondPoint;   //Second point of the shape
    wxString _type;         //Type of the shape
    wxColour _borderColour; //Colour of shape's outline
    wxColour _fillColour;   //Colour of shape's fill
    bool _isFilled;         // Should the shape be filled or transparent

    //Bitmaps that serve as layers
    wxBitmap _backgroundLayer;
    wxBitmap _middleLayer;
    wxBitmap _currentLayer;

    //Brightness and opacity controls
    int _backgroundBrightness;
    int _middleOpacity;


    std::vector<Frame>  _frames;    //Vector of Frames
    int _frameIterator;             //Iterator over the _frames vector


    int animationSpeed = 100;
};

#endif //STOP_MOTION_CONFIGCLASS_H
