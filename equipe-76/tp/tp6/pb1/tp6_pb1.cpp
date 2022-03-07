/*

Auteurs : Ryan Kezouh, Ilias Bakhbukh

Description du programme :  Ce programme implémente un capteur de type bouton. Le programme calcule le nombre de dixieme de seconde aucours duquel le bouton est enfoncé, puis affiche ce nombre
                            divisé par 2 sous forme de clignotements.

Identification matérielle : Le microcontrolleur utilisé est Atmega324a
                            La broche D2 est la seule entrée du circuit.
                            Less broches B0 et B1 sont les sorties.
*/

#define F_CPU 8000000UL  // 8 MHzs

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile bool siCompteurEnCours = false;

volatile bool siAppuye = false;
volatile bool siEnfonce = false;

const uint16_t DUREE_CTC = 8000000/1024/10;
const uint16_t NB_ITERS = 120;
volatile uint16_t compteur = 0;

const uint16_t ETEINT = 0;
const uint16_t ROUGE = 0x01;
const uint16_t VERT = 0x02;


void initExternal(){

    cli();

    EIMSK |= (1 << INT0);

    EICRA |= (0 << ISC01) | (1 << ISC00);

    sei();

}

void initTimer(uint16_t duree, int mode){
    
    cli();

    TCNT1 = 0;
    OCR1A = duree;
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12);
    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void stopTimer(){
    cli();

    TCNT1 = 0;
    OCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;

    TIMSK1 = 0;

    sei();
}

ISR(INT0_vect){

    if(!siAppuye){
        _delay_ms ( 30 );

        siEnfonce = !siEnfonce;

        if(siEnfonce){

            siCompteurEnCours = true;
            initTimer(DUREE_CTC, WGM12);
            compteur++;

        }else if(siCompteurEnCours){

            stopTimer();

            siCompteurEnCours = false;
            siAppuye = true;
        }

        EIFR |= (1 << INTF0) ;
    }
}

ISR(TIMER1_COMPA_vect){

    if(compteur < NB_ITERS){
        compteur++;
        initTimer(DUREE_CTC, WGM12);
    }else{
        siCompteurEnCours = false;
        siAppuye = true;
        stopTimer();
    }
}


int main(){

    initExternal();

    DDRB = 0xFF;
    DDRD = 0x00;

    while(true){

        if(!siCompteurEnCours && !siAppuye){

            PORTB = ETEINT;

        }else if(!siCompteurEnCours){

            PORTB = VERT;
            _delay_ms ( 500 );

            PORTB = ETEINT;
            _delay_ms ( 2000 );

            for(int clignotant_compteur=0; clignotant_compteur < compteur/2; clignotant_compteur++){
                PORTB = ROUGE;
                _delay_ms(250);
                PORTB = ETEINT;
                _delay_ms(250);
            }

            PORTB = VERT;
            _delay_ms(1000);

            compteur = 0;
            siCompteurEnCours = siEnfonce = siAppuye = false;
        }
    }

}