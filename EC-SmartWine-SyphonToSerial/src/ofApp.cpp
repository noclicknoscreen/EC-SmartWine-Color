#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxSyphonServerDirectoryExample");
    ofSetWindowShape(800, 600);
    ofSetFrameRate(60);
    
    //setup our directory
    dir.setup();
    //setup our client
    client.setup();
    
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    // not yet implemented
    //ofAddListener(dir.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    
    dirIdx = -1;
    
    myScreen.allocate(50, 50, OF_IMAGE_COLOR);
    
    ecSerial.setup();
    
    // GUI Setup
    // events
    gui.setup(); // most of the time you don't need a name
    gui.setPosition(10, 150);
    gui.add(Inited.set("Inited", false));
    gui.add(vv8Color.set("vv8 Color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(Auto.set("Auto", true));
    gui.add(Period.set("Auto. period", 10000, 50, 20000));
    gui.add(grabX.set("grabX", 0, 0, ofGetWidth()));
    gui.add(grabY.set("grabY", 0, 0, ofGetHeight()));
    
}

//these are our directory's callbacks
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // get the initialization status
    Inited = ecSerial.isInitialized();
    
    if(Inited == true){
        
        // Eventually send
        if(Auto == true /*&& (ofGetFrameNum() % 10 == 0)*/){
            ofColor autoColor;
            autoColor.setBrightness(255);
            autoColor.setSaturation(255);
            
            float hue = fmod(ofGetElapsedTimeMillis(), Period);
            hue /= Period;
            
            autoColor.setHue(255 * hue);
            vv8Color = autoColor;
        }
        
        if(ofGetFrameNum() % 2 == 0){
            // Sending All
            ofLogVerbose() << "Update sent !";
            ecSerial.sendGeneral(vv8Color);
        }
        
        // Then Eventually read
        ecSerial.readAllAwaiting();
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw Syphon and grab pixels ----------------------------------
    if(dir.isValidIndex(dirIdx)){
        client.draw(0, 0);
    }
    myScreen.grabScreen(grabX, grabY, 100, 100);
    vv8Color = myScreen.getColor(0.5 * myScreen.getWidth(), 0.5 * myScreen.getHeight());
    
    // Draw waht we grab -------------------------------------------
    ofPushMatrix();
    ofTranslate(250, 200);
    
        myScreen.draw(0, 0, myScreen.getWidth(), myScreen.getHeight());
    
        ofPushStyle();
            ofNoFill();
            ofSetLineWidth(5);
            ofSetColor(ofColor::white);
            ofDrawRectangle(0, 0, myScreen.getWidth(), myScreen.getHeight());
        ofPopStyle();
    
    ofPopMatrix();
    
    // Draw sliders ---------------------------------------------------
    gui.draw();

    // Draw messages
    string drawMsg;
    
    // Draw what we send
    drawMsg += "Last Send ";
    drawMsg += "[";
    drawMsg += ecSerial.lastSentTime();
    drawMsg += "]";
    drawMsg += " : [";
    drawMsg += ecSerial.lastSent();
    drawMsg += "]";
    
    ofDrawBitmapString(drawMsg, 10, 400);
    
    // and Draw what we read
    drawMsg = "";
    drawMsg += "Last read ";
    drawMsg += "[";
    drawMsg += ecSerial.lastReadTime();
    drawMsg += "]";
    drawMsg += " : [";
    drawMsg += ecSerial.lastRead();
    drawMsg += "]";
    
    ofDrawBitmapString(drawMsg, 10, 425);

    // Draw Witness of serial reception -----------------------------------------------------
    ofPushMatrix();
    ofTranslate(500, 250);
        ecSerial.draw();
    ofPopMatrix();
    
    
    
    
    ofDrawBitmapString("Press any key to cycle through all available Syphon servers.", ofPoint(20, 580));
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //press any key to move through all available Syphon servers
    if (dir.size() > 0)
    {
        dirIdx++;
        if(dirIdx > dir.size() - 1)
            dirIdx = 0;
        
        client.set(dir.getDescription(dirIdx));
        string serverName = client.getServerName();
        string appName = client.getApplicationName();
        
        if(serverName == ""){
            serverName = "null";
        }
        if(appName == ""){
            appName = "null";
        }
        ofSetWindowTitle(serverName + ":" + appName);
    }
    else
    {
        ofSetWindowTitle("No Server");
    }
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
