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
volatile bool toggleTimer = false;

ISR (INT0_vect) {
    _delay_ms (30);
    if(PIND & _BV(PD2)) {
        toggleButton = true;
    }
    EIFR |= (1 << INTF0) ;
}

ISR(TIMER1_COMPA_vect) {
    toggleTimer = true;
}

void initialisation (void) {
    cli ();

    
    DDRD = 0x00;
    DDRA = 0xFF;
    _delay_ms(10000);
    PORTA = 0x01;
    _delay_ms(100);
    PORTA = 0x00;

    EIMSK |= (1 << INT0) ;

    EICRA |= (1 << ISC00) | (1 << ISC01);

    sei();
}

void partirMinuterie (uint16_t duree) {
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    cli();
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // mode CTC du timer 1 avec horloge divisée par 1024
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A); // Pour créer une interruption avec le flag OCIE1A

    sei();
}

int main()
{
    initialisation();
    partirMinuterie(7815); // Lancer minuterie de 1 sec

    do {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while (!toggleButton && !toggleTimer);

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse

    if(toggleButton) {
        PORTA = 0x02;
    } else {
        PORTA = 0x01;
    }

    while(true) {}

    return 0;
} 