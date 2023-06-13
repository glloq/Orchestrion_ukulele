#include "settings.h"
#include "ukulele.h"
#include "midiHandler.h"

Ukulele ukulele;
MidiHandler midiHandler(ukulele);

void setup() {
    Serial.println("setup main UKULELE MIDI USB");
}

void loop() {
  midiHandler.readMidi();
}
