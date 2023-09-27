#include "settings.h"
#include "ukulele.h"
#include "midiHandler.h"

Ukulele ukulele;
MidiHandler midiHandler(ukulele);

void setup() {
    Serial.println("setup main UKULELE MIDI USB");
}

void loop() {
  midiHandler.readMidi(); // gestion des messages midi
  ukulele.update(); // gestion extinction electroaiamants / temps maximum actif
}
