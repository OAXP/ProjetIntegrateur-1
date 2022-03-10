#include <avr/io.h>
#include <avr/interrupt.h>

class Timer0 {

public :

    Timer0(uint8_t mode, uint16_t duree);
    void arreter();

}