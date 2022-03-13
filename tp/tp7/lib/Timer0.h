#include <avr/io.h>
#include <avr/interrupt.h>

class Timer0 {

public :

    Timer0(uint8_t modeDeFonctionnement, uint16_t duree);
    void initialiser(uint8_t modeDeFonctionnement, uint16_t duree);
    void arreter();

};