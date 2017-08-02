//
//  EC-SmartWine-Serial.cpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#include "EC-SmartWine-Serial.h"

void EC_SmartWine_Serial::setup(){
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    //serial.setup(0, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    serial.setup("/dev/tty.usbserial", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    memset(bytesReadString, 0, 4);
    
}

bool EC_SmartWine_Serial::isInitialized(){
    return serial.isInitialized();
}

// Main base function to send
void EC_SmartWine_Serial::send(string _msg){
    m_lastSent = _msg;
    
    for(int idxChar = 0; idxChar < _msg.length(); idxChar++){
        
        char c = _msg[idxChar];
        ofLogVerbose() << "Char sent : as string [" << c << "] : HEX [" << ofToString(ofToHex(c)) << "]";
        
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
    msg += "@LED_R_";
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getTermination();
    //msg += (char)Ox0A;
    
    send(msg);
    
    ofLogNotice() << "Robinets color [r,g,b] : [" << getColorString(_color) << "]";
}
void EC_SmartWine_Serial::sendLeftBottles(ofColor _color){
    //"@LED_B_G_"
    string msg;
    msg += "@LED_B_G_";
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getTermination();
    
    send(msg);
    
    ofLogNotice() << "Left bottles color [r,g,b] : [" <<  getColorString(_color) << "]";
}
void EC_SmartWine_Serial::sendRightBottles(ofColor _color){
    //"@LED_B_D_"
    string msg;
    msg += "@LED_B_D_";
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getColorString(_color);
    msg += getTermination();
    
    send(msg);
    
    ofLogNotice() << "Right bottles color [r,g,b] : [" <<  getColorString(_color) << "]";
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

