#include "Ukulele.h"

Ukulele::Ukulele() {
  // Initialise each string (servo + electro-magnets)
  for (int i = 0; i < STRING_COUNT; i++) {
    _strings[i] = new UkuleleString(SERVO_PINS[i], MCP_ADDRESSES[i],OPEN_STRING_NOTE[i]);
  }
  // Initialise the servo for height/velocity/force plucking control
  servoVelocity.attach(SERVO_VELOCITY_PIN);
  servoVelocity.write(INIT_ANGLE_VELOCITY);
}

void Ukulele::playMidiNote(int midiNote, int velocity) {
  int stringIndex = findString(midiNote);
  if (stringIndex != -1) { // If the note can be played
    setVelocity(velocity);
    _strings[stringIndex]->playNote(midiNote, true);
  }
}

void Ukulele::stopMidiNote(int midiNote) {
  for (int i = 0; i < STRING_COUNT; i++) {
    if (_strings[i]->getCurrentMidiNote() == midiNote) {
      _strings[i]->playNote(midiNote, false);
      break;
    }
  }
}

int Ukulele::findString(int midiNote) {
  for (int i = 0; i < STRING_COUNT; i++) {
    if (_strings[i]->isPlayable(midiNote)){
      return i;
    }
  }
  return -1; // Return -1 if no string can play the note
}

void Ukulele::setVelocity(int velocity) {
  int angle = map(velocity, 0, 127, SERVO_VELOCITY_MIN, SERVO_VELOCITY_MAX);
  servoVelocity.write(angle);
}
