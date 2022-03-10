#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Moteur.h"

int main(){
    Moteur moteur;


    while (true)
    {
        moteur.avancer();
        _delay_ms(1000);
        moteur.reculer();
        _delay_ms(1000);
        moteur.tournerDroite();
        _delay_ms(1000);
        moteur.tournerGauche();
        _delay_ms(1000);
    }
    
}
