//
//  EC-SmartWine-Serial.hpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#pragma once

#include "ofMain.h"

class EC_SmartWine_Serial {
    
    bool		bSendSerialMessage;			// a flag for sending serial
    char		bytesRead[3];				// data from serial, we will be trying to read 3
    char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?
    
    ofSerial	serial;
    
    string      m_lastSent;
    
private:
    string      getColorString(ofColor _color);
    string      getTermination();
    void        send(string _msg);
    
public:
    void setup();
    bool isInitialized();
    
    void sendLeftBottles(ofColor _color);
    void sendRightBottles(ofColor _color);
    void sendRobinets(ofColor _color);
    void sendGeneral(ofColor _color);
    
    string lastSent(){
        return m_lastSent;
    }
    
};
