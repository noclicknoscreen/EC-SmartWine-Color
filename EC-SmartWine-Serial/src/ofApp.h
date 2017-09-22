#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "EC-SmartWine-Serial.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void generalChanged(ofColor & color);
    void robinetsChanged(ofColor & color);
    void leftBottlesChanged(ofColor & color);
    void rightBottlesChanged(ofColor & color);
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // Serial
    EC_SmartWine_Serial ecSerial;
    
    // GUI
    ofParameter<ofColor>  LBottles;
    ofParameter<ofColor>  RBottles;
    ofParameter<ofColor>  Robinets;
    ofParameter<ofColor>  General;
    
    ofParameter<bool>       Inited;
    ofParameter<bool>       Auto;
    
    ofParameter<float>      Period;
    
    ofxPanel gui;
    
};

