#include <avr/io.h>
#include <avr/interrupt.h>

class Timer1 {

public :

    Timer1(uint8_t modeDeFonctionnement, uint16_t duree);
    void initialiser(uint8_t modeDeFonctionnement, uint16_t duree);
    void arreter();

};