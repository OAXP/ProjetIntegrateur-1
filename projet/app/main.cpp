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
#include "Bouton.h"
#include "Del.h"
#include "debug.h"

// Constantes pour couleurs
const uint8_t ETEINT = 0x00;   // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;    // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;     // 0b00000001 Courant sur A0 pour avoir du VERT
const uint8_t DELAI_AMBRE = 3; // Délai en ms pour avoir la couleur ambre

// Clignotement de DEL à 5Hz pour 3 secondes
const uint8_t DELAI_CLIGNOTANT = 100; // 100ms vient de la période (200ms) divisée par 2

void clignoterDel(Del& del, bool estRouge) {

    // 15 itérations, car 3000ms / 200ms = 15
    for (uint8_t i = 0; i < 15; i++)
    {
        if(estRouge) {
            del.appliquerRougeDel();
        } else {
            del.appliquerVertDel();
        }
        _delay_ms(DELAI_CLIGNOTANT);
        del.appliquerEteintDel();
        _delay_ms(DELAI_CLIGNOTANT);
    }
    
}

int main() {
    // Classes utilisées
    Moteur moteur;
    can convertisseurAnalog;
    Del del(&PORTA, PA0, PA1);
    Bouton boutonInt(&PIND, PD2);
    Bouton boutonBlanc(&PINA, PA6);

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

    // Variables de fonctionnement du robot
    bool estModeReprise = false;
    bool estFini = false;
    bool estArrete = true;


    while (true)
    {
        if(boutonBlanc.getEtat() == Bouton::Etat::RELACHE){
            clignoterDel(del, true); // mode reprise
            estModeReprise = true;
            break;
        }

        if(boutonInt.getEtat() == Bouton::Etat::RELACHE){
            clignoterDel(del, false); // mode parcours
            estModeReprise = false;
            break;
        }
    }

    while(true) {
        
         // Lecture des moteurs
        pourcentageMoteurG = moteur.getPourcentageG();
        pourcentageMoteurD = moteur.getPourcentageD();
        signeMoteurG = moteur.getDirectionG() ? '-' : ' ';
        signeMoteurD = moteur.getDirectionD() ? '-' : ' ';
        estArrete = (pourcentageMoteurG == 0 && pourcentageMoteurD == 0);

        // Lecture des capteurs de photorésistances
        lecturePhotoD = convertionHuitBits(convertisseurAnalog.lecture(PA3));
        lecturePhotoG = convertionHuitBits(convertisseurAnalog.lecture(PA5));

        // Lecture du capteur de distance
        distanceMurCm = 10; // TODO remplacer 10 par la variable appropriée

        // Debugage des valeurs
        debugTaille = sprintf(tamponDebug, 
            "V(%1c%3d, %1c%4d)  D(%2d)  P(%3d, %3d)\n", 
            signeMoteurG, pourcentageMoteurG, // V(a)
            signeMoteurD, pourcentageMoteurD, // V(b)
            distanceMurCm, // D(c)
            lecturePhotoG, lecturePhotoD // P(d, e)
        );
        DEBUG_PRINT(tamponDebug, debugTaille);

        if(estModeReprise) {

            if(estFini) {
                del.appliquerVertDel();
            }
            else {
                // Lire mémoire et refaire parcours
            }

        } 
        else {

            if(estFini) {
                // À voir
            }
            else {

                if(estArrete) {

                    if(boutonBlanc.getEtat() == Bouton::Etat::RELACHE){
                        _delay_ms(1000); // Robot ne fait rien pendant 1 sec
                        // TODO Faire Demi-tour en U et mettre DEL ambrée
                        break;
                    }

                    if(boutonInt.getEtat() == Bouton::Etat::RELACHE){
                        estFini = true;
                        del.appliquerRougeDel();
                        // Enregistrer le parcours en mémoire
                        del.appliquerVertDel(); // Pour indiquer que l'écriture est terminée
                        break;
                    }

                }

                suivre_lumiere(moteur, lecturePhotoG, lecturePhotoD); // Vérifier si ça marche avec Mur déjà

            }

        }

    }

    return 0;
}