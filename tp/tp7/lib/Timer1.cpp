#include "Timer1.h"

Timer1::Timer1(uint8_t modeDeFonctionnement, uint16_t duree){

    initialiser(modeDeFonctionnement, duree);

}

void Timer1::initialiser(uint8_t modeDeFonctionnement, uint16_t duree){

    cli();

    TCNT1 = 0;

    OCR1A = duree;
    OCR1B = duree;

    switch (modeDeFonctionnement){
        case 0 :    
            TCCR1A |= (1 << WGM10); 
            TCCR1B |= (1 << WGM12);
            break;
        case 1 :
            TCCR1A = 0; 
            TCCR1B |= (1 << WGM12);
            break;
        default : 
            TCCR1A |= (1 << WGM10); 
            TCCR1B |= (1 << WGM12);
    }

    
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    TCCR1B |= (1 << CS11); // définir le prescaler

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void Timer1::arreter(){

    cli();

    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A = 0; 
    TCCR1B = 0;
    TCCR1C = 0;

    TIMSK1 = 0;

    sei();

}