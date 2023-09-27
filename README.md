
--- WORK IN PROGRESS ---

# Orchestrion-Ukulele

Ce projet utilise un Arduino Leonardo (ou micro) pour contrôler un ukulele acoustique à l'aide de signaux MIDI. 
L'Ukulele est équipé d'électroaimants pour actionner les frettes et d'un servomoteur pour actionner le "grattage" sur chaque corde.

Le contrôleur MIDI permet de jouer des notes recues par le cable USB.

## Fonctionnalités

- Lecture et execution des notes MIDI dans la plage jouable du Ukulele

## Installation materielle

#### impression 3D
Ce projet utilise l'impression 3D FMD afin de faire les differentes pieces du projet.
Une fois les differentes parties validé, toutes les pieces seront regroupée dans le dossier "STL".
certaines pieces sont relativement grosse mais elles devrais renter sur un plateau de 30x20cm pour la piece la plus imposante.

### Schemas branchements
![schema electronique](https://github.com/glloq/Orchestrion_ukulele/blob/main/schemas.png?raw=true)

### Matériel requis
- Alimentation 5v 2A
- un cable USB pour l'arduino
- Arduino Leonardo(ou compatible) 
- Ukulele 12 frettes
- 4 servomoteurs pour le grattage des 4 cordes
- 4 x 12 électroaimants; un pour chaque frettes avec alimentation + fusible adapté + driver (mofset par exemple) 
- 4 MCP23017 : pour l'extension des pins de l'arduino



## Installation logicielle

#### Bibliothèques requises

- [MidiUSB.H](https://github.com/arduino-libraries/MIDIUSB)
- [Adafruit_MCP23X17.h](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)
- avr/interrupt.h
- Arduino.h


## Options de configuration

Le fichier `Settings.h` contient plusieurs options de configuration pour personnaliser le fonctionnement du contrôleur Arduino Ukulele MIDI. 
Vous pouvez modifier ces options avant de téléverser le code sur votre Arduino:

- le nombre de frettes par cordes
- le temps d'activation maximum de l'electroaimant en continu
- l'angle "zero" du servo de grattage par corde : c'est la position du servo contre la corde
- l'angle de grattage
- L'activation du debuggage via serial


#### Preparations
1. Ouvrez le fichier "ukulele-servo-init.ino" de ce dépôt
2. Sélectionnez le port série approprié et le type de carte dans le menu Outils de l'IDE Arduino.
3. Téléversez le code sur votre Arduino.
4. il faut rentrer l'angle du servo (entre 20 et 160) dans le moniteur serie et valider avec entré jusqu'a ce que le pick soit en contact avec la corde
5. noter la valeur de l'angle et passer à la corde suivante en envoyant "ok"
6. faire les meme manipulations que précedement avec les 3 autres servos 

#### Installation
1. Clonez ou téléchargez ce dépôt.
2. Ouvrez le fichier ukulele.ino dans l'IDE Arduino.
3. Installez la bibliothèque MIDIUSB et adafruit MCP23x17 si vous ne l'avez pas déjà fait.
4. faites les modifications necessaire à votre montage dans settings.h
5. Connectez votre Arduino Leonardo à votre ordinateur via un câble USB.
6. Sélectionnez le port série approprié et le type de carte dans le menu Outils de l'IDE Arduino.
7. Téléversez le code sur votre Arduino Leonardo.
8. Connectez votre Arduino à un hôte MIDI et profitez de votre ukulele contrôlé par MIDI !

## patreon 
[lien pour me soutenir](https://patreon.com/user?u=2656559&utm_medium=clipboard_copy&utm_source=copyLink&utm_campaign=creatorshare_creator&utm_content=join_link) 

## Licence

Ce projet est sous licence "je partage mon taf gratuitement si tu veut faire de l'argent dessus demande avant et on partage :D"
