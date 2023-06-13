#include "UkuleleString.h"

UkuleleString::UkuleleString(int servoPin, uint8_t mcpAddress, int baseMidiNote)
: _servoPin(servoPin), _mcpAddress(mcpAddress), _baseMidiNote(baseMidiNote), _playing(false), _servoMovingToA(false), _numOfNotes(12)
{
    // Initialisation du MCP / electroaiamnt de la corde
    Wire.begin();
    _mcp.begin_I2C(_mcpAddress);

    //init des electroaiamnt pour chaque note /accords sur la corde 
    for(int i=0; i<_numOfNotes;i++){
        _mcp.pinMode(i, OUTPUT);
        _mcp.digitalWrite(i,LOW);
    }
    //init du servomoteur
    _servo.attach(_servoPin);  // attaches the servo on pin servoPin
    //met le pin du servo de grattage a la positon init 
    _servo.write(START_ANGLE);
}

int UkuleleString::getCurrentMidiNote (){
    return _currentMidiNote;
}

void UkuleleString::playNote(int midiNote, bool isNoteOn) {
    // Activation or désactivation de la note
    int McpPin = midiNote-_baseMidiNote;
    //note On
    if(isNoteOn) {
        if (midiNote!=_baseMidiNote){
            _mcp.digitalWrite(McpPin-1, HIGH);
        }
        _playing=true;
        _currentMidiNote = midiNote;
        pluck();
        // Note Off 
    } else {
        if(midiNote!=_baseMidiNote){ // si c'est pas la premiere case a vide 
            _mcp.digitalWrite(McpPin-1, LOW); 
        } 
        _playing=false;
        _currentMidiNote = -1;
    }
}

bool UkuleleString::isPlayable(int MidiNote) {
    if (!_playing && MidiNote >= _baseMidiNote && MidiNote < _baseMidiNote + _numOfNotes) {
        return true;
    }
    return false;
}

void UkuleleString::pluck() { 
    if (_servoMovingToA) {
        _servo.write(END_ANGLE);
        _servoMovingToA = false;
    }else{
        _servo.write(START_ANGLE);
        _servoMovingToA = true;
    }
}
