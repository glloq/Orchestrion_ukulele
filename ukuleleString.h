#ifndef UkuleleString_h
#define UkuleleString_h

#include "settings.h"
#include "Servo.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"

class UkuleleString {
public:
    UkuleleString(int servoPin, uint8_t mcpAddress, int baseMidiNote);
    int getCurrentMidiNote();
    void playNote(int midiNote, bool isNoteOn);
    bool isPlayable(int MidiNote);

private:
    Servo _servo;
    Adafruit_MCP23X17 _mcp;
    int _servoPin, _baseMidiNote, _currentMidiNote, _numOfNotes;
    uint8_t _mcpAddress;
    bool _playing, _servoMovingToA;
    void pluck();
};

#endif
