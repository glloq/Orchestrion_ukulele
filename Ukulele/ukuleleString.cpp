#include "ukuleleString.h"
#include "settings.h"

// ********************************************************************************************************************************
// Constructeur de la corde, créer les object pour chaque notes en fonction de la note de base recue + initiatlise le servomoteur grattage en position de depart
UkuleleString::UkuleleString(int servoPin,  uint8_t mcpAddress, int baseMidiNote, int numOfNotes, int angle) {
   if (DEBUG) {
        Serial.println("ukuleleString--creation objet UkuleleString");
    } 
  
  if (DEBUG) {
        Serial.println("ukuleleString--mcp init start");
    } 
 
  // initialisation du mcp pour la corde  
  Wire.begin(); // Initialize I2C communication
  mcp= Adafruit_MCP23X17();

    if (!mcp.begin_I2C(mcpAddress)) {
        Serial.println("MCP init failed");
        while(1);
    }   
    if (DEBUG) {
        Serial.println("ukuleleString--mcp init done");
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
        extinctionTime[i] = 0;
        active[i] = false;
        mcp.pinMode(i, OUTPUT);
    }
    //initialisation du servo grattage
  if (DEBUG) {
        Serial.println("ukuleleString--servo init start");
    } 
  this->servo.attach(servoPin);  // attaches the servo on pin servoPin
  //met le pin du servo de grattage a la positon init 
  this->servo.write(angleZero-ANGLE_GRATTAGE);
  delay(1000);
  this->servo.write(angleZero);
     if (DEBUG) {
        Serial.println("ukuleleString--servo init done");
    } 
}


// ********************************************************************************************************************************
// joue la note envoyé par ukulele.h, active et desactive l'electroaimant si message note on/off pour la note en cours
void UkuleleString::playNote(int note, bool isNoteOn) {
    int numMcp = note - this->baseMidiNote;    //note On
    if (DEBUG) {
        Serial.print("ukuleleString--Note :");
        Serial.print(note);       
        Serial.print(" - ");        
       
        if(isNoteOn){
          Serial.println("on");
          }else{
          Serial.println("off");
        }
    }
    if(isNoteOn) {
      this->currentMidiNote = note;
      if (numMcp==0){// le cas ou c'est la premiere note de la corde pas d'electroaiamnt a activer
        pluck();
      }else{// sinon on active la frette et on gratte 
        activateFret(numMcp-1);
        pluck();
      }
      // Note Off 
    } else {
        mute();// utilise le servo grattage pour arreter le son de la corde 
        if(numMcp!=this->baseMidiNote){// si c'est pas la premiere case a vide 
          desactivateFret(numMcp-1);
        } 
        this->currentMidiNote = -1;
    }
}


// ********************************************************************************************************************************
// permet de mettre a jours le temps max actif pour l'elecroaimant (permet d'eviter des surchauffes et augmente la durée de vie)
void UkuleleString::update() {
//si la corde est active
  if(playing) {
        for(int i = 0; i < numOfNotes; i++) {
            if(active[i] && millis() > extinctionTime[i]) {
                desactivateFret(i); 
            }
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
    return currentMidiNote;
}
  // ********************************************************************************************************************************
  //active la note / accord sur la frette avec l'electroaiamant
void UkuleleString::activateFret(int numMcp) {
    mcp.digitalWrite(numMcp, HIGH);
    active[numMcp] = true;
    extinctionTime[numMcp] = millis() + MAX_ACTIVATION_TIME;
    playing = true;
}
  // ********************************************************************************************************************************
  //desactive la note / accord sur la frette avec l'electroaiamant
void UkuleleString::desactivateFret(int numMcp) {
  //verifie si c'est bien la note en cours sur la corde ?
    mcp.digitalWrite(numMcp, LOW);
    active[numMcp] = false;
    playing = false;
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