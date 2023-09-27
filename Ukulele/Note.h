#ifndef NOTE_H
#define NOTE_H

#include "settings.h"
#include <Adafruit_MCP23X17.h>
#include <Arduino.h> // For millis()
/***********************************************************************************************
----------------------------  object for each magnets ----------------------------------------
************************************************************************************************/
class Note {
public:
    Note(int pin, Adafruit_MCP23X17* mcp);
    void on();
    void off();
    bool isActive();
    void check(); // to handle timed desactivation
private:
    int _pin;
    Adafruit_MCP23X17* _mcp;
    bool _active;
    long _extinctionTime; 
};

#endif
