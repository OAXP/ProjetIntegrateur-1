
/**
 * @file Timer2.cpp
 * @author Ilias Bakhbukh (ilias.bakhbukh@polymtl.ca)
 * @brief Classe Timer2 permet de contrôler le timer 2,
 * elle donne accès aux modes Fast PWM et CTC
 * @date 2022-03-13
 */

#include "Timer2.h"

Timer2::Timer2(uint8_t modeDeFonctionnement, uint16_t duree){

    initialiser(modeDeFonctionnement, duree);

}

void Timer2::initialiser(uint8_t modeDeFonctionnement, uint16_t duree){
    cli();

    TCNT2 = 0;

    OCR2A = duree;
    OCR2B = duree;

    switch (modeDeFonctionnement){
        case 0 :    
            TCCR2A |= (1 << WGM20) | (1 << WGM21); 
            break;
        case 1 :
            TCCR2A |= (1 << WGM21); 
            break;
        default :    
            TCCR2A |= (1 << WGM20) | (1 << WGM21);
    }


    TCCR2A |= (1 << COM2A1)| (1 << COM2B1);

    TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); // 1024 prescaler

    TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);

    sei();
}

void Timer2::arreter(){

    cli();

    TCNT2 = 0;
    OCR2A = 0;
    OCR2B = 0;
    TCCR2A = 0; 
    TCCR2B = 0;

    TIMSK2 = 0;

    sei();

}