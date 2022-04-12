/**
 * @file Moteur.cpp
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Moteur pour contrôler les roues du robot, elle peut
 * contrôler la vitesse et la direction du robot.
 * @date 2022-03-12
 * 
 */

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
    pourcentageG = pourcentage0;
    pourcentageD = pourcentage1;
}

uint8_t Moteur::getPourcentageG() {
    return pourcentageG;
}

uint8_t Moteur::getPourcentageD() {
    return pourcentageD;
}

bool Moteur::getDirectionG() {
    return directionG;
}

bool Moteur::getDirectionD() {
    return directionD;
}

void Moteur::avancer(uint8_t pourcentage) {
    directionPersonnalisee(pourcentage, pourcentage, 0, 0);
}

void Moteur::reculer(uint8_t pourcentage) {
    directionPersonnalisee(pourcentage, pourcentage, 1, 1);
}

void Moteur::tournerDroite() {
   directionPersonnalisee(100, 0, 0, 0);
}

void Moteur::tournerGauche() {
    directionPersonnalisee(0, 100, 0, 0);
}

void Moteur::arreter() {
    directionPersonnalisee(0, 0, 0, 0);
}