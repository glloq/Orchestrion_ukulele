#include "ukuleleString.h"
#include "Arduino.h"
#include "mcpDevices.h"

UkuleleString::UkuleleString(int servoPin, int baseMidiNote, int numFrets, int angle, const FretMapping* fretMapping)
    : baseMidiNote(baseMidiNote), numFrets(numFrets), angleZero(angle), fretMapping(fretMapping)
{
    if (DEBUG) {
        Serial.println("ukuleleString--creation objet UkuleleString");
    }
    
    // Initialisation des sorties pour chaque frette
    for (int i = 0; i < numFrets; i++) {
        uint8_t mcpIdx = fretMapping[i].mcpIndex;
        uint8_t pin = fretMapping[i].pin;
        mcpDevices[mcpIdx].pinMode(pin, OUTPUT);
        active[i] = false;
        extinctionTime[i] = 0;
    }
    
    playing = false;
    servoMovingToA = true;
    currentMidiNote = -1;
    
    // Initialisation du servo
    servo.attach(servoPin);
    servo.write(angleZero - ANGLE_GRATTAGE);
    delay(1000);
    servo.write(angleZero);
}

void UkuleleString::playNote(int note, bool isNoteOn) {
    int fretIndex = note - baseMidiNote; // 0 correspond à la corde à vide
    if (DEBUG) {
        Serial.print("ukuleleString--Note :");
        Serial.print(note);
        Serial.print(" - ");
        Serial.println(isNoteOn ? "on" : "off");
    }
    if (isNoteOn) {
        currentMidiNote = note;
        if (fretIndex == 0) { // open string
            // Enregistrer que la corde est en cours d'utilisation même en open string
            playing = true;  
            pluck();
        } else {
            // Pour une note jouée sur une frette, active le solénoïde correspondant
            activateFret(fretIndex - 1);
            delay(20);
            pluck();
        }
    } else {
        mute();
        if (fretIndex != 0) {
            desactivateFret(fretIndex - 1);
        }
        // Réinitialisation de l'état de la corde
        playing = false;
        currentMidiNote = -1;
    }
}

void UkuleleString::update() {
    if (playing) {
        for (int i = 0; i < numFrets; i++) {
            if (active[i] && millis() > extinctionTime[i]) {
                desactivateFret(i);
            }
        }
    }
}

int UkuleleString::getCurrentMidiNote() {
    return currentMidiNote;
}

bool UkuleleString::isPlayable(int midiNote) {
    if (!playing) {
        if (midiNote >= baseMidiNote && midiNote <= baseMidiNote + numFrets) {
            return true;
        }
    }
    return false;
}

void UkuleleString::activateFret(int fretIndex) {
    uint8_t mcpIdx = fretMapping[fretIndex].mcpIndex;
    uint8_t pin = fretMapping[fretIndex].pin;
    mcpDevices[mcpIdx].digitalWrite(pin, HIGH);
    active[fretIndex] = true;
    extinctionTime[fretIndex] = millis() + MAX_ACTIVATION_TIME;
    playing = true;
}

void UkuleleString::desactivateFret(int fretIndex) {
    uint8_t mcpIdx = fretMapping[fretIndex].mcpIndex;
    uint8_t pin = fretMapping[fretIndex].pin;
    mcpDevices[mcpIdx].digitalWrite(pin, LOW);
    active[fretIndex] = false;
    playing = false;
}

void UkuleleString::pluck() {
    if (servoMovingToA) {
        servoGoToA();
    } else {
        servoGoToB();
    }
    servoMovingToA = !servoMovingToA;
}

void UkuleleString::servoGoToA() {
    servo.write(angleZero + ANGLE_GRATTAGE);
}

void UkuleleString::servoGoToB() {
    servo.write(angleZero - ANGLE_GRATTAGE);
}

void UkuleleString::mute() {
    servo.write(angleZero);
}