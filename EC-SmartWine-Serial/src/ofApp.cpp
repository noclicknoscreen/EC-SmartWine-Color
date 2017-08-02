#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundGradient(ofColor::darkGray, ofColor::beige);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ecSerial.setup();
    
    // GUI Setup
    // events
    General.addListener(this,&ofApp::generalChanged);
    Robinets.addListener(this,&ofApp::robinetsChanged);
    LBottles.addListener(this,&ofApp::leftBottlesChanged);
    RBottles.addListener(this,&ofApp::rightBottlesChanged);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(Inited.set("Inited", false));
    
    gui.add(General.set("General", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(LBottles.set("Left", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(RBottles.set("Right", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(Robinets.set("Robinets", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    
    gui.add(Auto.set("Auto", false));
    gui.add(Period.set("Auto. period", 1000, 50, 10000));
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // get the initialization status
    Inited = ecSerial.isInitialized();
    
    if(Inited == true){
        
        // Eventually send
        if(Auto == true && (ofGetFrameNum() % 10 == 0)){
            ofColor autoColor;
            autoColor.setBrightness(255);
            autoColor.setSaturation(255);
            
            float hue = fmod(ofGetElapsedTimeMillis(), Period);
            hue /= Period;
            
            autoColor.setHue(255 * hue);
            General = autoColor;
            
            // Sending All
            ecSerial.sendGeneral(General);
        }
        
        // Then Eventually read
        ecSerial.readAllAwaiting();
        
    }
    /*
     if (bSendSerialMessage){
     
     // (1) write the letter "a" to serial:
     //serial.writeByte('a');
     
     // (2) read
     // now we try to read 3 bytes
     // since we might not get them all the time 3 - but sometimes 0, 6, or something else,
     // we will try to read three bytes, as much as we can
     // otherwise, we may have a "lag" if we don't read fast enough
     // or just read three every time. now, we will be sure to
     // read as much as we can in groups of three...
     
     nTimesRead = 0;
     nBytesRead = 0;
     int nRead  = 0;  // a temp variable to keep count per read
     
     unsigned char bytesReturned[3];
     
     memset(bytesReadString, 0, 4);
     memset(bytesReturned, 0, 3);
     
     while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
     nTimesRead++;
     nBytesRead = nRead;
     };
     
     memcpy(bytesReadString, bytesReturned, 3);
     
     bSendSerialMessage = false;
     readTime = ofGetElapsedTimef();
     }
     */
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw sliders
    gui.draw();
    
    ofPushMatrix();
    ofTranslate(250, 100);
    ecSerial.draw();
    ofPopMatrix();
    
    // Draw messages
    string drawMsg;
    
    // Draw what we send
    drawMsg += "Last Send ";
    drawMsg += "[";
    drawMsg += ofToString(ofGetFrameNum());
    drawMsg += "]";
    drawMsg += "[";
    drawMsg += ofGetTimestampString();
    drawMsg += "]";
    
    drawMsg += " : [";
    drawMsg += ecSerial.lastSent();
    drawMsg += "]";
    
    ofDrawBitmapString(drawMsg, 10, ofGetHeight() - 20);
    
    // and Draw what we read
    drawMsg = "";
    drawMsg += "Last read ";
    drawMsg += "[";
    drawMsg += ofToString(ofGetFrameNum());
    drawMsg += "]";
    drawMsg += "[";
    drawMsg += ofGetTimestampString();
    drawMsg += "]";
    
    drawMsg += " : [";
    drawMsg += ecSerial.lastRead();
    drawMsg += "]";
    
    ofDrawBitmapString(drawMsg, 10, ofGetHeight() - 50);

    /*
     if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
     ofSetColor(0);
     } else {
     ofSetColor(220);
     }
     */
}

//--------------------------------------------------------------
void ofApp::generalChanged(ofColor & color){
    ofLogNotice() << "General color changed [r,g,b] : [" << color << "]";
    if(Inited == true){
        ecSerial.sendGeneral(color);
    }
}

//--------------------------------------------------------------
void ofApp::robinetsChanged(ofColor & color){
    ofLogNotice() << "robinets color changed [r,g,b] : [" << color << "]";
    if(Inited == true){
        ecSerial.sendRobinets(color);
    }
}
//--------------------------------------------------------------
void ofApp::leftBottlesChanged(ofColor & color){
    ofLogNotice() << "left bottles color changed [r,g,b] : [" << color << "]";
    if(Inited == true){
        ecSerial.sendLeftBottles(color);
    }
}
//--------------------------------------------------------------
void ofApp::rightBottlesChanged(ofColor & color){
    ofLogNotice() << "right bottles color changed [r,g,b] : [" << color << "]";
    if(Inited == true){
        ecSerial.sendRightBottles(color);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 's'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //bSendSerialMessage = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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

