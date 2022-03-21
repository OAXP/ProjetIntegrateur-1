#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>

class Midi {
    public:
    Midi();
    void jouerNote(uint8_t note);
    void arreterNote();
};