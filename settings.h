#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"

// Définition des broches pour les servomoteurs grattage
const int SERVO_PINS[4] = {2, 3, 4, 5};
const int START_ANGLE = 90;
const int END_ANGLE = 100;
const int PAUSE_ANGLE = 95;

//servo velocité/ hauteur de grattage 
const int INIT_ANGLE_VELOCITY =140;
const int SERVO_VELOCITY_MIN=70;
const int SERVO_VELOCITY_MAX=120;
const int SERVO_VELOCITY_PIN=6;

// Définition des adresses I2C pour les MCP23017
const uint8_t MCP_ADDRESSES[4] = {0x20, 0x21, 0x22, 0x23}; // adresse des 4 mcp,  1 par corde par simplicité

const int MAX_ACTIVATION_TIME =5000;// temps max actif pour un electroaimant
const int OPEN_STRING_NOTE[4]= {67, 60, 64, 69}; //base accordage ukulele (numero midi a vide pour les 4 cordes)

#endif
