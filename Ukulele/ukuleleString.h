#ifndef UKULELESTRING_H
#define UKULELESTRING_H

#include "Arduino.h"
#include "Servo.h"
#include "Wire.h"
#include "settings.h"
#include "mcpDevices.h"  // Pour accéder aux mcpDevices globaux

class UkuleleString {
public:
    // Constructeur : reçoit la broche du servo, la note à vide, le nombre de frettes,
    // l'angle central et le tableau de mapping des frettes
    UkuleleString(int servoPin, int baseMidiNote, int numFrets, int angle, const FretMapping* fretMapping);
    
    // Joue ou arrête une note (note = MIDI Note)
    void playNote(int note, bool isNoteOn);
    
    // Mise à jour (désactivation automatique des solénoïdes après le délai max)
    void update();
    
    // Retourne la note MIDI actuellement jouée
    int getCurrentMidiNote();
    
    // Vérifie si la note MIDI peut être jouée sur cette corde
    bool isPlayable(int midiNote);
    
private:
    Servo servo;
    bool playing;
    int angleZero;
    bool servoMovingToA;
    int currentMidiNote;
    int baseMidiNote;
    int numFrets;
    const FretMapping* fretMapping; // Tableau de mapping pour cette corde

    long extinctionTime[9]; // Capacité maximale pour 10 frettes
    bool active[9];

    void activateFret(int fretIndex);
    void desactivateFret(int fretIndex);
    void pluck();
    void mute();
    void servoGoToA();
    void servoGoToB();
};

#endif