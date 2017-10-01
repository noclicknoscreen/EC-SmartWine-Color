#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define HOST "192.168.2.33"
#define PORT 6666

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory dir;
    ofxSyphonClient client;
    int dirIdx;
    
    ofImage myScreen;
    
    // GUI
    ofParameter<ofColor>  vv8Color;
    
    ofParameter<bool>       Auto;
    
    ofParameter<float>      Period;
    ofParameter<int>        grabX;
    ofParameter<int>        grabY;

    ofParameterGroup parameters;
    ofxPanel gui;
    
    ofxOscSender sender;
    
};
