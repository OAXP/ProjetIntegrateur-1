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
//#include "Timer2.h"

// Constantes pour couleurs
const uint8_t ETEINT = 0x00;   // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;    // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;     // 0b00000001 Courant sur A0 pour avoir du VERT
const uint8_t DELAI_AMBRE = 3; // Délai en ms pour avoir la couleur ambre

// Clignotement de DEL à 5Hz pour 3 secondes
const uint8_t DELAI_CLIGNOTANT = 100; // 100ms vient de la période (200ms) divisée par 2

// Classes utilisées
Moteur moteur;
can convertisseurAnalog;
Del del(&PORTA, PA0, PA1);
Bouton boutonInt(&PIND, PD2);
Bouton boutonBlanc(&PINA, PA6);
Memoire24CXXX memoire;
//uint8_t reprise[1000];
//uint16_t iterateurReprise = 0;
//Timer2 timer2; // À corriger pour respecter le constructor de la class

// Variables pour Debug
char tamponDebug[100];
int debugTaille;

// Variables d'information sur le robot
char signeMoteurG = ' ';
char signeMoteurD = ' ';
uint8_t lecturePhotoD; // Photorésistance droite
uint8_t lecturePhotoG; // Photorésistance gauche
uint8_t lectureCapteur;
uint8_t pourcentageMoteurG = 0;
uint8_t pourcentageMoteurD = 0;
uint8_t distanceMurCm = 0;
volatile uint16_t addresse = 0x0000;
bool murDetecte;


ISR(TIMER1_COMPA_vect)
{
    //ecrire_memoire(memoire, moteur.getPourcentageG(), moteur.getPourcentageD(), addresse);
    uint8_t pwm = combine(pourcentageMoteurG, pourcentageMoteurD);
    memoire.ecriture(addresse, pwm); // addresse: (8bit) pourcentageMoteurG/10 | pourcentageMoteurD/10
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
    // Réglage des entrées/sorties
    DDRA &= ~(1 << PA2 | 1 << PA3 | 1 << PA5);

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
            partirMinuterie1(781); //ctc, écriture chaque ~100ms
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

            if(estFini) {
                // Del reste verte
            }
            else {
                // Lire mémoire et refaire parcours
                addresse = 0;
                uint8_t lectureMemoire;
                
                while(true) {
                    memoire.lecture(addresse, &lectureMemoire);
                    if(lectureMemoire == 255) {
                        estFini = true;
                        moteur.arreter();
                        del.appliquerVertDel();
                        break;
                    }
                    dechiffrer_donnee(lectureMemoire, pourcentageMoteurG, pourcentageMoteurD);
                    moteur.directionPersonnalisee(pourcentageMoteurG, pourcentageMoteurD, 0, 0);
                    _delay_ms(100);
                    addresse++;

                    /*for (uint16_t i = 0; i < 1000; i++)
                    {
                        memoire.lecture(addresse, &lectureMemoire);
                        addresse++;
                        _delay_ms(5);
                        if(lectureMemoire == 255) {
                            reprise[i] = 255;
                            break;
                        }
                        reprise[i] = lectureMemoire;
                    }

                    for (uint16_t i = 0; i < 1000; i++)
                    {
                        if(reprise[i] == 255) {
                            estFini = true;
                            moteur.arreter();
                            del.appliquerVertDel();
                            break;
                        }
                        dechiffrer_donnee(reprise[i], pourcentageMoteurG, pourcentageMoteurD);
                        moteur.directionPersonnalisee(pourcentageMoteurG, pourcentageMoteurD, 0, 0);
                        _delay_ms(100);
                    }*/
                }
            }

        } 
        else {

            if(estFini) {
                // À voir
            }
            else {

                murDetecte = suivre_mur(moteur, lectureCapteur);

                if(estArrete) {

                    if(boutonBlanc.getEtat() == Bouton::Etat::RELACHE){

                        // Parcours à enregistrer terminé
                        arreterMinuterie1();
                        indiquer_fin_memoire(memoire, addresse); // Indiquer dans la mémoire la fin de l'enregistrement
                        //reprise[iterateurReprise] = 255;

                        _delay_ms(1000); // Robot ne fait rien pendant 1 sec

                        effectuerDemiTour(); // TODO Revoir pour mur
                    }

                    if(boutonInt.getEtat() == Bouton::Etat::RELACHE){

                        estFini = true;

                        del.appliquerRougeDel();
                        // Processus à effectuer
                        arreterMinuterie1();
                        indiquer_fin_memoire(memoire, addresse); // Indiquer dans la mémoire la fin de l'enregistrement
                        /*reprise[iterateurReprise] = 255;
                        addresse = 0;
                        for (uint16_t i = 0; i < 1000; i++)
                        {
                            memoire.ecriture(addresse, reprise[i]);
                            if(reprise[i] == 255){
                                break;
                            }
                            addresse++;
                        }*/
                        
                        del.appliquerVertDel(); // Pour indiquer que la fin
                        break;
                    }

                }
                if(!murDetecte) {
                    suivre_lumiere(moteur, lecturePhotoG, lecturePhotoD); // Si ça bouge déjà avec le Mur, ne pas faire ça
                }
                /*
                if(iterateurReprise < 1000) {
                    reprise[iterateurReprise] = combine(moteur.getPourcentageG(), moteur.getPourcentageD());
                    iterateurReprise++;
                }*/
                _delay_ms(15);
                // ecrire_memoire(memoire, moteur.getPourcentageG(), moteur.getPourcentageD(), addresse);
                // _delay_ms(25.6);
                
            }

        }

    }

    return 0;
}
