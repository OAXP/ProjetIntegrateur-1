/*

Auteurs : Ryan Kezouh, Ilias Bakhbukh

Description du programme :  Ce programme implémente un capteur de type bouton. Le programme calcule le nombre de dixieme de seconde aucours duquel le bouton est enfoncé, puis affiche ce nombre
                            divisé par 2 sous forme de clignotements.

Identification matérielle : Le microcontrolleur utilisé est Atmega324a
                            Les broches D2 et D3 sont les seules entrées du circuit.
                            La broche A1 est la sortie.
*/

#define F_CPU 8000000UL  // 1 MHzs

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "can.h"
#include "can.cpp"

const uint8_t VALEUR_MIN = 150;
const uint8_t VALEUR_MAX = 170;

const uint8_t VERT = 0x02;
const uint8_t ROUGE = 0x01;

int main(){

    DDRB = 0xFF;
    DDRD = 0x00;

    can convertisseur = can();

    uint16_t lecture;

    while(true){
        lecture = convertisseur.lecture(0) >> 2;

        if(lecture < VALEUR_MIN){
            PORTB = VERT;
        }else if(lecture > VALEUR_MAX){
            PORTB = ROUGE;
        }else{

            PORTB = ROUGE;
            _delay_ms(2);
            PORTB = VERT;
            _delay_ms(2);

        }
        
    }

}