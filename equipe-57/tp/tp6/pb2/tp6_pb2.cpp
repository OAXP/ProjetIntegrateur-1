/*
Auteurs : Anas Barbouch (2143541) et Andy Tran (2146959)

Description : La DEL est rouge si la photorésistance détecte une lumière forte (>=LIMITE_AMBIANTE).
Si la photorésistance détecte une lumière ambiante (>LIMITE_BASSE et <LIMITE_AMBIANTE), la DEL prend la couleur ambre.
Si la photorésistance détecte une lumière faible (<=LIMITE_BASSE), la DEL passe au Vert.

Broches en mode sortie utilisées : B0, B1
Broches en mode entrée utilisées : A0
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

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
    can convertisseurAnalog;
    uint8_t lectureCan;
    DDRB = 0xFF;
    DDRA = 0x00;
    const uint8_t LIMITE_BASSE = 100; // Limite pour lumière basse et extrémité pour ambiante
    const uint8_t LIMITE_AMBIANTE = 200; // Limite pour lumière ambiante et extrémité pour hausse

    while (true)
    {
        lectureCan = convertionHuitBits(convertisseurAnalog.lecture(PA0));

        if(lectureCan <= LIMITE_BASSE) { // Lumière basse -> Vert
            PORTB = VERT;
        } else if (lectureCan > LIMITE_BASSE && lectureCan < LIMITE_AMBIANTE) { // Lumière ambiante -> Ambre
            PORTB = VERT;
            _delay_ms(DELAI_AMBRE);
            PORTB = ROUGE;
            _delay_ms(DELAI_AMBRE);
        } else { // Lumière hausse -> Rouge
            PORTB = ROUGE;
        }
    }
    return 0;
}