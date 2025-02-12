#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>

// ----------------------
// Paramètres généraux
// ----------------------
#define DEBUG 1

// Broches des servomoteurs (Arduino Micro Pro, par exemple)
constexpr int SERVO_PINS[4] = { 5, 6, 9, 10 };
constexpr int ANGLE_GRATTAGE = 15; // angle de déplacement du servo pour le grattage

// ----------------------
// Gestion des MCP23017
// ----------------------
constexpr int NUM_MCP_DEVICES = 2;       // On utilise 2 MCP23017
constexpr int MAX_OUTPUTS_PER_MCP = 16;    // Maximum de sorties par MCP
// Adresses I2C des MCP
constexpr uint8_t MCP_ADDRESSES_GLOBAL[NUM_MCP_DEVICES] = {0x20, 0x21};

// ----------------------
// Mapping des solénoïdes (frettes) pour chaque corde
// ----------------------

// Structure de mapping associant une frette à un MCP et une broche
struct FretMapping {
    uint8_t mcpIndex; // Indice du MCP (0 ou 1)
    uint8_t pin;      // Broche sur le MCP (0 à 15)
};

// Corde 1 (9 solénoïdes) : toutes sur MCP0, pins 0 à 8
constexpr FretMapping STRING1_MAPPING[9] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}
};

// Corde 2 (9 solénoïdes) : 7 sur MCP0 (pins 9 à 15) et 2 sur MCP1 (pins 0 et 1)
constexpr FretMapping STRING2_MAPPING[9] = {
    {0, 9}, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}, {1, 0}, {1, 1}
};

// Corde 3 (8 solénoïdes) : toutes sur MCP1, pins 2 à 9
constexpr FretMapping STRING3_MAPPING[8] = {
    {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}
};

// Corde 4 (6 solénoïdes) : toutes sur MCP1, pins 10 à 15
constexpr FretMapping STRING4_MAPPING[6] = {
    {1, 10}, {1, 11}, {1, 12}, {1, 13}, {1, 14}, {1, 15}
};

// Tableaux récapitulatifs pour utilisation dans le code
constexpr const FretMapping* STRING_FRET_MAPPINGS[4] = {
    STRING1_MAPPING,
    STRING2_MAPPING,
    STRING3_MAPPING,
    STRING4_MAPPING
};

constexpr int NUM_FRETS[4] = {9, 9, 8, 6}; // Nombre de solénoïdes (frettes) par corde

// ----------------------
// Autres paramètres
// ----------------------
constexpr int MAX_ACTIVATION_TIME = 5000; // Durée maximale d'activation d'un électroaimant (ms)
constexpr bool WAIT_DESACTIVATE = true;   // Attente après réception d'un note off
constexpr int TIME_WAIT_DESACTIVATE = 200;  // Délai en ms

constexpr int OPEN_STRING_NOTE[4] = {67, 60, 64, 69};   // Note MIDI à vide pour chaque corde
constexpr int SERVO_CENTER_ANGLE[4] = {130, 90, 100, 95}; // Angle central des servos

#endif
