#include "ecrire.h"

uint8_t combine(uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD) { //combiner pourcentageD et pourcentageG en un uint8_t
    pourcentageMoteurG = ((uint8_t) (pourcentageMoteurG / 10.0)) << 4; // On prend seulement les dizaines
	pourcentageMoteurD = (uint8_t) (pourcentageMoteurD / 10.0); // On prend seulement les dizaines
	return pourcentageMoteurG + pourcentageMoteurD;
}

void dechiffrerDonnee(uint8_t donnee, volatile uint8_t& pourcentageMoteurG, volatile uint8_t& pourcentageMoteurD) {
    pourcentageMoteurG = (donnee >> 4) * 10;
    pourcentageMoteurD = (donnee & 0x0F) * 10; // 0x0F pour ne garder que les bits à droite
}

void ecrireMemoire(Memoire24CXXX& memoire, uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD, volatile uint16_t & addresse){
    uint8_t pwm = combine(pourcentageMoteurG, pourcentageMoteurD);
    memoire.ecriture(addresse, pwm); // addresse: (8bit) pourcentageMoteurG/10 | pourcentageMoteurD/10
    _delay_ms(5);
    addresse++;
}

void indiquerFinMemoire(Memoire24CXXX& memoire, volatile uint16_t& addresse) {
    // On a décidé que la valeur indiquant la fin serait 255 (1111 1111);
    memoire.ecriture(addresse, 255);
    addresse++;
}