#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Midi.h"
#include <avr/interrupt.h>

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
