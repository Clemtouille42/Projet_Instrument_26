# Projet_Instrument_26



## Présentation générale

Ce projet consiste à concevoir et réaliser une harpe électronique sans cordes physiques, dans laquelle les cordes traditionnelles sont remplacées par des faisceaux optiques.
Lorsqu’un utilisateur interrompt un faisceau avec la main, une note de musique est générée, reproduisant le principe de jeu d’une harpe classique tout en exploitant des technologies modernes de détection et de traitement du signal.


## Objectifs du projet

* Concevoir un instrument de musique basé sur des capteurs optiques
* Mettre en œuvre une détection, puis un traitement et enfin une génération sonore


## Principe de fonctionnement

1. Chaque “corde” de la harpe est matérialisée par un faisceau optique.
2. Lorsque le faisceau est interrompu par la main de l’utilisateur :

   * l’événement est détecté par un microcontrôleur,
   * une **note musicale associée** est déclenchée.
3. Le son est :

   * soit généré directement par le système embarqué,
   * soit transmis sous forme de **signal MIDI** vers un logiciel externe.



## Architecture du système

### 1. Système de détection

* Faisceaux optiques alignés verticalement
* Détection par photodiodes / phototransistors
* Sortie numérique (faisceau coupé / non coupé)
* Filtrage logiciel pour éviter les faux déclenchements (bruit, lumière ambiante)

### 2. Unité de traitement

* Microcontrôleur central (STM32G431KB)
* Lecture en temps réel des capteurs
* Association capteur - note - octave
* Gestion de la logique musicale (gamme, modes, sustain)

### 3. Génération sonore

Plusieurs modes possibles :

* Lecture de fichiers audio pré-enregistrés
* Synthèse sonore numérique
* Sortie MIDI vers un ordinateur ou un synthétiseur externe

### 4. Sortie audio

* Amplificateur audio basse puissance
* Haut-parleur intégré ou sortie casque
* Contrôle du volume



## Composants principaux

* Microcontrôleur (STM32G431KB)
* Émetteurs optiques (laser ou LED infrarouge)
* Module audio ou DAC
* Amplificateur audio
* Haut-parleur
* Alimentation 5V
* Structure mécanique (bois / plastique / impression 3D)



## Fonctionnalités

* Détection de notes en temps réel
* Attribution d’une note par faisceau
* Changement de gamme ou d’octave
* Contrôle du volume
* Retour visuel possible (LEDs par corde)
* Mode autonome ou connecté à un ordinateur (MIDI)



## Équipe

Projet réalisé dans le cadre d’un **projet d’ingénierie de fin d’année** par :

* Clément SERVAES - Le Grand Manitou
* Damien GANTCHEV - Le Grand Vizir
* Serge AROU - Le Grand Chanteur
* Maxime LEBRUN - Le Grand Brun

