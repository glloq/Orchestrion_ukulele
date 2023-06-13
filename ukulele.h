#ifndef UKULELE_H
#define UKULELE_H

#include "Arduino.h"
#include "Servo.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"
#include "UkuleleString.h"
#include "settings.h"

#define STRING_COUNT 4

class Ukulele {
public:
  Ukulele();
  void playMidiNote(int midiNote, int velocity);// demande a chaque string si c'est jouable et assigne la note a la premiere corde 
  void stopMidiNote(int midiNote);
private:
  int findString(int midiNote);
  Servo servoVelocity;
  UkuleleString* _strings[STRING_COUNT];
  void setVelocity(int velocity);
};

#endif
