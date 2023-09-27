#ifndef UKULELE_H
#define UKULELE_H

#include "settings.h"
#include "ukuleleString.h"
#include "Servo.h"
/***********************************************************************************************
----------------------------      UKULELE system       ----------------------------------------
************************************************************************************************/
class Ukulele {
public:
  Ukulele();
  void playMidiNote(int midiNote, int velocity); // note On
  void stopMidiNote(int midiNote);// note off
  void update (); // fonction pour verifier les temps d'activations des electroaimants pour limiter la surchauffe
  void initMusic(); // fonction pour faire une musique a l'alumage => test des cordes, premiere frette + servo 
private:
  int findString(int midiNote);// demande a chaque string si c'est jouable et assigne la note a la premiere corde dipo
  UkuleleString* _strings[4];// tableaux des cordes 
};

#endif
