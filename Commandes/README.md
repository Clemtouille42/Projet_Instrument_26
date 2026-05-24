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
La principale contrainte de cette architecture réside dans l'alimentation en 1,8 V des lignes d'entrées/sorties (E/S) du microcontrôleur STM32. L'objectif initial était d'intégrer des adaptateurs de niveau logique (*level shifters*) afin d'éviter une sous-alimentation du STM32 mais cette option a été écarté pour simplifier la conception du pcb (réduire le nombre de composants). 

Cette configuration a imposé des contraintes d'interfaçage, la plupart des autres composants du PCB utilisant une tension IOVDD standard à 3,3 V. Cela a généré des conflits de compatibilité, notamment :
* L'interface de programmation ST-Link, qui opère nativement avec des niveaux logiques de 3,3 V.
* L'interface de débogage SWD, qui s'est retrouvée privée de sa tension de référence IOVDD.
---

## Voie d'amélioration

Les régulateurs ont une pin on/off (enable) qui permet de les désactiver ou activer. Sauf que j'ai routé la pin vers le STM32 afin de pouvoir séparer le 5V en cas de problème ou autre. 

Le fait est que l'USB étant, lors de la phase de test, la seule source d'alimentation puisque IOVDD n'est pas branchée (car les cartes en SWD pull up la tension à 3.3V), la carte s'est retrouvée sans alimentation. Un pont entre EN et le 5V suffit à corriger ce problème.

## Capteur de mouvement / LiDAR

Cette section aborde la partie capteur de la carte, utilisée pour concevoir les cordes virtuelles et sans contact de la harpe.

* **Le VL53L8CX :** Il s'agit d'un module LiDAR d'état solide multizone. Il mesure les distances sur un FoV (champ de vision) de 65° sous forme de matrice 4x4 ou 8x8. Le composant intègre son propre microprocesseur pour traiter le signal en interne. Il est capable de détecter plusieurs cibles au sein d'une même zone (par exemple, à travers une vitre), offre une immunité face au bruit optique et intègre un algorithme de détection de mouvement.

Le composant est multi-tension : il doit être alimenté en 3,3 V (maximum 3,6 V) pour sa partie analogique/laser, et en 1,8 V pour ses IOVDD.

---

## Conception

Le choix de ce composant repose sur sa capacité à mesurer plusieurs zones simultanément, répondant ainsi à l'exigence du cahier des charges de gérer plusieurs cordes. L'utilisation d'un capteur unique permet de limiter la taille et la complexité du PCB ; en effet, multiplier les LiDARs individuels en $I^2C$ aurait grandement complexifié la gestion des adresses.

Bien que le traitement embarqué du signal soit un aspect secondaire pour notre application, il offre l'avantage de pouvoir intégrer une vitre de protection transparente sur la harpe. De plus, la précision est excellente et le composant intègre son propre système d'auto-calibration.

---

## Axes d'amélioration

L'intégration logicielle de ce composant s'avère complexe. Comme mentionné précédemment, il possède son propre microcontrôleur et nécessite le chargement d'un firmware propriétaire au démarrage, sans quoi aucune mesure n'est possible. 

Ce firmware pèse environ **80 Ko**. Rapporté aux **128 Ko** de mémoire Flash disponibles sur notre STM32G431KBT6, cela représente une charge considérable, d'autant plus qu'il faut conserver de l'espace pour les fonctions HAL, la pile logicielle et le reste de l'application.

---

## Solutions correctives

Pour pallier ce problème de mémoire, deux pistes sont envisageables :
1. **Migration matérielle :** Remplacer le microcontrôleur actuel par un modèle doté d'une mémoire Flash plus importante (par exemple, un STM32 avec 256 Ko ou 512 Ko de Flash) ne pas prendre les composant que l'on nous demande de mettre car dans les stock.
2. **Optimisation logicielle :** Optimiser l'empreinte mémoire du code global et ajuster les options de compilation (par exemple, via le flag d'optimisation de taille `-Os` sous GCC) pour réduire la taille des bibliothèques HAL et du code utilisateur.
