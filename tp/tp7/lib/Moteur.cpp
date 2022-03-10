#include "Moteur.h"

Moteur::Moteur() {
    DDRB |= (1 << PB2) | (1 << PB5);
    _pwm = Pwm_T0();
}

void Moteur::directionPersonnalisee(uint8_t pourcentage0, uint8_t pourcentage1, uint8_t direction0, uint8_t direction1) {
    PORTB |= (direction0 << PB2) | (direction1 << PB5);
    if(direction0 == 0) {
        PORTB &= (direction0 << PB2);
    } else {
        PORTB |= (direction0 << PB2);
    }
    if(direction1 == 0) {
        PORTB &= (direction1 << PB5);
    } else {
        PORTB |= (direction1 << PB5);
    }
    _pwm.appliquerPourcentage(pourcentage0, pourcentage1);
}

void Moteur::avancer() {
    directionPersonnalisee(100, 100, 0, 0);
}

void Moteur::reculer() {
    directionPersonnalisee(100, 100, 1, 1);
}

void Moteur::tournerDroite() {
   directionPersonnalisee(100, 0, 0, 0);
}

void Moteur::tournerGauche() {
    directionPersonnalisee(0, 100, 0, 0);
}

void Moteur::arreter() {
    _pwm.appliquerPourcentage(0, 0);
}