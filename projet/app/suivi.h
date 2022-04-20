/**
 * @file suivi.h
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier gère les suivi de lumière et de mur.
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "Moteur.h"
#include "ecrire.h"

uint8_t convertionHuitBits(uint16_t num);

// Suivi lumière
void suivreLumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD);

const uint8_t LIMITE_AMBIANTE = 120; // Limite pour lumière ambiante
const uint8_t LIMITE_MAX = LIMITE_AMBIANTE + 100; // Limite pour la lumière max
const uint8_t CORRECTION_PHOTO = 20; // Correction pour les photorésistance

// Suivi Mur
bool suivreMur(Moteur& moteur, uint8_t& distance);

const uint8_t DISTANCE_CIBLE = 69; // Valeur correspondante a une distance de 20cm par rapport a une surface