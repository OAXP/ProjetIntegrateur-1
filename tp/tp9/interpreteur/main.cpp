/**
 * @file main.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier lit les instructions dans la mémoire et utilise l'interpreteur pour les éxecuter. (Tests faits par Ryan et Ilias)
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "rs232.h"
#include "memoire_24.h"
#include "Interpreteur.h"


int main(){
    Midi sonnerie;
    Interpreteur interpreteur;
    Memoire24CXXX memoire;
    uint8_t code;
    uint16_t addresse = 0;
    
    // joue la mélodie suivante pour démarrer : https://www.youtube.com/watch?v=0VZghMkvN6c
    sonnerie.jouerNote(64);
    _delay_ms(500);
    sonnerie.jouerNote(68);
    _delay_ms(500);
    sonnerie.jouerNote(63);
    _delay_ms(500);
    sonnerie.jouerNote(68);
    _delay_ms(500);
    sonnerie.arreterNote();

    // Lecture de la mémoire et interprétation des instructions
    while(true) {
        memoire.lecture(addresse, &code);
        interpreteur.faire(code, addresse);
    }
    
}
