#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "Moteur.h"
#include "ecrire.h"

uint8_t convertionHuitBits(uint16_t num);

// Suivi lumière
void suivre_lumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD, Memoire24CXXX& memoire, uint16_t& addresse);

const uint8_t LIMITE_AMBIANTE = 125; // Limite pour lumière ambiante
const uint8_t LIMITE_MAX = LIMITE_AMBIANTE + 100; // Limite pour la lumière max

// Suivi Mur
bool suivre_mur(Moteur& moteur, uint8_t& distance, Memoire24CXXX& memoire, uint16_t& addresse);

const uint8_t DISTANCE_CIBLE = 69; // Valeur correspondante a une distance de 20cm par rapport a une surface