#define F_CPU 8000000
#include "Midi.h"

Midi::Midi() {
    DDRD |= (1 << PD4) | (1 << PD5);
    cli();
    TCNT1 = 0;
    
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // définir le prescaler clk/8mhz et CTC
    TCCR1C = 0;
    sei();
}

void Midi::jouerNote(uint8_t note) { // note doit être entre 45 et 81

    if(note >= 45 && note <= 81) {
        // fonction prise du site https://www.music.mcgill.ca/~gary/307/week1/node28.html
        double freq = 440 * pow(2, (note-69.0)/12);

        // formule prise de la documentation de Atmel à la page 120
        OCR1A = (F_CPU/(2.0*8*freq)) - 1;
    }

}

void Midi::arreterNote() {
    OCR1A = 0;
}