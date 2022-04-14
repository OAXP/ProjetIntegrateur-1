#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "memoire_24.h"

void ecrire_memoire(Memoire24CXXX& memoire, uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD, volatile uint16_t& addresse);
void indiquer_fin_memoire(Memoire24CXXX& memoire, volatile uint16_t& addresse);
// int combine(uint16_t pourcentageMoteurG, uint8_t pourcentageMoteurD);