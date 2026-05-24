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

   
## Interface USB-C

L'intégration d'un port USB Type-C sur la carte est un choix d'ergonomie, permettant d'alimenter le système en 5 V de manière universelle. Néanmoins, nous avons configuré le STM32 pour qu'il puisse transmettre et recevoir des données via cette interface, offrant ainsi plus de polyvalence pour les phases de test et de débogage.

---

## Conception et routage

Le port USB-C utilise un routage standard incluant les lignes de données ($D+/D-$), le bus d'alimentation ($V_{BUS}$ / 5 V) et la masse ($GND$). L'ensemble a été routé de manière symétrique pour garantir la réversibilité native du connecteur mâle.

Il y a un USBLC6-2SC6 qui sert de protection pour le port usb c'est un composant standard qui est en stock a l'école.

Cependant, deux contraintes critiques liées à la haute vitesse et à la conception du PCB sont à noter :
* **Paires différentielles :** Les lignes $D+$ et $D-$ forment une paire différentielle qui exige une adaptation d'impédance et des longueurs de pistes strictement identiques (skews minimisés). Bien que cette condition soit globalement respectée sur notre routage, l'équilibrage des longueurs peut encore être affiné.
* **Intégrité du signal :** La présence de vias sur ces lignes de données n'est pas optimale et peut introduire des discontinuités d'impédance.

---

## Axes d'amélioration

Lors de la phase de conception, un problème de synchronisation sous KiCad a empêché le transfert correct des informations de routage depuis le schéma vers le layout (footprint). À cause de ce bug, la ligne 5 V ($V_{BUS}$) n'a pas été reliée au régulateur de tension 3,3 V.

De plus, le routage de la paire différentielle USB pourra être optimisé dans une future révision de la carte en supprimant complètement les vias et en appliquant un *length-matching* parfait.

Effectuer des test pour étudier l'adaptation d'impédence.

---

## Solution corrective

Pour valider le prototype fonctionnel malgré l'erreur de routage du $V_{BUS}$, un strap (pont filaire) a été soudé manuellement pour amener directement le 5 V aux bornes du régulateur de tension.


## Interface midi

L'interface midi est indiquer dans le cahier des charges, elle permet de communiquer a l'ordinateur les notes jouer par l'instrument.

* **Le ACPL-M61L:** Il s'agit d'un opto-coupleur il est obligatoir d'apres les specs du midi , cela permet d'éviter les boucles de masse.
* * **Le le 74LVC1G125:** Il s'agit du buffer qui permet a la communiaction UART qui sort de l'opto-coupleur d'avoir assez de puissance pour etre reçus de maniere correcte coté PC.

---

## Conception

Je vais etre bref sur cette partie car le Midi est pas ma partie du projet. J'ai choisis les composant standard proposer par des forums sur l'audio.Le APCL respecte le baud rate du midi et la ferite permet d'éviter certain parasite et d'augmenter la portée du midi. Nous avons choisis de faire un midi in/out pour tester la conception entiere d'une interface midi. 

---

## Axes d'amélioration

Je n'ai pas commander la ferite, ça impacte pas vraiment les resultat car le cable commander (voir liste des composants) est court <1m. 
nous avons pas pu tester pleinment la communication par manque de temps.

---

## Solutions correctives

Pousser des test de CEM pour étudier l'utilitée de la ferrite.

## Partie Audio

Afin de rendre la harpe autonome et de ne pas la faire dépendre entièrement de l'interface MIDI et d'un ordinateur externe, un étage d'amplification de puissance et un haut-parleur (speaker) ont été intégrés directement sur la carte.

* **Le PAM8403 :** Il s'agit d'un amplificateur audio stéréo de classe D. Très populaire dans les systèmes embarqués pour son excellent rendement énergétique, il permet de piloter directement de petits haut-parleurs sans nécessiter de dissipateur thermique externe.

---

## Conception

Le haut parleur indique dans sa documentation qu'il faut de la férite sur ses deux entrée donc nous avons commander celle-ci. 
---

## Axes d'amélioration

Nous avons pas eu le temps de tester cette partie en profondeur donc c'est compliquer d'avoir un retour d'expériences mais j'imagine que des teste sur l'adaptation d'impédence ou autres aurais pus etre utiles.

néamoins le haut parleur arrive a sortir des bip boup en testant les sortie DAC.

---



