# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Projet final
+ Section #  : 3
+ Équipe #   : 5776
+ Correcteur : Ghali Chraibi

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(0/1.5)__ |

Pas de d'identification matérielle dans les différents fichiers utilisés de votre librairie.

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.4/0.5)     |
| __Résultat partiel__                         | __(0.9/1.5)__ |

Plusieurs chiffres magiques :
Délais, vitesse des moteurs, nombres d'itérations et valeurs magiques dans 'main.cpp' lignes 71, 76, 126, 128, 219, 229, 222 et 223,
Valeurs magiques, délais et masques dans 'ecrire.cpp' lignes 14, 15, 20, 21 et 27,
etc.

Nom de fonctions:
Mélange Anglais et Français: 'getEtat' dans 'main.cpp'.


## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(0/1.0)__ |

Plusieurs commentaires inutiles. Ex: 'main.cpp' lignes 229, 248, 250, 270, 271, etc.

## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0.5/0.5)     |
| Indentation uniforme dans le programme       | (0/0.5)     |
| __Résultat partiel__                         | __(0.5/1.0)__ |

La structure n'est pas uniforme (accolades utilisées différemment à travers les différents fichiers). 

# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |    -0.5    |
| __Résultat partiel__                         | __(0.5/1.0)__ |

Les 150 lignes de logique dans votre 'main' manque de modularité. Vous devez séparer les différentes procédures, calculs et ajustements dans des fonctions, voir des classes dans différents fichiers. Cela rendrait le code beaucoup plus lisible et compréhensible.


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (1.5/1.5)     |
| Absence de fichiers inutiles                 | (1.5/1.5)     |
| __Résultat partiel__                         | __(3.0/3.0)__ |

## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (0/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.5/0.5)     |
| __Résultat partiel__                         | __(0.5/2.0)__ |
   
L'exécutable ne compile pas dû à une erreur d'inclusion ('ecrire.h' inclut 2 fois). Un '#pragma once' ou des header guards auraient pu régler le problème.

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 14.4/20__


# Basé sur le commit suivant
```
commit b0fc1385224b2550bce7bb307dbf947662e5455b
Author: Anas Barbouch <anas.barbouch@polymtl.ca>
Date:   Tue Apr 19 23:40:20 2022 -0400

    Commit final (espérons)
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`
```
make: Entering directory '/home/gigl/Bureau/corrections/inf1900-grader/projet/5776/projet/lib'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Interpreteur.cpp
In file included from Interpreteur.h:19,
                 from Interpreteur.cpp:11:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Pwm_T0.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c rs232.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Bouton.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
In file included from memoire_24.cpp:33:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Timer1.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Midi.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Del.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Timer2.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Interruption.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Timer0.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Moteur.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c debug.cpp
avr-ar -crs liba5776.a  Interpreteur.o can.o Pwm_T0.o rs232.o Bouton.o memoire_24.o Timer1.o Midi.o Del.o Timer2.o Interruption.o Timer0.o Moteur.o debug.o
make: Leaving directory '/home/gigl/Bureau/corrections/inf1900-grader/projet/5776/projet/lib'

```

## Sortie de `make` dans `projet/app`
```
make: Entering directory '/home/gigl/Bureau/corrections/inf1900-grader/projet/5776/projet/app'
avr-gcc -I. -I/usr/include/simavr  -MMD -I ../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
In file included from ecrire.h:16,
                 from suivi.h:16,
                 from main.cpp:18:
../lib/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
In file included from main.cpp:24:
ecrire.h:18:15: error: redefinition of 'const uint8_t VALEUR_FIN'
   18 | const uint8_t VALEUR_FIN = 255;
      |               ^~~~~~~~~~
In file included from suivi.h:16,
                 from main.cpp:18:
ecrire.h:18:15: note: 'const uint8_t VALEUR_FIN' previously defined here
   18 | const uint8_t VALEUR_FIN = 255;
      |               ^~~~~~~~~~
make: *** [Makefile:148: main.o] Error 1
make: Leaving directory '/home/gigl/Bureau/corrections/inf1900-grader/projet/5776/projet/app'

```
