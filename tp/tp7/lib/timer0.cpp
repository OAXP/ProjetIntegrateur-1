#include "timer0.h"

Timer0::Timer0(uint8_t mode, uint16_t duree){

    cli();

    TCNT0 = 0;

    OCR0A = duree;

    if(mode == 0){
        TCCR0A |= (1 << WGM00); 
        TCCR0B |= (1 << WGM02) | (1 << CS12) | (1 << CS10);
        TCCR0C = 0;
    }

    TIMSK0 |= (1 << OCIE0A);

    sei();

}

void Timer0::arreter(){

    cli();

    TCNT0 = 0;
    OCR0A = 0;
    TCCR0A = 0; 
    TCCR0B = 0;
    TCCR0C = 0;

    TIMSK0 = 0;

    sei();

}