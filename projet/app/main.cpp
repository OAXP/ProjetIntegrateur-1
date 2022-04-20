/**
 * @file main.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier gère tout le fonctionnement du robot et lie les classes entres elles.
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "suivi.h"
#include "Bouton.h"
#include "Del.h"
#include "debug.h"
#include "memoire_24.h"
#include "can.h"
#include "ecrire.h"

// Constantes de couleurs
const uint8_t DELAI_AMBRE = 3; // Délai en ms pour avoir la couleur ambre

// Clignotement de DEL à 5Hz pour 3 secondes
const uint8_t DELAI_CLIGNOTANT = 100; // 100ms vient de la période (200ms) divisée par 2

// Constantes en rapport avec la mémoire et le suivi
const uint8_t DELAI_MEMOIRE = 100;
const uint16_t DELAI_ECRITURE = 781;
const uint8_t DELAI_SUIVI = 15;
const uint8_t INDICE_DIRECTION = 110;

// Classes utilisées
Moteur moteur;
can convertisseurAnalog;
Del del(&PORTA, PA0, PA1);
Bouton boutonInt(&PIND, PD2);
Bouton boutonBlanc(&PINA, PA6);
Memoire24CXXX memoire;

// Variables pour Debug
char tamponDebug[100];
int debugTaille;

// Variables d'information sur le robot
char signeMoteurG = ' ';
char signeMoteurD = ' ';
uint8_t lecturePhotoD; // Photorésistance droite
uint8_t lecturePhotoG; // Photorésistance gauche
uint8_t lectureCapteur;
volatile uint8_t pourcentageMoteurG = 0;
volatile uint8_t pourcentageMoteurD = 0;
uint8_t distanceMurCm = 0;
volatile uint16_t addresse = 0x0000;
bool murDetecte;


// Début partie écriture en mémoire
ISR(TIMER1_COMPA_vect)
{
    // Écriture en mémoire du PWM gauche puis droit
    // Le +110 indique que le PWM est dans la direction arrière

    uint8_t pwmG = (moteur.getDirectionG()) ? pourcentageMoteurG + INDICE_DIRECTION : pourcentageMoteurG;
    memoire.ecriture(addresse, pwmG); // addresse: (8bit) pourcentageMoteurG
    _delay_ms(5);
    addresse++;

    uint8_t pwmD = (moteur.getDirectionD()) ? pourcentageMoteurD + INDICE_DIRECTION : pourcentageMoteurD;
    memoire.ecriture(addresse, pwmD); // addresse: (8bit) pourcentageMoteurD/10
    _delay_ms(5);
    addresse++;
}

void partirMinuterie1 (uint16_t duree) {
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    cli();
    TCNT1 = 0;
    OCR1A = duree;

    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12); // définir le prescaler clk/8mhz et CTC
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A); // Pour créer une interruption avec le flag OCIE1A

    sei();
}


void arreterMinuterie1 () {
    cli();
    TCCR1B &= ~(1 << CS10);
    TCCR1B &= ~(1 << CS12);
    OCR1A = 0;
    sei();
}
// Fin partie écriture en mémoire

// Clignotement de DEL 3 secondes
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

// Effectue un demi tour puis suit le mur
void effectuerDemiTour() {

    moteur.directionPersonnalisee(100,55,0,0);

    for (int i = 0; i < 500; i++)
    {
        del.appliquerRougeDel();
        _delay_ms(DELAI_AMBRE);
        del.appliquerVertDel();
        _delay_ms(DELAI_AMBRE);
    }

    moteur.arreter();
    del.appliquerEteintDel();
}


int main() {
    // Réglage des entrées/sorties pour Photorésistances et Capteur infrarouge
    DDRA &= ~(1 << PA2 | 1 << PA3 | 1 << PA5);

    // Variables de fonctionnement du robot
    bool estModeReprise = false;
    bool estFini = false;
    bool estArrete = true;


    // Choix du mode parcours ou reprise
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
            partirMinuterie1(DELAI_ECRITURE); //ctc, écriture chaque ~100ms
            break;
        }
    }

    // Débugage et traitement du mode choisi
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
        lectureCapteur = convertionHuitBits(convertisseurAnalog.lecture(PA2));
        distanceMurCm = (uint8_t) (2998.8 * pow(lectureCapteur, (-1.173))); // Fonction prise de https://www.makerguides.com/sharp-gp2y0a21yk0f-ir-distance-sensor-arduino-tutorial/

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

            if(!estFini) {
                // Lire mémoire et refaire parcours
                addresse = 0;
                uint8_t lectureMemoireG;
                bool directionG;
                uint8_t lectureMemoireD;
                bool directionD;
                
                while(true) {
                    memoire.lecture(addresse, &lectureMemoireG);
                    addresse++;
                    memoire.lecture(addresse, &lectureMemoireD);

                    if(lectureMemoireG == VALEUR_FIN || lectureMemoireD == VALEUR_FIN) {
                        estFini = true;
                        moteur.arreter();
                        del.appliquerVertDel();
                        break;
                    }

                    // Traite les valeurs pour les roues
                    pourcentageMoteurG = (lectureMemoireG > 100) ? lectureMemoireG - INDICE_DIRECTION : lectureMemoireG;
                    directionG = (lectureMemoireG > 100);

                    pourcentageMoteurD = (lectureMemoireD > 100) ? lectureMemoireD - INDICE_DIRECTION : lectureMemoireD;
                    directionD = (lectureMemoireD > 100);

                    // Applique les pourcentages et la direction de chaque roue
                    moteur.directionPersonnalisee(pourcentageMoteurG, pourcentageMoteurD, directionG, directionD);

                    // Délai pour aller avec la mémoire
                    _delay_ms(DELAI_MEMOIRE);

                    addresse++;
                }
            }

        } 
        else {

            if(!estFini) {

                murDetecte = suivreMur(moteur, lectureCapteur);

                if(estArrete) {

                    if(boutonBlanc.getEtat() == Bouton::Etat::RELACHE){

                        // Parcours à enregistrer terminé
                        arreterMinuterie1();
                        indiquerFinMemoire(memoire, addresse); // Indiquer dans la mémoire la fin de l'enregistrement

                        _delay_ms(1000); // Robot ne fait rien pendant 1 sec

                        effectuerDemiTour(); // TODO Revoir pour mur
                    }

                    if(boutonInt.getEtat() == Bouton::Etat::RELACHE){

                        estFini = true;

                        del.appliquerRougeDel();

                        arreterMinuterie1();
                        indiquerFinMemoire(memoire, addresse); // Indiquer dans la mémoire la fin de l'enregistrement
                        
                        del.appliquerVertDel(); // Pour indiquer que la fin
                        break;
                    }

                }
                if(!murDetecte) {
                    suivreLumiere(moteur, lecturePhotoG, lecturePhotoD); // Si ça bouge déjà avec le Mur, ne pas faire ça
                }
                
                // Délai entre chaque suivi
                _delay_ms(DELAI_SUIVI);
                
            }

        }

    }

    return 0;
}
