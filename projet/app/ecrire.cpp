#include <ecrire.h>

int combine(uint16_t pourcentageMoteurG, uint8_t pourcentageMoteurD) { //combiner pourcentageD et pourcentageG en un uint16_t
	pourcentageMoteurG = pourcentageMoteurG << 8; //ex: 0xF3 -> 0xF300
	return pourcentageMoteurG + pourcentageMoteurD;
}

void ecrire_memoire(Memoire24CXXX& memoire, uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD, volatile uint16_t & addresse){
    uint16_t pwm = combine(pourcentageMoteurG, pourcentageMoteurD);
    memoire.ecriture(addresse, pwm); // addresse: (8bit)pourcentageMoteurG | (8bit)pourcentageMoteurD
    addresse++;
}