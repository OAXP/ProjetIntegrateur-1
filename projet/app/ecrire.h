#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "memoire_24.h"

void ecrireMemoire(Memoire24CXXX& memoire, uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD, volatile uint16_t& addresse);
void indiquerFinMemoire(Memoire24CXXX& memoire, volatile uint16_t& addresse);
uint8_t combine(uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD);
void dechiffrerDonnee(uint8_t donnee, volatile uint8_t& pourcentageMoteurG, volatile uint8_t& pourcentageMoteurD);