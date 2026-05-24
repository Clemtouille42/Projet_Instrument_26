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
La principale contrainte de cette architecture réside dans l'alimentation en 1,8 V des lignes d'entrées/sorties (E/S) du microcontrôleur STM32. L'objectif initial était d'intégrer des adaptateurs de niveau logique (*level shifters*) afin d'éviter une sous-alimentation du STM32. 

Cette configuration a imposé de fortes contraintes d'interfaçage, la plupart des autres composants du PCB utilisant une tension IOVDD standard à 3,3 V. Cela a généré des conflits de compatibilité, notamment :
* L'interface de programmation ST-Link, qui opère nativement avec des niveaux logiques de 3,3 V.
* L'interface de débogage SWD, qui s'est retrouvée privée de sa tension de référence IOVDD.
---

## Voie d'amélioration

Les régulateurs ont une pin on/off (enable) qui permet de les désactiver ou activer. Sauf que j'ai routé la pin vers le STM32 afin de pouvoir séparer le 5V en cas de problème ou autre. 

Le fait est que l'USB étant, lors de la phase de test, la seule source d'alimentation puisque IOVDD n'est pas branchée (car les cartes en SWD pull up la tension à 3.3V), la carte s'est retrouvée sans alimentation. Un pont entre EN et le 5V suffit à corriger ce problème.

---

## Solution corrective

Un raccordement physique (pont/strap) entre la broche EN et le rail 5V_USB permet de forcer l'activation permanente des régulateurs. Ce correctif matériel résout le problème de démarrage et sera directement intégré lors de la prochaine révision du routage du PCB.
