#include "ukulele.h"
#include "settings.h"

Ukulele:: Ukulele () {
  //initialise chaque cordes (servo + electroaiamants)
  for (int i = 0; i < 4; i++) {
    
        Serial.print("ukulele--creation corde :");
        Serial.println(i);
     
   _strings[i]= new UkuleleString(SERVO_PINS[i], MCP_ADDRESSES[i],OPEN_STRING_NOTE[i],NUM_MAGNET_PER_STRING[i],SERVO_CENTER_ANGLE[i]);

  }
}
  void Ukulele::initMusic(){
     if (DEBUG) {
        Serial.println("ukulele-- init music start serial");
    } 
  for(int i = 0; i < 4; i++) { // Jouer la première note (1ère frette) de la corde pendant 0.5secondes 
   
    _strings[i]->playNote(OPEN_STRING_NOTE[i] + 1, true); // Supposition que getBaseMidiNote() donne la note de la corde à vide et que playNote prend un MIDI Note en paramètre.
    
    delay(500); // attendre 0.5s
    
    // Désactiver la note jouée
    _strings[i]->playNote(OPEN_STRING_NOTE[i] + 1, false);
    
    delay(500); // attendre 0.5s entre les cordes
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



