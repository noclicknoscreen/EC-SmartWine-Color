//
//  EC-SmartWine-Serial.hpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#pragma once

#include "ofMain.h"

#define EC_MSG_ALL     "@LED_ALL"
#define EC_MSG_R       "@LED_R_"
#define EC_MSG_B_G     "@LED_B_G_"
#define EC_MSG_B_D     "@LED_B_D_"

class EC_SmartWine_Serial {
    
    ofSerial	serial;
    
    string		bytesReadString;			// a string needs a null terminator, so we need 3 + 1 bytes
    string      m_lastSent;
    string      m_lastRead;
    string      m_lastSentTime;
    string      m_lastReadTime;
    
    ofColor     m_colorRobi;
    ofColor     m_colorL_Bottles;
    ofColor     m_colorR_Bottles;
    
private:
    string      getColorString(ofColor _color);
    string      getTermination();
    void        send(string _msg);
    
public:
    void setup();
    void draw();
    bool isInitialized();
    
    void sendLeftBottles(ofColor _color);
    void sendRightBottles(ofColor _color);
    void sendRobinets(ofColor _color);
    void sendGeneral(ofColor _color);
    
    void readAllAwaiting();
    int valueFromMessage(vector<string> messages, int indexRequired);
    
    string lastSent(){
        return m_lastSent;
    }
    string lastRead(){
        return m_lastRead;
    }
    
    string lastSentTime(){
        return m_lastSentTime;
    }
    string lastReadTime(){
        return m_lastReadTime;
    }
    
};
