/**
 * @file main.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier écrit est le main.
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "suivi_lumiere.h"
#include "debug.h"

int main() {
    // Classes utilisées
    Moteur moteur;
    can convertisseurAnalog;

    // Variables pour Debug
    char tamponDebug[100];
    int debugTaille;

    // Variables d'information sur le robot
    char signeMoteurG = ' ';
    char signeMoteurD = ' ';
    uint8_t lecturePhotoD; // Photorésistance droite
    uint8_t lecturePhotoG; // Photorésistance gauche
    uint8_t pourcentageMoteurG = 0;
    uint8_t pourcentageMoteurD = 0;
    uint8_t distanceMurCm = 0;

    // Réglage des entrées/sorties
    DDRA &= ~(1 << PA3 | 1 << PA5);

    while(true) {
        // Lecture des moteurs
        pourcentageMoteurG = moteur.getPourcentageG();
        pourcentageMoteurD = moteur.getPourcentageD();
        signeMoteurG = moteur.getDirectionG() ? '-' : ' ';
        signeMoteurD = moteur.getDirectionD() ? '-' : ' ';

        // Lecture des capteurs de photorésistances
        lecturePhotoD = convertionHuitBits(convertisseurAnalog.lecture(PA3));
        lecturePhotoG = convertionHuitBits(convertisseurAnalog.lecture(PA5));

        // Debugage des valeurs
        debugTaille = sprintf(tamponDebug, 
            "V(%1c%3d, %1c%4d)  D(%2d)  P(%3d, %3d)\n", 
            signeMoteurG, pourcentageMoteurG, // V(a)
            signeMoteurD, pourcentageMoteurD, // V(b)
            distanceMurCm, // D(c)
            lecturePhotoG, lecturePhotoD // P(d, e)
        );
        DEBUG_PRINT(tamponDebug, debugTaille);

        suivre_lumiere(moteur, lecturePhotoG, lecturePhotoD); // Vérifier si ça marche avec Mur déjà
    }

    return 0;
}