#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "Moteur.h"

uint8_t convertionHuitBits(uint16_t num);
void suivre_lumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD);

const uint8_t LIMITE_AMBIANTE = 150; // Limite pour lumière ambiante
const uint8_t LIMITE_MAX = LIMITE_AMBIANTE + 100; // Limite pour la lumière max