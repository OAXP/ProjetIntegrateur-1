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


    {
        moteur.avancer();
        {
            char tab[] = "Robot Avance\n";
            uint8_t taille = sizeof(tab)/sizeof(tab[0]);
            DEBUG_PRINT(tab, taille);
        }
        _delay_ms(1000);
        moteur.reculer();
        {
            char tab[] = "Robot Recule\n";
            uint8_t taille = sizeof(tab)/sizeof(tab[0]);
            DEBUG_PRINT(tab, taille);
        }
        _delay_ms(1000);
        moteur.tournerDroite();
        {
            char tab[] = "Robot tourne droite\n";
            uint8_t taille = sizeof(tab)/sizeof(tab[0]);
            DEBUG_PRINT(tab, taille);
        }
        _delay_ms(1000);
        moteur.tournerGauche();
        {
            char tab[] = "Robot tourne gauche\n";
            uint8_t taille = sizeof(tab)/sizeof(tab[0]);
            DEBUG_PRINT(tab, taille);
        }
        _delay_ms(1000);
        moteur.arreter();
    }
    while (true)
    {
        switch (bouton.getEtat())
        {
        case Bouton::Etat::APPUYE:
            {
                char tab[] = "Bouton Appuyé et DEL allume en rouge\n";
                uint8_t taille = sizeof(tab)/sizeof(tab[0]);
                DEBUG_PRINT(tab, taille);
            }
            del.appliquerRougeDel();
            break;
        case Bouton::Etat::MAINTENU:
            {
                char tab[] = "Bouton maintenu et DEL allume en vert\n";
                uint8_t taille = sizeof(tab)/sizeof(tab[0]);
                DEBUG_PRINT(tab, taille);
            }
            del.appliquerVertDel();
            break;
        case Bouton::Etat::RELACHE:
            {
                char tab[] = "Bouton Relaché et DEL allume en rouge\n";
                uint8_t taille = sizeof(tab)/sizeof(tab[0]);
                DEBUG_PRINT(tab, taille);
            }
            del.appliquerRougeDel();
            break;
        
        default:
            del.appliquerRougeDel();
            break;
        }
    }
    
}
