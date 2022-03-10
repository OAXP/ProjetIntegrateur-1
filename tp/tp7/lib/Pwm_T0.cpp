#include "Pwm_T0.h"

Pwm_T0::Pwm_T0() {
    DDRB &= ~((1 << PB3) | (1 << PB4));
}

void Pwm_T0::appliquerPourcentage(uint8_t pourcentage0, uint8_t pourcentage1) {

    double valeur0 = pourcentage0 / 100.0;
    double valeur1 = pourcentage1 / 100.0;

    OCR0A = 255 * valeur0;
    OCR0B = 255 * valeur1;
}