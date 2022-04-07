
/**
 * @file Timer0.cpp
 * @author Ilias Bakhbukh (ilias.bakhbukh@polymtl.ca)
 * @brief Classe Timer0 permet de contrôler le timer 0,
 * elle donne accès aux modes Fast PWM et CTC
 * @date 2022-03-13
 */

#include "Timer0.h"

Timer0::Timer0(uint8_t modeDeFonctionnement, uint16_t duree){

    initialiser(modeDeFonctionnement, duree);

}

void Timer0::initialiser(uint8_t modeDeFonctionnement, uint16_t duree){
    cli();

    TCNT0 = 0;

    OCR0A = duree;
    OCR0B = duree;

    switch (modeDeFonctionnement){
        case 0 :    
            TCCR0A |= (1 << WGM00) | (1 << WGM01); 
            break;
        case 1 :
            TCCR0A |= (1 << WGM01); 
            break;
        default :    
            TCCR0A |= (1 << WGM00) | (1 << WGM01);
    }


    TCCR0A |= (1 << COM0A1)| (1 << COM0B1);

    TCCR0B |= (1 << CS01);

    TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B);

    sei();
}

void Timer0::arreter(){

    cli();

    TCNT0 = 0;
    OCR0A = 0;
    OCR0B = 0;
    TCCR0A = 0; 
    TCCR0B = 0;

    TIMSK0 = 0;

    sei();

}