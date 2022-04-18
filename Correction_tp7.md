# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 3
+ Équipe #   : 5776
+ Correcteur : Charles Jiang

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (3.25/5.0)      |
| La qualités de vos modifications aux Makefiles           | (4.75/5.0)      |
| __Résultat partiel__                                     | __(8/10.0)__ |

## **PORTION DE CODE**

moteur :


minuterie:
 -.25 prescaler non modifiable set a 8 qui est tres bas pour des secondes
 -.25 valeur OCR0B inutile (meme coupler avec PWM_T0, pas besoin de le set)
 -.25 mieux d'utiliser un enum class pour modeDeFonctionnement au lieu de 0/1 pour Fast PWM et le mode CTC.

interruption:
 -.5 code dupliqué, seule différence par méthode est le EIMSK et EICRA que vous pouvez passez en paramètre / enum class pour mode
 -.25 commentaires dupliqué inutile 
 -.25 non possible de changer configuration sensibilité interruption EICRA
 


## **Makefile**
makefile lib:
 -0.25 il faut utiliser avr-ar au lieu de ar (specifier compilateur avr)

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (/2.0)     |
| Explications claires avec un bon niveau de détails                          | (/2.0)     |
| Bon français                                                                | (/1.0)     |
| __Résultat partiel__                                                        | __(7/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| etc                      |            |
| __Résultat partiel__     | __(2/3.0)__ |

-0.5 warning exec (Bouton)
-0.5 warning lib

# Résultat

__Total des points: 17.0/20__

# Commentaires du correcteur:

À remplir par l'évaluateur


# Basé sur le commit suivant
```
commit d70c5796395c359b6f3f0ec716eec4a0e283b88f
Author: Anas Barbouch <anas.barbouch@polymtl.ca>
Date:   Sun Mar 13 16:58:50 2022 -0400

    Modification du main et ajout du rapport
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make : on entre dans le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5776/tp/tp7/lib »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Timer0.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Pwm_T0.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c rs232.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Bouton.cpp
In file included from Bouton.h:10,
                 from Bouton.cpp:9:
/usr/avr/include/util/delay.h:92:3: warning: #warning "F_CPU not defined for <util/delay.h>" [-Wcpp]
   92 | # warning "F_CPU not defined for <util/delay.h>"
      |   ^~~~~~~
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
In file included from memoire_24.cpp:34:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
memoire_24.cpp: In member function 'uint8_t Memoire24CXXX::lecture(uint16_t, uint8_t*, uint8_t)':
memoire_24.cpp:280:7: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
  280 |       while ((TWCR & _BV(TWINT)) == 0) ; // Attente de fin de transmission
      |       ^~~~~
memoire_24.cpp:281:10: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
  281 |          *donnee++ = TWDR;               // Lecture
      |          ^
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Timer1.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Del.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Interruption.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Moteur.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c debug.cpp
ar -crs liba5776.a  Timer0.o can.o Pwm_T0.o rs232.o Bouton.o memoire_24.o Timer1.o Del.o Interruption.o Moteur.o debug.o
make : on quitte le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5776/tp/tp7/lib »

```

## Sortie de `make` dans `tp/tp7/exec`
```
make : on entre dans le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5776/tp/tp7/exec »
avr-gcc -I. -I/usr/include/simavr  -MMD -I ../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
main.cpp: In function 'int main()':
main.cpp:16:9: warning: variable 'debugTaille' set but not used [-Wunused-but-set-variable]
   16 |     int debugTaille;
      |         ^~~~~~~~~~~
avr-gcc -Wl,-Map,tp7.elf.map -mmcu=atmega324pa -o tp7.elf  main.o \
-lm -L ../lib -l a5776
avr-objcopy -j .text -j .data \
	-O ihex tp7.elf tp7.hex
make : on quitte le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5776/tp/tp7/exec »

```
