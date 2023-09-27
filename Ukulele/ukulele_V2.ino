#include "settings.h"
#include "ukulele.h"
#include "midiHandler.h"
#include "Arduino.h"

Ukulele* ukulele = nullptr;
MidiHandler* midiHandler = nullptr;

void setup() {
    Serial.begin(115200);
  
  while (!Serial) {
   delay(10); // Attendre que la connexion série soit établie
  }
    Serial.println("setup main UKULELE MIDI USB");
    //initialise les objets pour avoir les info de debuggage
    ukulele = new Ukulele();
    midiHandler = new MidiHandler(*ukulele);
    // test cordes => servo plus 1ere frette
    //ukulele->initMusic();
}

void loop() {
  midiHandler->readMidi(); // gestion des messages midi
  ukulele->update(); // gestion extinction electroaiamants / temps maximum actif
}
