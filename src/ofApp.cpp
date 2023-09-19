#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("controls");
    gui.add(pixelSize.setup("pixelSize", 4, 1, 20));
    gui.add(speed.setup("speed (fps)", 24, 1, 24));
    
    gui.add(resetButton.setup("reset"));
    gui.add(isPlaying.set("isPlaying", true));
    
    resetButton.addListener(this,&ofApp::generateSeed);
    
    gameBoardImg.allocate(ofGetScreenWidth(), ofGetScreenHeight(), OF_IMAGE_GRAYSCALE);
    gameBoard = gameBoardImg.getPixels();
    
    generateSeed();
}

//--------------------------------------------------------------
void ofApp::update(){
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
    gameBoardImg.draw(0, 0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

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
    
//    for (int i = 0; i < gameBoard.size(); i++ ) {
//        float pixelColor = (int)ofRandom(100) % 7 == 0 ? alive : dead;
//        gameBoard[i] = pixelColor;
//    }
    gameBoardImg.setFromPixels(gameBoard);
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
    
    //------------------------------//
    //----- PRINT FOR DEBUGGING ----//
    // Printing is highly inefficient and causes crashing with this many pixels, heads up.
    //------------------------------//
//    cout << "currentPixel: " << pixelIndex << endl << "neighbors: " << endl;
//    for (int n = 0; n < 8; n++) {
//        cout << " " << pixels[n] << ": " << gameBoardImg.getPixels()[pixels[n]] << endl;
//    }
//    cout << endl << endl;
    
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
