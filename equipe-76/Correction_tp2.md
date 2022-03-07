# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 76
+ Correcteur : Charles Jiang

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |     -1.5       |
| __Résultat partiel__                         | __(0/1.5)__ |

trop d'etats non necessaires pour pb1/pb2¡ au lieu d'un etat pour verifier le relachement, utilisez plutot des methodes 
qui verifient le relachement

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.3/0.5)     |
| Noms de variables décrivent l'intention      | (/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
|  etc                                               x
| __Résultat partiel__                         | __(1.2/1.5)__ |

-0.1 registre int delEteint = 0x00; devrait utiliser uint8_t 
-0.2 chiffre magique (0x08/0x04) a mettre dans des variables 

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


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
| Absence de code dupliqué                     |     x       |
| etc                                          |            |
| __Résultat partiel__                         | __(0.5/1.0)__ |

absence de fonctions

beaucoup de duplication de code, vous pouvez combiner dans une fonction qui prend des valeurs du bit SHIFT et State en parametre
if(PIND & 0x04){
	etatPresent = E3;
}


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |    x        |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(3/4.0)__ |

trop d'etat non pertinents -1

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


to check long press.

# Résultat

__Total des points: 16.7/20__

# Commentaires du correcteur:



# Basé sur le commit suivant
```
commit 094f78c385e6acff5d60ba65986e9f5afdd28944
Author: Ryan Kezouh <ryan.kezouh@polymtl.ca>
Date:   Sun Jan 30 16:22:32 2022 -0500

    mise a jour
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/76/tp/tp2/pb1 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c code_pb1.cpp
avr-gcc -Wl,-Map,code_pb1.elf.map -mmcu=atmega324pa -o code_pb1.elf  code_pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex code_pb1.elf code_pb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/76/tp/tp2/pb1 »

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/76/tp/tp2/pb2 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c code_pb2.cpp
avr-gcc -Wl,-Map,code_pb2.elf.map -mmcu=atmega324pa -o code_pb2.elf  code_pb2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex code_pb2.elf code_pb2.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/76/tp/tp2/pb2 »

```
