#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Moteur.h"
#include "Bouton.h"
#include "Del.h"
#include "debug.h"

int main(){
    Moteur moteur; // La classe Moteur teste aussi la classe Pwm_T0 et Pwm_T0 est compatible avec Timer0
    Bouton bouton(&PIND, PD2);
    Del del(&PORTA, PA0, PA1);

    char tamponDebug[100];
    int debugTaille;
    
    moteur.avancer();
    debugTaille = sprintf(tamponDebug, "Robot Avance\n");
    DEBUG_PRINT(tamponDebug, debugTaille);
    _delay_ms(1000);
    moteur.reculer();
    debugTaille = sprintf(tamponDebug, "Robot Recule\n");
    DEBUG_PRINT(tamponDebug, debugTaille);
    _delay_ms(1000);
    moteur.tournerDroite();
    debugTaille = sprintf(tamponDebug, "Robot tourne droite\n");
    DEBUG_PRINT(tamponDebug, debugTaille);
    _delay_ms(1000);
    moteur.tournerGauche();
    debugTaille = sprintf(tamponDebug, "Robot tourne gauche\n");
    DEBUG_PRINT(tamponDebug, debugTaille);
    _delay_ms(1000);
    moteur.arreter();
    while (true)
    {
        switch (bouton.getEtat())
        {
        case Bouton::Etat::APPUYE:
            {
                debugTaille = sprintf(tamponDebug, "Bouton Appuyé et DEL allume en rouge\n");
                DEBUG_PRINT(tamponDebug, debugTaille);
            }
            del.appliquerRougeDel();
            break;
        case Bouton::Etat::MAINTENU:
            {
                debugTaille = sprintf(tamponDebug, "Bouton maintenu et DEL allume en vert\n");
                DEBUG_PRINT(tamponDebug, debugTaille);
            }
            del.appliquerVertDel();
            break;
        case Bouton::Etat::RELACHE:
            {
                debugTaille = sprintf(tamponDebug, "Bouton Relaché et DEL allume en rouge\n");
                DEBUG_PRINT(tamponDebug, debugTaille);
            }
            del.appliquerRougeDel();
            break;
        
        default:
            del.appliquerRougeDel();
            break;
        }
    }
    
}
