#  Projet Instrument : Harpe Sans Contact

##  Présentation générale
Ce projet consiste à concevoir et réaliser une harpe électronique sans cordes physiques, dans laquelle les cordes traditionnelles sont remplacées par des faisceaux de détection. Lorsqu'un utilisateur est détecté par le capteur, la harpe analyse la position et la hauteur de la main pour émettre une note de musique spécifique. Ce système reproduit le principe de jeu d'une harpe classique tout en exploitant des technologies modernes de détection et de traitement du signal.

##  Objectifs du projet
* Mettre en œuvre une détection spatiale précise à l'aide d'un capteur multizone.
* Concevoir une carte électronique sur mesure intégrant la gestion d'alimentation et le traitement.
* Traiter les données de distance en temps réel pour les transformer en notes musicales.
* Restituer un signal sonore propre correspondant à la note calculée.

---

##  Architecture du système

Notre architecture repose sur trois grands piliers matériels, de la détection à la restitution sonore, en passant par une gestion rigoureuse de l'énergie.

### 1. Détection des mouvements
* **Capteur Time-of-Flight (ToF) :** VL53L8CX, utilisé pour déterminer avec précision la distance et la position de la main dans l'espace.
* **Adaptation et Communication :** Communication via le bus I2C avec des résistances de Pull-up (4.7 kΩ) sur les lignes SDA/SCL. Un adaptateur de niveaux est prévu pour assurer la compatibilité des signaux entre le capteur et le microcontrôleur.
* **Connectique :** Connecteurs dédiés pour lier physiquement le module capteur à la carte de traitement principale.

### 2. Traitement et Gestion de l'Énergie
* **Microcontrôleur :** STM32G431KB. Il est le cerveau du système : il reçoit les données de position du capteur via I2C et les convertit mathématiquement en notes (ex: mapping de plages de distances vers DO, RE, MI...).
* **Gestion de l'alimentation :** * **Alimentation directe en 5V** via le connecteur USB-C.
  * **Résistances CC (5.1 kΩ) :** Tirées vers la masse (GND) sur les broches CC1 et CC2 pour la négociation de puissance et assurer que le système reçoit bien ses 5V.
  * **LDO (Régulateur de tension) :** Abaisse le 5V en une tension stable de 3.3V, indispensable pour alimenter le microcontrôleur et le capteur ToF.
  * **Filtrage et découplage :** Utilisation de billes de ferrite et de condensateurs de découplage pour garantir une tension propre, sans parasites, afin de ne pas perturber les communications I2C et les traitements internes.

### 3. Restitution du signal
* **Isolation :** Optocoupleur pour garantir l'isolation électrique, protéger le microcontrôleur et éliminer les boucles de masse.
* **Audio :** Le signal est traité par un amplificateur avant d'être envoyé au mini haut-parleur pour la vibration sonore finale.
* **Interface externe :** Prise / Câble MIDI permettant une sortie numérique vers d'autres instruments ou un ordinateur.

---

##  Logiciel Embarqué (Work In Progress)

Le firmware (dossier `/CODE`) est actuellement en cours de développement et de débogage.

* **Communication :** Interfaçage I2C en cours d'implémentation pour récupérer la matrice de données du VL53L8CX.
* **Algorithme prévu :** Découpage du champ de vision du capteur en plusieurs zones virtuelles. Chaque zone correspond à une "corde". La distance mesurée dans une zone détermine la hauteur de la note (Grave/Aiguë) tandis que la zone elle-même détermine la note de la gamme.

---

##  Structure du dépôt

L'arborescence du projet est organisée de la manière suivante :

* 📁 **`Armature harpe/`** : Fichiers liés à la structure mécanique de la harpe (bois, impression 3D).
* 📁 **`CODE/`** : Code source C pour le microcontrôleur STM32 (En cours de développement).
* 📁 **`Commandes/`** : Suivi des achats et factures du matériel.
* 📁 **`Composants/`** : Regroupe toutes les ressources matérielles brutes (Datasheets des composants, empreintes spécifiques, nomenclature complète `composants.xlsx`).
* 📁 **`KiCad Harpe/`** : Projet KiCad complet incluant les schémas électroniques et le routage du PCB de notre carte sur mesure.

---

##  L'Équipe

Projet réalisé dans le cadre de notre 1ère année de cycle ingénieur (ENSEA) par :

* **Clément SERVAES** - Le Grand Manitou
* **Damien GANTCHEV** - Le Grand Vizir
* **Serge AROU** - Le Grand Chanteur
* **Maxime LEBRUN** - Le Grand Brun
