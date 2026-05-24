# Conception du PCB et choix des composants

Ce readme va aborder la partie conception du pcb et choix des composants en détail. Je vais le faire pour chaque partie que l'on peut voir sur le schematics, donc je vous invite à le regarder.

---

## Régulateur / alimentation

Cette partie est composée de deux régulateurs de tension en série qui régulent successivement le 5V puis le 3.3V pour délivrer du 1.8V et 3.3V. La source d'alimentation principale pour la carte est le 5V de l'USB.

### Choix des composants

* **Le BU33SD5WG-TR :** C'est un régulateur qui sort du 3.3V. Celui-ci sert à alimenter les composants fonctionnant en 3.3V avec le 5V de l'usb. C'est un composant plutôt standard pour ce genre de tâche.

* **AP2112K-1.8 :** C'est aussi un régulateur, sauf que celui-ci sort du 1.8V. Le choix de ce composant est plus stratégique car il sort sur IOvdd qui est extrêmement important pour le lidar (qui est alimenté en 3.3v et 1.8v). J'ai choisi ce composant car il ne laisse pas passer de bruit, possède un bon taux de réjection et le courant fourni correspond à la consommation.

---

## Conception

La principale contrainte est l'alimentation en 1.8V de la STM32 car je voulais ajouter des levels shifter mais sans sous-alimenter la stm. Cela nous a pas mal contraint car pour la plupart des composants, IOVDD est du 3.3V. Ce qui a causé des problèmes, notamment avec le ST-link qui est en 3.3V et le SWD qui s'est retrouvé sans iovdd du coup.

---

## Voie d'amélioration

Les régulateurs ont une pin on/off (enable) qui permet de les désactiver ou activer. Sauf que j'ai routé la pin vers le STM32 afin de pouvoir séparer le 5V en cas de problème ou autre. 

Le fait est que l'USB étant, lors de la phase de test, la seule source d'alimentation puisque IOVDD n'est pas branchée (car les cartes en SWD pull up la tension à 3.3V), la carte s'est retrouvée sans alimentation. Un pont entre EN et le 5V suffit à corriger ce problème.

