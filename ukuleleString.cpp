#include "ukuleleString.h"
#include "settings.h"

// ********************************************************************************************************************************
// Constructeur de la corde, créer les object pour chaque notes en fonction de la note de base recue + initiatlise le servomoteur grattage en position de depart
UkuleleString::UkuleleString(int servoPin,  uint8_t mcpAddress, int baseMidiNote, int numOfNotes, int angle) {
  // initialisation du mcp pour la corde  
  Wire.begin(); // Initialize I2C communication
  this->mcp = new Adafruit_MCP23X17();
    if (!this->mcp->begin_I2C(mcpAddress)) {
        Serial.println("MCP init failed");
        while(1);
    }   
  // declaration des varaibles de l'objet
    this->playing = false;
    this->servoMovingToA = true;
    this->baseMidiNote = baseMidiNote;
    this->numOfNotes = numOfNotes;
    this->angleZero = angle;
    this->currentMidiNote = -1;  // no note is playing
    //init des electroaiamnt pour chaque note /accords sur la corde 
    for(int i = 0; i < numOfNotes; i++) {
        this->notes[i] = new Note( i, this->mcp);
    }
    this->servo.attach(servoPin);  // attaches the servo on pin servoPin
    //met le pin du servo de grattage a la positon init 
    this->servo.write(angleZero-ANGLE_GRATTAGE);
}


// ********************************************************************************************************************************
// joue la note envoyé par ukulele.h, active et desactive l'electroaimant si message note on/off pour la note en cours
void UkuleleString::playNote(int note, bool isNoteOn) {
    int numMcp = notes[note-this->baseMidiNote];
    //note On
    if(isNoteOn) {
      this->currentMidiNote = note;
      if (note==0){// le cas ou c'est la premiere note de la corde pas d'electroaiamnt a activer
        pluck();
      }else{// sinon on active la frette et on gratte 
        activateFret(numMcp);
        pluck();
      }
      // Note Off 
    } else {
        mute();// utilise le servo grattage pour arreter le son de la corde 
        if(note!=this->baseMidiNote){// si c'est pas la premiere case a vide 
          desactivateFret(numMcp);
        } 
        this->currentMidiNote = -1;
    }
}


// ********************************************************************************************************************************
// permet de mettre a jours le temps max actif pour l'elecroaimant (permet d'eviter des surchauffes et augmente la durée de vie)
void UkuleleString::update() {
//si la corde est active
  if (playing== true){
    for(int i = 1; i < numOfNotes; i++) {
        notes[i]->check();// on verfie si le temps max actif est depassé 
    }
  }
}


  // ********************************************************************************************************************************
  //verifie si la note est jouable et si la corde est pas deja en cours d'utilisation
  bool UkuleleString::isPlayable(int MidiNote) {
    if (this->playing==false){// si la corde ne joue pas deja une note
      if((MidiNote>=this->baseMidiNote )&& (MidiNote<= this->baseMidiNote+this->numOfNotes )){// si la note peut etre jouée 
        return 1;
    }else{
      return 0;}
  }else{return 0;}
}


  // ********************************************************************************************************************************
  //revoi la note en cours active tant qu'on ne recoit pas la note off
int UkuleleString::getCurrentMidiNote() {
    return this->currentMidiNote;
}
  // ********************************************************************************************************************************
  //active la note / accord sur la frette avec l'electroaiamant
void UkuleleString::activateFret(int numMcp) {
    this->notes[numMcp-1]->on();
    this->playing = true;
}
  // ********************************************************************************************************************************
  //desactive la note / accord sur la frette avec l'electroaiamant
void UkuleleString::desactivateFret(int numMcp) {
  //verifie si c'est bien la note en cours sur la corde ?

    this->notes[numMcp-1]->off();
    this->playing = false;
}
  // ********************************************************************************************************************************
//le mouvement du servo moteur pour le grattage de la corde, ne va que de haut en bas en alternant
void UkuleleString::pluck() {
    if (this->servoMovingToA) {
        this->servoGoToA();
    } else {
        this->servoGoToB();
    }
    this->servoMovingToA = !this->servoMovingToA;
}

void UkuleleString::servoGoToA() {
    this->servo.write(angleZero+ANGLE_GRATTAGE);
}

void UkuleleString::servoGoToB() {
    this->servo.write(angleZero-ANGLE_GRATTAGE);
}

void UkuleleString::mute() {
    this->servo.write(angleZero);
}