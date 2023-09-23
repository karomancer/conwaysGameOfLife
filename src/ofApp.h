#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofxButton resetButton;
        ofParameter<bool> isPlaying;
        ofxIntSlider pixelSize;
        ofxIntSlider speed;
            
        ofxButton takePhotoButton;
        ofVideoGrabber grabber;
    
        ofImage gameBoardImg;
        ofPixels gameBoard;
    
        float dead = 0.f;
        float alive = 255.f;
        int threshold = 140;
    
        //---- Standards Methods ----//
		void setup() override;
		void update() override;
		void draw() override;
    
        //---- Game of Life methods ----//
        void generateSeed();
        void takePhoto();
        void setPixelColor(int x, int y, float color);
        float nextPixelState(int x, int y);
        int* findNeighbors(int pixelIndex);            
};
    
