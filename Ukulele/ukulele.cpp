#include "ukulele.h"
#include "settings.h"

Ukulele:: Ukulele () {
  //initialise chaque cordes (servo + electroaiamants)
  for (int i = 0; i < 4; i++) {
    this->_strings[i]= new UkuleleString(SERVO_PINS[i], MCP_ADDRESSES[i],OPEN_STRING_NOTE[i],NUM_MAGNET_PER_STRING[i],SERVO_CENTER_ANGLE[i]);
  }
}

void Ukulele::playMidiNote(int midiNote, int velocity) {
  int stringIndex=-1;
  stringIndex=findString(midiNote);

  if (stringIndex != -1 ) {//si la note peut etre jouée
    _strings[stringIndex]->playNote(midiNote, true);
  }
}

void Ukulele::stopMidiNote(int midiNote) {
  for (int i = 0; i < 4; i++) {
    if (_strings[i]->getCurrentMidiNote() == midiNote) {
      _strings[i]->playNote(midiNote, false);
      break;
    }
  }
}


int Ukulele::findString(int midiNote) {
  for (int i = 0; i < 4; i++) {
    if(this->_strings[i]->isPlayable(midiNote)){
      return i;//renvoi la corde jouable
    }
  }
  return -1;//renvoi -1 si pas de corde dispo 
}

//verifie chaque cordes 
void Ukulele::update() {
  for(int i = 0; i < 4; i++) {
    _strings[i]->update();
  }
}



