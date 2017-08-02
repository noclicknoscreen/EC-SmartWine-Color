//
//  EC-SmartWine-Serial.cpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#include "EC-SmartWine-Serial.h"

/*
 Vitesse: 19200 bauds
 Nombre de bits: 8
 Parité; sans
 Nombre se stops: 1
 Contrôle de flux: sans
 */

#define BAUDS 19200

void EC_SmartWine_Serial::setup(){
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    //int baud = 9600;
    //serial.setup(0, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    serial.setup("/dev/tty.usbserial", BAUDS); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
}


void EC_SmartWine_Serial::draw(){
    
    ofSetColor(m_colorRobi);
    ofDrawCircle(0, 0, 25);
    
    ofSetColor(m_colorL_Bottles);
    ofDrawCircle(100, 0, 25);
    
    ofSetColor(m_colorR_Bottles);
    ofDrawCircle(200, 0, 25);
    
}

bool EC_SmartWine_Serial::isInitialized(){
    return serial.isInitialized();
}

// Main base function to send
void EC_SmartWine_Serial::send(string _msg){
    m_lastSent = _msg;
    
    for(int idxChar = 0; idxChar < _msg.length(); idxChar++){
        
        char c = _msg[idxChar];
        ofLogVerbose() << "Char sent : '" << c << "' : HEX [" << ofToString(ofToHex(c)) << "]";
        
        serial.writeByte(c);
        
    }
}

// --------------------------------------------------------------------
// Sending color to all elements (Robinets + Left & Right Bottles)
void EC_SmartWine_Serial::sendGeneral(ofColor _color){
    
    string msg;
    msg += "@LED_ALL";
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getTermination();
    //msg += (char)Ox0A;
    
    send(msg);
    
}
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// Sending color to particular elements
void EC_SmartWine_Serial::sendRobinets(ofColor _color){
    //""
    string msg;
    msg += "@LED_R";
    msg += getColorString(_color);
    msg += getTermination();
    //msg += (char)Ox0A;
    
    send(msg);
    
    ofLogNotice() << "Robinets color [r,g,b] : [" << getColorString(_color) << "]";
}

void EC_SmartWine_Serial::sendLeftBottles(ofColor _color){
    //"@LED_B_G_"
    string msg;
    msg += "@LED_B_G";
    msg += getColorString(_color);
    msg += getTermination();
    
    send(msg);
    
    ofLogNotice() << "Left bottles color [r,g,b] : [" <<  getColorString(_color) << "]";
}
void EC_SmartWine_Serial::sendRightBottles(ofColor _color){
    //"@LED_B_D_"
    string msg;
    msg += "@LED_B_D";
    msg += getColorString(_color);
    msg += getTermination();
    
    send(msg);
    
    ofLogNotice() << "Right bottles color [r,g,b] : [" <<  getColorString(_color) << "]";
}
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// READ SECTION
void EC_SmartWine_Serial::readAllAwaiting(){
    
    char charRead;
    
    if(serial.available() > 0){
        
        while(serial.available() > 0){
            
            charRead = (char)serial.readByte();
            ofLog() << ofGetFrameNum() << " : Char Read '" << charRead << "' HEX [" << ofToString(ofToHex(charRead)) << "]";
            bytesReadString += charRead;
            
            if(charRead == 0x0a){
                // End of instructions --
                m_lastRead = bytesReadString;
                ofLog() << "Frame complete : " << bytesReadString;
                
                if(ofIsStringInString(bytesReadString, "@")){
                    
                    ofLog() << "String Header OK !";
                    
                    vector<string> decodedMessage = ofSplitString(bytesReadString, "_");
                    
                    if(ofIsStringInString(bytesReadString, EC_MSG_ALL)){
                        // Color of robinets is first
                        m_colorRobi.r = ofMap(ofToInt(decodedMessage[2]), 0, 32, 0, 255);
                        m_colorRobi.g = ofMap(ofToInt(decodedMessage[3]), 0, 32, 0, 255);
                        m_colorRobi.b = ofMap(ofToInt(decodedMessage[4]), 0, 32, 0, 255);
                        // Color of robinets is first
                        m_colorL_Bottles.r = ofMap(ofToInt(decodedMessage[5]), 0, 32, 0, 255);
                        m_colorL_Bottles.g = ofMap(ofToInt(decodedMessage[6]), 0, 32, 0, 255);
                        m_colorL_Bottles.b = ofMap(ofToInt(decodedMessage[7]), 0, 32, 0, 255);
                        // Color of robinets is first
                        m_colorR_Bottles.r = ofMap(ofToInt(decodedMessage[8]), 0, 32, 0, 255);
                        m_colorR_Bottles.g = ofMap(ofToInt(decodedMessage[9]), 0, 32, 0, 255);
                        m_colorR_Bottles.b = ofMap(ofToInt(decodedMessage[10]), 0, 32, 0, 255);
                        
                        // Message For controling ALL
                        ofLog() << "ALL Colors received, Color Robi [" << ofToString(m_colorRobi) << "], Color L Bottles [" << ofToString(m_colorL_Bottles) << "], Color R Bottles [" << ofToString(m_colorR_Bottles) << "]";
                        /*
                         m_colorRobi = color;
                         m_colorL_Bottles = color;
                         m_colorR_Bottles = color;
                         */
                    }else if (ofIsStringInString(bytesReadString, EC_MSG_R)){
                        // Color of robinets is first
                        m_colorRobi.r = ofMap(ofToInt(decodedMessage[2]), 0, 32, 0, 255);
                        m_colorRobi.g = ofMap(ofToInt(decodedMessage[3]), 0, 32, 0, 255);
                        m_colorRobi.b = ofMap(ofToInt(decodedMessage[4]), 0, 32, 0, 255);
                        
                        // Message For controling Robinets
                        ofLog() << "ROBINETS received, Color Robi [" << ofToString(m_colorRobi) << "]";
                        
                        
                    }else if (ofIsStringInString(bytesReadString, EC_MSG_B_G)){
                        // Color of robinets is first
                        m_colorL_Bottles.r = ofMap(ofToInt(decodedMessage[3]), 0, 32, 0, 255);
                        m_colorL_Bottles.g = ofMap(ofToInt(decodedMessage[4]), 0, 32, 0, 255);
                        m_colorL_Bottles.b = ofMap(ofToInt(decodedMessage[5]), 0, 32, 0, 255);
                        
                        // Message For controling Left Bottles
                        ofLog() << "LEFT Bottles received, Color L Bottles [" << ofToString(m_colorL_Bottles) << "]";
                        
                    }else if (ofIsStringInString(bytesReadString, EC_MSG_B_D)){
                        // Color of robinets is first
                        m_colorR_Bottles.r = ofMap(ofToInt(decodedMessage[3]), 0, 32, 0, 255);
                        m_colorR_Bottles.g = ofMap(ofToInt(decodedMessage[4]), 0, 32, 0, 255);
                        m_colorR_Bottles.b = ofMap(ofToInt(decodedMessage[5]), 0, 32, 0, 255);
                        
                        // Message For controling Right Bottles
                        ofLog() << "RIGHT Bottles received, Color R Bottles [" << ofToString(m_colorR_Bottles) << "]";
                        
                    }
                }
                
                // Reset Message
                bytesReadString = "";
                
                ofLog() << "Frame EMPTY : " << bytesReadString;
                
            }
        }
    }
}
// --------------------------------------------------------------------


// --------------------------------------------------------------------
string EC_SmartWine_Serial::getColorString(ofColor _color){
    
    int redMapped = ofMap((int)_color.r, 0, 255, 0, 31);
    int greenMapped = ofMap((int)_color.g, 0, 255, 0, 31);
    int blueMapped = ofMap((int)_color.b, 0, 255, 0, 31);
    
    string colorString;
    
    colorString += "_";
    colorString += ofToString(redMapped, 2, '0');
    colorString += "_";
    colorString += ofToString(greenMapped, 2, '0');
    colorString += "_";
    colorString += ofToString(blueMapped, 2, '0');
    
    return colorString;
    
}
// --------------------------------------------------------------------

// --------------------------------------------------------------------
string EC_SmartWine_Serial::getTermination(){
    return "\r\n";
}
// --------------------------------------------------------------------

