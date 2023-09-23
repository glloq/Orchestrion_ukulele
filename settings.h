#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"

#define DEBUG 1

//*********************arduino leonardo
//i2c SDA: pin 2 SDl: pin 3
const int SERVO_PINS[4] = { 9, 10, 11, 13};
//******************************************



// Définition des broches pour les servomoteurs grattage
const int ANGLE_GRATTAGE = 15;


// Définition des adresses I2C pour les MCP23017
const uint8_t MCP_ADDRESSES[4] = {0x20, 0x21, 0x22, 0x23}; // adresse des 4 mcp,  1 par corde par simplicité

const int MAX_ACTIVATION_TIME =5000;// temps max actif pour un electroaimant

const int WAIT_DESACTIVATE = true;//attend un peut apres reception de note off 
const int TIME_WAIT_DESACTIVATE =200;//attend un peut apres reception de note off 

const int OPEN_STRING_NOTE[4]= {67, 60, 64, 69}; //base accordage ukulele (numero midi a vide pour les 4 cordes)
const int NUM_MAGNET_PER_STRING[4]= {12,12,12,12}; //nombre d'electroaimants utilisé par corde
const int SERVO_CENTER_ANGLE[4]= {90,90,90,90}; //angle central des servos grattage

#endif
