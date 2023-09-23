#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("controls");
    gui.add(pixelSize.setup("pixelSize", 4, 1, 20));
    gui.add(speed.setup("speed (fps)", 24, 1, 24));        
    
    gui.add(resetButton.setup("randomize"));
    gui.add(takePhotoButton.setup("take photo"));
    gui.add(isPlaying.set("isPlaying", true));
    
    resetButton.addListener(this,&ofApp::generateSeed);
        
    takePhotoButton.addListener(this,&ofApp::takePhoto);
    
    gameBoardImg.allocate(ofGetScreenWidth(), ofGetScreenHeight(), OF_IMAGE_GRAYSCALE);
    grabber.setup(ofGetScreenWidth(), ofGetScreenHeight());
    gameBoard = gameBoardImg.getPixels();
    
    takePhoto();
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if (isPlaying) {
        ofSetFrameRate(speed);
        for (int y = 0; y < gameBoardImg.getHeight(); y += pixelSize)
        {
          for (int x = 0; x < gameBoardImg.getWidth(); x += pixelSize)
          {
              setPixelColor(x, y, nextPixelState(x, y));
          }
        }
        
        gameBoardImg.setFromPixels(gameBoard);
        gameBoardImg.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    gameBoardImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    gui.draw();
}

//--------------------------------------------------------------
//--------- CUSTOM METHODS FOR CONWAY'S GAME OF LIFE -----------
//--------------------------------------------------------------
void ofApp::generateSeed() {
    // Generating a seed starting configuration
    for (int y = 0; y < gameBoardImg.getHeight(); y += pixelSize)
    {
      for (int x = 0; x < gameBoardImg.getWidth(); x += pixelSize)
      {
          setPixelColor(x, y, ofRandomuf() < 0.5 ? alive : dead);
      }
    }

    gameBoardImg.setFromPixels(gameBoard);
    gameBoardImg.update();
}

void ofApp::takePhoto() {
    ofPixels& grabberPix = grabber.getPixels();
    ofPixels& threshPix = gameBoardImg.getPixels();
    
    for (int y = 0; y < grabberPix.getHeight(); y++) {
        for (int x = 0; x < grabberPix.getWidth(); x++) {
            ofColor color = grabberPix.getColor(x,y);
            
            if (color.getBrightness() > threshold) {
                color = dead;
            } else {
                color = alive;
            }
            
            threshPix.setColor(x, y, color);
        }
    }
    gameBoardImg.update();
}

void ofApp::setPixelColor(int x, int y, float pixelColor) {
    for (int y1 = y; y1 < y + pixelSize; y1++) {
        for (int x1 = x; x1 < x + pixelSize; x1++) {
            gameBoard.setColor(x1, y1, pixelColor);
        }
    }
}

float ofApp::nextPixelState(int x, int y) {
    int numAliveNeighbors = 0;
    ofColor currentPixelState = gameBoardImg.getColor(x, y);
    
    int pixels[8][2] = {
        {x - pixelSize, y - pixelSize}, // top left
        {x, y - pixelSize}, // top center
        {x + pixelSize, y - pixelSize}, // top right
        {x - pixelSize, y}, // center left
        // This is where pixelIndex goes
        {x + pixelSize, y}, // center right
        {x - pixelSize, y + pixelSize}, // bottom left
        {x, y+ pixelSize}, // bottom center
        {x + pixelSize, y+ pixelSize} // bottom right
    };
    
    for (int i = 0; i < 8; i++) {
        // If neighbor pixel is within bounds
        if (pixels[i][0] >= 0 && pixels[i][0] < gameBoard.getWidth() && pixels[i][1] >= 0 && pixels[i][1] < gameBoard.getHeight()) {
            if (gameBoardImg.getColor(pixels[i][0], pixels[i][1]) == alive) {
                numAliveNeighbors++;
            }
        }
    }
    
    // If the pixel is alive
    if (currentPixelState == alive) {
        if (numAliveNeighbors < 2) {
            return dead; // Isolated
        }
            
        if (numAliveNeighbors >= 4) {
            return dead; // Overcrowded
        }
        
        return alive;
    }
        
    // If the pixel is dead
    if (currentPixelState == dead) {
        if (numAliveNeighbors == 3) {
            return alive; // Rebirth
        }
    }
    
    return dead;
}
