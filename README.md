# Projet d'intégration SIM H25

#### Note: Voir le répo [master](https://github.com/zon-n/prog4-master) pour les informations sur l'appareil master du projet

## Table des matières

1. [Présentation](#présentation)   
2. [Installation et assemblage](#installation-et-assemblage)  
3. [Ressources supplémentaires](#ressources-supplémentaires)  

---

## Présentation

Ce projet est complémentaire à celui de l'appareil maître. Il s'agit de l'appareil esclave qui reçoit les commandes de l'appareil maître et ajuste la puissance des moteurs en fonction des données de télémétrie. Il utilise un algorithme de contrôle PID pour réguler la vitesse des moteurs et optimiser l'adhérence du véhicule pendant les virages. Le système est conçu pour être utilisé dans un véhicule à roues, tel qu'un robot ou un véhicule télécommandé.
La librairie CRC est utilisée pour la gestions des instructions embarquées de l'appareil essclave.

## Installation et assemblage

### Matériel utilisé
- **CRCDuino** : Microcontrôleur pour la gestion de contrôle des moteurs et la communication sans fil avec la manette.
- **Contrôleur de moteur** : Gère la puissance des moteurs en fonction des signaux reçus par PWM.

Installation du module CRC Duino sur le châssis du véhicule. Le module est alimenté par une batterie 12V et est relié à un contrôleur de moteur pour gérer la puissance des moteurs. Voici un exemple de schéma de câblage :
![image](images/circuit.png)

### Installation des logiciels et librairies

Le projet est développé à l'aide du framework **PlatformIO** pour le développement embarqué et des librairies Arduino.

1. **Installation de PlatformIO** : [https://platformio.org/install](https://platformio.org/install)

2. **Installation de l'Arduino IDE** : [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

3. **Librairies nécessaires** :

* `CRCLib` : Pour la gestion des instructions embarquées de l'appareil esclave.
* `Wire` : Pour la gestion de la communication par I2C.
   #### Voir les [ressources supplémentaires](#ressources-supplémentaires) pour plus d'informations

#### Installation de la librairie `CRCLib` :
Naviguer sur la page de téléchargement de la librairie [CRCLib](https://robo-crc.ca/participant-portal/) et télécharger la dernière version de la librairie. Dézipper le fichier et placer le dossier `CRCLib` dans le répertoire `lib` du projet.

#### Ajustement de la zone morte de la mannette
Pour ajuster la zone morte de la manette, il faut modifier la valeur de `DEAD_ZONE` dans le fichier `src/main.cpp`. La valeur par défaut est de 0.05, ce qui signifie que les valeurs inférieures à 0.05 seront considérées comme nulles. Vous pouvez ajuster cette valeur en fonction de vos besoins.

#### Ajustement de la vitesse maximale
Pour ajuster la vitesse maximale du véhicule, il faut modifier la valeur de `MAX_SPEED` dans le fichier `src/main.cpp`. La valeur par défaut est de 255, ce qui correspond à la vitesse maximale des moteurs. Vous pouvez ajuster cette valeur en fonction de vos besoins.

---

### Protocoles de communication

Le projet utilise plusieurs protocoles pour gérer les différents composants :

1. **PWM** : Utilisé pour contrôler la vitesse des moteurs en ajustant la largeur des impulsions électriques.
2. **I2C** : Utilisé pour la communication avec le capteur MPU9250. Établit la connection d'envoi binaire avec un appareil [master](https://github.com/zon-n/prog4-master). L'appareil maître envoie un signal de 2 octets contenant la vitesse souhaitée et l'angle de virage. L'appareil esclave reçoit ce signal et ajuste la puissance des moteurs en conséquence.
---

## Ressources supplémentaires

- **Documentation sur l'ESP32** : [https://docs.espressif.com/](https://docs.espressif.com/)
- **Documentation sur PlatformIO**: [https://platformio.org/](https://platformio.org/)
- **Docoumentation sur Arduino**: [https://www.arduino.cc/en/software/](https://www.arduino.cc/en/software/)
- **Documentation sur la librairie CRCLib** : [https://robo-crc.ca/participant-portal/](https://robo-crc.ca/participant-portal/)

- **Hyperliens vers les répositoires Github des libraires utilisées**
    - [CRCLib](https://robo-crc.ca/participant-portal/)
    - [Wire](https://docs.arduino.cc/language-reference/en/functions/communication/wire/)
    - [Servo](https://docs.arduino.cc/libraries/servo/)