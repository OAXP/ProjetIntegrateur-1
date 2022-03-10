#include "timer0.h"

Timer0::Timer0(uint8_t mode, uint16_t duree){

    cli();

    TCNT1 = 0;

    OCR1A = duree;

    switch (mode){
        case 0 :    
            TCCR1A |= (1 << WGM10) | (1 << WGM11); 
            TCCR1B |= (1 << WGM13) | (1 << CS12) | (1 << CS10);
            TCCR1C = 0;
            break;
        case 1 :
            TCCR1A = 0; 
            TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
            TCCR1C = 0;
            break;
    }

    TIMSK1 |= (1 << OCIE1A);

    sei();

}

void Timer0::arreter(){

    cli();

    TCNT1 = 0;
    OCR1A = 0;
    TCCR1A = 0; 
    TCCR1B = 0;

    TIMSK1 = 0;

    sei();

}