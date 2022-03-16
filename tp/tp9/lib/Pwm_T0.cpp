/**
 * @file Pwm_T0.h
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Pwm_T0 pour activer le Fast PWM sur le Timer 0.
 * @date 2022-03-12
 * 
 */

#include "Pwm_T0.h"

Pwm_T0::Pwm_T0() {
    DDRB |= (1 << PB3) | (1 << PB4);
    initialiserTimer0();
}

void Pwm_T0::initialiserTimer0() {
    cli();

    TCNT0 = 0;
    TCCR0A =
        (1 << WGM00) | 
        (1 << WGM01) | // Mis en commentaire pour utiliser PWM Phase Correct 8-bit
        (1 << COM0A1)| 
        (1 << COM0B1);
    TCCR0B = (1 << CS01); 
    sei();
}

void Pwm_T0::appliquerPourcentage(uint8_t pourcentage0, uint8_t pourcentage1) {

    double valeur0 = (double) pourcentage0 / 100.0;
    double valeur1 = (double) pourcentage1 / 100.0;

    OCR0A = 255 * valeur0;
    OCR0B = 255 * valeur1;
}