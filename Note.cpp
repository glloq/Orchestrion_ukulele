#include "Note.h"

// ********************************************************************************************************************************
// constructeur de la note asocié au mcp pour chaque electroaimant 
Note::Note(int pin, Adafruit_MCP23X17* mcp) {
    _pin = pin;
    _mcp = mcp;
    _active = false;
    _mcp->pinMode(_pin, OUTPUT);
    _mcp->digitalWrite(_pin, LOW);
}
// ********************************************************************************************************************************
// active l'electroaimant
void Note::on() {
    _mcp->digitalWrite(_pin, HIGH);
    _active = true;
    _extinctionTime = millis()+ MAX_ACTIVATION_TIME; // stoque le temps max ou il faut desactiver la sortie
}
// ********************************************************************************************************************************
// desactive l'electroaimant
void Note::off() {
    _mcp->digitalWrite(_pin, LOW);
    _active = false;
}
// ********************************************************************************************************************************
// desactive l'electroaimant
bool Note::isActive() {
    return _active;
}
// ********************************************************************************************************************************
// desactive l'electroaimant si il est actif depuis trop longtemps
void Note::check() {
  if (_active ){// si electroaiamant actif 
    if(millis() > _extinctionTime) { //et temps depassé alors 
      off();//on desactive l'electroaimant
    }
  }
}
