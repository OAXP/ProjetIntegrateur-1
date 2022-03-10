#include "Moteur.h"

Moteur::Moteur() {
    DDRB &= ~((1 << PB2) | (1 << PB5));
    _pwm = Pwm_T0();
}

void Moteur::directionPersonnalisee(uint8_t pourcentage0, uint8_t pourcentage1, uint8_t direction0, uint8_t direction1) {
    PORTB |= (direction0 << PB2) | (direction1 << PB5);
    _pwm.appliquerPourcentage(pourcentage0, pourcentage1);
}

void Moteur::avancer() {
    _pwm.appliquerPourcentage(100, 100);
}

void Moteur::reculer() {
    directionPersonnalisee(100, 100, 1, 1);
}

void Moteur::tournerDroite() {
    _pwm.appliquerPourcentage(100, 0);
}

void Moteur::tournerGauche() {
    _pwm.appliquerPourcentage(0, 100);
}

void Moteur::arreter() {
    _pwm.appliquerPourcentage(0, 0);
}