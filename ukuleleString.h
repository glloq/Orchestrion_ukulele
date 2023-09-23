#ifndef UkuleleString_h
#define UkuleleString_h

#include "Arduino.h"
#include "Servo.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"
#include "Note.h"
#include "settings.h"
/***********************************************************************************************
----------------------------  STRING  ----------------------------------------
************************************************************************************************/
class UkuleleString {
public:
    UkuleleString(int servoPin, uint8_t mcpAddress, int baseMidiNote, int numOfNotes, int angle);
    void playNote(int note, bool isNoteOn);
    void update();                    //fct verif temps max actif
    int getCurrentMidiNote();         //renvoi la note midi en cours
    bool isPlayable(int MidiNote);    //fct qui dit si la corde joue une note actuellement

private:
    Servo servo;                       // servo grattage de la corde
    Adafruit_MCP23X17* mcp;            // carte mcp
    Note* notes[12];                   // tableau des nottes/frettes/electroaimants
    bool playing;                      // stoque si une note est en cours sur la corde
    int angleZero;                     // angle servo contre la corde
    bool servoMovingToA;               //
    int currentMidiNote;               // note en cours 
    int baseMidiNote;                  // note corde a vide 
    int numOfNotes;                    //  nombre de notes/frettes/electroaimants sur la corde
    bool isActive();                   // renvoi la valeur de playing
    void activateFret(int numMcp);     // active la frette
    void desactivateFret(int numMcp);  // desactive la frette en cours
    void pluck();                      // gratte la corde
    void mute();
    void servoGoToA();                 // deplacement de A ver B
    void servoGoToB();                 // deplacement de B vers A
};

#endif
