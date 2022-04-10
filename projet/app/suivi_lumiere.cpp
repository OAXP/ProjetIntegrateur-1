#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "debug.h"

const uint8_t ETEINT = 0x00;   // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;    // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;     // 0b00000001 Courant sur A0 pour avoir du VERT
const uint8_t DELAI_AMBRE = 3; // Délai en ms pour avoir la couleur ambre


uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}

int main()
{
    char tamponDebug[100];
    int debugTaille;
    can convertisseurAnalog;
    uint8_t lecturePhoto0; // Photorésistance droite
    uint8_t lecturePhoto1; // Photorésistance gauche
    DDRA &= ~(1 << PA3 | 1 << PA5);
    const uint8_t LIMITE_BASSE = 100; // Limite pour lumière basse et extrémité pour ambiante
    const uint8_t LIMITE_AMBIANTE = 200; // Limite pour lumière ambiante et extrémité pour hausse

    while (true)
    {
        lecturePhoto0 = convertionHuitBits(convertisseurAnalog.lecture(PA3));
        lecturePhoto1 = convertionHuitBits(convertisseurAnalog.lecture(PA5));
        
        debugTaille = sprintf(tamponDebug, "Gauche : %d ; Droite : %d\n", lecturePhoto1, lecturePhoto0);
        DEBUG_PRINT(tamponDebug, debugTaille);

        _delay_ms(200);
    }
    return 0;
}