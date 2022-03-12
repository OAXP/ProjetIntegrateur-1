/**
 * @file Interruption.cpp
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Interruption pour initialiser les interruptions externes
 * INT0, INT1 ou/et INT2.
 * @date 2022-03-12
 * 
 */

#include "Interruption.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void Interruption::initInt0() {
    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC01);

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

void Interruption::initInt1() {
    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT1) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC11);

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

void Interruption::initInt2() {
    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT2) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC21);

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}