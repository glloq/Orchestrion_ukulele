/************************************************************************************************************************************
// code prevu uniquement pour trouver les angles de contacts des pics sur la corde avec les 4 servomoteurs de grattage de l'intrument 
************************************************************************************************************************************/
#include <Servo.h>

Servo servos[4];  // Un tableau pour contenir vos objets Servo.
int angles[4] = {90, 90, 90, 90};  // Angles initiaux pour chaque servo.
int servoPins[4] = {5, 6, 9, 10};  // Les pins auxquels les servos sont connectés.
int currentServo = 0;  // Le servo actuellement sélectionné pour le réglage.

void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);  // Attachez chaque servo à son pin.
    servos[i].write(angles[i]);  // Mettez à jour l'angle initial de chaque servo.
  }
  Serial.println("Ajustez l'angle du servo 0. Envoyez 'ok' pour confirmer et passer au suivant.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Lire la commande jusqu'à la nouvelle ligne.
    command.trim();  // Enlever les espaces en début et fin de chaîne.
    
    if(command == "ok") {
      Serial.println("Angle confirmé.");
      if(currentServo < 3) {
        currentServo++;  // Passer au servo suivant
        Serial.print("Ajustez l'angle du servo ");
        Serial.print(currentServo);
        Serial.println(". Envoyez 'ok' pour confirmer et passer au suivant.");
      } else {
        Serial.println("Tous les servos sont réglés.");
      }
    } else {
      int angle = command.toInt();  // Convertir la commande en un entier.
      if(angle >= 0 && angle <= 180) {  // Vérifier si l'angle est valide.
        angles[currentServo] = angle;  // Mettre à jour l'angle du servo actuel.
        servos[currentServo].write(angle);  // Ajuster l'angle du servo actuel.
        Serial.print("Servo ");
        Serial.print(currentServo);
        Serial.print(" ajusté à ");
        Serial.println(angle);
      } else {
        Serial.println("Angle invalide. Entrez un nombre entre 0 et 180.");
      }
    }
  }
}
