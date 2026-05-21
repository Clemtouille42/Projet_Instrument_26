# Projet_Instrument_26



## Présentation générale

Ce projet consiste à concevoir et réaliser une harpe électronique sans cordes physiques, dans laquelle les cordes traditionnelles sont remplacées par des capteurs. Lorsqu'un utilisateur est détecter par un capteur en fonction de la position et l'hauteur, la harpe vas émettre une note de musique, reproduisant le principe de jeu d'une harpe classique tout en exploitant des technologies modernes de détection et de traitement du signal.


## Objectifs initiaux du projet

-Mettre en œuvre une détection de mouvement a l'aide de capteurs.
-Traiter les données pour les transformer en notes.
-Envoyer un signal sonore de la note calculée.


## Solution mise en place

1. Chaque “corde” de la harpe est simulé par une zone délimitée arbitrairement par un capteur Time-of-Flight (TOF).

2. Lorsque la main de l’utilisateur entre dans la zone du capteur l’événement est détecté par l'unique capteur qui vas transférer les informations de la position de notre main aux processeur.

3. Le processeur va traiter les données afin de déterminer où verticalement et horizontalement ce trouve notre main pour déterminer respectivement la note (DO RE MI FA SOL LA) et la hauteur (Grave/Aigue)

4. le processeur renvoies ces données sous forme de signal  afin de sortir la dite note.

## Architecture du système

## Composants pour la détection des mouvements :

-Capteur de mouvement (Time-of-Flight) : Détecte la distance de la main.
-Résistances Pull-up (SDA/SCL) : Pour la communication (I2C) entre les capteurs et le processeur.
-Adaptateur de niveaux : Pour que les signaux du capteur (en 3.3V) sont compatibles avec le microcontrôleur.
-Connecteurs : Pour lier physiquement les capteurs à la carte de traitement.


## Composant pour le Traitement de l'information
-Microcontrôleur : reçois la position de la part des capteurs, puis la traite afin de convertir les données de la position en une note
-Alimentation 5V : Fournit l'énergie stable à toute la logique.
-LDO Régulateur de tension : Garantit une tension propre, essentielle pour éviter les erreurs de calcul du processeur.
-Ferrite : Filtre les parasites haute fréquence sur l'alimentation pour ne pas perturber les calculs.
-Passifs : Condensateurs de découplage pour stabiliser le fonctionnement du microcontrôleur.


## Composant pour la restitution du signal

Prise MIDI / Câble MIDI : Permet la sortie numérique vers le haut parleur.

Optocoupleur : Garantit l'isolation électrique (protection du microcontrôleur et élimination des boucles de masse).

Amplificateur : Reçoit le signal audio numérique/analogique et le prépare pour le haut-parleur.

Mini haut-parleur : Émet la vibration sonore finale.

Résistances CC (Rd 5.1 kΩ) : Permettent la négociation de l'alimentation (via USB-C) pour assurer que le système a assez de puissance pour alimenter l'amplificateur et le reste des composants.



## Composants principaux

- Mini haut-parleur
- Prise USB
- Câble MIDI
- Capteur de mouvement
- Microcontrôleur
- Amplificateur
- Transformateur
- Ferrite
- LDO Régulateur de tension 
- Adaptateur de niveaux 
- Prise MIDI
- 2× résistances CC (Rd) : 5.1 kΩ ±1% (0603/0805) vers GND sur CC1 & CC2
- "Pull-up SDA/SCL : 2.2 kΩ à 4.7 kΩ vers 3.3 V (0603) Safe default: 4.7 kΩ (si bus pas trop long)"
- Connecteur
- Optocoupleur
- Passifs
- Alimentation 5V
- Structure mécanique (bois / plastique / impression 3D)



## Fonctionnalités

- Détection de notes en temps réel
- Attribution d’une note par faisceau
- Changement de gamme ou d’octave
- Contrôle du volume
- Retour visuel possible (LEDs par corde)
- Mode autonome ou connecté à un ordinateur (MIDI)



## Équipe

Projet réalisé dans le cadre d’un **projet d’ingénierie de fin d’année** par :

* Clément SERVAES - Le Grand Manitou
* Damien GANTCHEV - Le Grand Vizir
* Serge AROU - Le Grand Chanteur
* Maxime LEBRUN - Le Grand Brun

