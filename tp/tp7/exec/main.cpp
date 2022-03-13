#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Moteur.h"
#include "Bouton.h"
#include "Del.h"
#include "debug.h"

int main(){
    Moteur moteur;
    Bouton bouton(&PIND, PD2);
    Del del(&PORTA, PA0, PA1);


    moteur.avancer();
    _delay_ms(1000);
    moteur.reculer();
    _delay_ms(1000);
    moteur.tournerDroite();
    _delay_ms(1000);
    moteur.tournerGauche();
    _delay_ms(1000);
    moteur.arreter();
    while (true)
    {
        if(bouton.getEtat() == Bouton::Etat::MAINTENU) {
            del.appliquerVertDel();
        } else {
            del.appliquerRougeDel();
        }
    }
    
}
