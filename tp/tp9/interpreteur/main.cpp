#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Midi.h"
#include "rs232.h"
#include "memoire_24.h"


int main(){
    Midi sonnerie;
    
    while (true)
    { // joue la mélodie suivante : https://www.youtube.com/watch?v=0VZghMkvN6c
        sonnerie.jouerNote(64);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(500);
        sonnerie.jouerNote(64);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(500);
        sonnerie.jouerNote(64);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(500);
        sonnerie.jouerNote(64);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(500);
        sonnerie.jouerNote(63);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(500);
        sonnerie.jouerNote(63);
        _delay_ms(500);
        sonnerie.jouerNote(68);
        _delay_ms(300);
        sonnerie.jouerNote(63);
        _delay_ms(300);
        sonnerie.jouerNote(64);
        _delay_ms(300);
        sonnerie.jouerNote(64);
        _delay_ms(300);
        sonnerie.jouerNote(63);
        _delay_ms(300);
        sonnerie.jouerNote(64);
        _delay_ms(300);
        sonnerie.jouerNote(68);
        _delay_ms(700);
    }
    
    
}
