# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 57
+ Correcteur : Charles Jiang

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |      -1      |
| __Résultat partiel__                         | __(0.5/1.5)__ |

pb1/pb2: une couleur n'est pas un etat, c'est plutot une sortie

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0/0.5)     |
| Noms de variables décrivent l'intention      | (/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
| __Résultat partiel__                         | __(1/1.5)__ |

pb1/pb2 indiquer variable pour 10 (delay)

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
|                                                     x
| __Résultat partiel__                         | __(0.5/1.0)__ |

trop de commentaire non pertinent : ex: pb1 ligne 50, 56, 60,62,77 etc.


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(1/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/1.0)__ |

dans estAppuye(), il est possible d'enlever le 2eme if (PIND & masque) puisque le while () verifie de toute facon apres


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 18.0/20__

# Commentaires du correcteur:



# Basé sur le commit suivant
```
commit edd6d5117e79fd1fe30ed3b467785b7a54aae94e
Merge: b792c4a 09476a0
Author: Andy Tran <andy.tran@polymtl.ca>
Date:   Sun Jan 30 00:07:52 2022 -0500

    Merge branch 'master' of https://githost.gi.polymtl.ca/git/inf1900-57
    
    merge
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/57/tp/tp2/pb1 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c tp2_pb1.cpp
avr-gcc -Wl,-Map,tp2_pb1.elf.map -mmcu=atmega324pa -o tp2_pb1.elf  tp2_pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex tp2_pb1.elf tp2_pb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/57/tp/tp2/pb1 »

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/57/tp/tp2/pb2 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c tp2_pb2.cpp
avr-gcc -Wl,-Map,tp2_pb2.elf.map -mmcu=atmega324pa -o tp2_pb2.elf  tp2_pb2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex tp2_pb2.elf tp2_pb2.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/57/tp/tp2/pb2 »

```
