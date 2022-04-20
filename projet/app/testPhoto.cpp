/**
 * @file testPhoto.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier (non utilisé, à part pour tests) est un fichier test pour les photorésistances.
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000
#define DEBUG

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "debug.h"
#include "can.h"

// Classes utilisées
can convertisseurAnalog;

// Variables pour Debug
char tamponDebug[100];
int debugTaille;

// Variables d'information sur le robot
uint8_t lecturePhotoD; // Photorésistance droite
uint8_t lecturePhotoG; // Photorésistance gauche


uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}


int main() {
    // Réglage des entrées/sorties
    DDRA &= ~(1 << PA3 | 1 << PA5);

    // Variables de fonctionnement du robot
    bool estModeReprise = false;
    bool estFini = false;
    bool estArrete = true;

    while(true) {

        // Lecture des capteurs de photorésistances
        lecturePhotoD = convertionHuitBits(convertisseurAnalog.lecture(PA3));
        lecturePhotoG = convertionHuitBits(convertisseurAnalog.lecture(PA5));

        // Debugage des valeurs
        debugTaille = sprintf(tamponDebug, 
            "P(%3d, %3d)\n",
            lecturePhotoG, lecturePhotoD // P(d, e)
        );
        DEBUG_PRINT(tamponDebug, debugTaille);

    }

    return 0;
}
