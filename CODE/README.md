# Compte-Rendu de Projet : Partie Développement et Programmation

Ici se trouve la partie logicielle du projet. Cela comprend :

* Programme brut
* Description de l’avancée du projet et des objectifs


## Choix de l'Architecture Matérielle et Programmation

Pour la programmation de notre microcontrôleur cible, un **STM32G431KBT6**, on a choisi de le codé en passant par une liaison **SWD (Serial Wire Debug)**. Cette méthode permet d'alléger le design de notre carte finale en évitant d'y intégrer un programmateur lourd.

Pour réaliser cette interface, nous avons utilisé une carte **NUCLEO** configurée en programmateur externe :
* **Configuration de la Nucleo :** Nous avons **retiré les cavaliers (jumpers)** du connecteur ST-LINK afin d'isoler le programmateur embarqué du microcontrôleur de la Nucleo.
* **Connection SWD :** Nous avons ensuite connecté les broches SWCLK, SWDIO, NRST et la masse (GND) du ST-LINK directement sur les broches correspondantes de notre processeur cible pour y injecter le code.

---

## 2. Tests de Validation et Communication I2C

Une fois la chaîne de programmation validée, nous avons développé un premier programme de test pour vérifier le bon câblage et la communication avec notre environnement matériel, plus précisément via le bus **I2C**.

### Scan du bus I2C :
Nous avons implémenté un code de balayage (*I2C scanner*) dont le but est de tester toutes les adresses esclaves possibles sur le bus.
* **Résultat :** Le programme de scan a détecté et retourné l'adresse décimale **41**.
* **Validation :** En confrontant ce résultat avec la documentation technique de notre capteur, nous avons confirmé que l'adresse **0x29** est bien celle par défaut du composant. Cela valide le bon fonctionnement de notre code de communication et l'intégrité matérielle de la liaison I2C.

---

## 3. Limitations Mémoire et Problématiques Rencontrées

L'étape suivante consistait à intégrer les drivers officiels (API Ultra Lite Driver - ULD) d'STMicroelectronics pour exploiter le capteur de vol (ToF) **VL53L8CX** et récupérer sa matrice de données. 

C'est à ce stade que nous avons rencontré une limitation technique majeure liée au dimensionnement du microcontrôleur :

> ⚠️ **Saturation de la mémoire :**
> Le **STM32G431KBT6** dispose d'une configuration mémoire trop restreinte pour cette application (32 Ko de RAM et 128 Ko de mémoire Flash). Les drivers nécessaires à l'initialisation et à la gestion des matrices du VL53L8CX requièrent un volume de mémoire Flash et de RAM supérieur à ce que notre processeur peut embarquer. 

Le code étant trop lourd, il a été impossible de compiler et de téléverser l'application complète. Nous n'avons donc pas pu finaliser la récupération de la matrice de données.

---

## 4. Conclusion et Perspectives

Ce projet a permis de valider avec succès notre stratégie de programmation par liaison SWD ainsi que la communication I2C avec le capteur. Cependant, le manque de mémoire (Flash/RAM) du processeur choisi s'est révélé être un facteur bloquant pour l'utilisation des drivers du VL53L8CX.

Pour finaliser ce projet, il aurait été nécessaire de :
1. **Migrer vers un microcontrôleur plus performant** de la même famille mais disposant de plus de mémoire (Flash et RAM).
2. **Développer un driver personnalisé ultra-léger**, en faisant l'impasse sur l'API officielle pour ne coder que les registres strictement nécessaires, bien que cette solution soit beaucoup plus complexe à mettre en œuvre.
