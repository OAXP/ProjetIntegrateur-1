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
    // Rs232 rs232;
    
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

    while(true) {
        memoire.lecture(addresse, &code);
        interpreteur.faire(code, addresse);
    }
    
}
