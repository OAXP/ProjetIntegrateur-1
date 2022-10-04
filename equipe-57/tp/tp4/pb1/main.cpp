/**
 * Description du programme:
 * 
 * 1. L'interruption INT0 est utilisé pour alterner la couleur de la DEL bicolore. (Intéragir avec le bouton poussoir)
 * 2. Le timer 1 est utilisé pour pour alterner la couleur de la DEL bicolor. (Pas besoin d'intéraction)
 * 3. Le timer 0 est utilisé pour controller les moteurs à l'aide d'un Pont en H. (Pas besoin d'intéraction)
 * 
 * Documentation: 
 * http://ww1.microchip.com/downloads/en/devicedoc/atmel-8272-8-bit-avr-microcontroller-atmega164a_pa-324a_pa-644a_pa-1284_p_datasheet.pdf
 * 
 *  Page de la documentation Atmel consulté:
 *  - Interruption avec INT0: p.67 à 68
 *  - Timer 1: p.128 à 134
 *  - Timer 0: p.101 à 106
 *  
 **/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile bool toggleButton = false;

ISR (INT0_vect) {
    _delay_ms (30);
    if(PIND & _BV(PD2)) {
        toggleButton = !toggleButton;
    }
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation (void) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'être interrompu alors que
// le microcontrôleur n'est pas prêt...
cli ();

// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables
DDRA = 0xFF;
DDRD = 0x00;

// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ;

// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC11);

// sei permet de recevoir à nouveau des interruptions.
sei ();
}

int main()
{
    initialisation();
    
    while (true)
    {
        if(toggleButton) {
            PORTA = 0x01;
        } else {
            PORTA = 0x02;
        }
    }

    return 0;
} 