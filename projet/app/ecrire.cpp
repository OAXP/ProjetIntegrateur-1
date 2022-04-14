#include "ecrire.h"

/*
int combine(uint16_t pourcentageMoteurG, uint8_t pourcentageMoteurD) { //combiner pourcentageD et pourcentageG en un uint16_t
	pourcentageMoteurG = pourcentageMoteurG << 8; //ex: 0xF3 -> 0xF300
	return pourcentageMoteurG + pourcentageMoteurD;
}
*/

void ecrire_memoire(Memoire24CXXX& memoire, uint8_t pourcentageMoteurG, uint8_t pourcentageMoteurD, volatile uint16_t & addresse){
    // uint16_t pwm = combine(pourcentageMoteurG, pourcentageMoteurD);
    memoire.ecriture(addresse, pourcentageMoteurG); // addresse: (8bit)pourcentageMoteurG
    addresse++;
    memoire.ecriture(addresse, pourcentageMoteurD); // addresse: (8bit)pourcentageMoteurD
    addresse++;
}

void indiquer_fin_memoire(Memoire24CXXX& memoire, volatile uint16_t& addresse) {
    // On a décidé que les 2 valeurs indiquant la fin serait 0 puis 69;
    memoire.ecriture(addresse, 0);
    addresse++;
    memoire.ecriture(addresse, 69);
    addresse++;
}