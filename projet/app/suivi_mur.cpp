#include "suivi_mur.h"

bool suivre_mur(Moteur& moteur, uint8_t& distance){

    bool murDetecte = true;

    // Si le robot est a la distance cible du mur
    if (distance == DISTANCE_CIBLE){
        moteur.directionPersonnalisee(60, 50, 0, 0);
    }
    // Si le robot est a une distance plus grande que la distance cible par rapport au mur
    else if(distance < DISTANCE_CIBLE){
        if(distance >= 65){
            moteur.directionPersonnalisee(60, 35, 0, 0); // Se rapproche tres peu
        }
        else if(distance >= 59){
            moteur.directionPersonnalisee(60, 20, 0, 0); // Se rapproche peu
        }
        else if(distance >= 56){
            moteur.directionPersonnalisee(60, 7, 0, 0); // Se rapproche moyennement
        }
        else if(distance >= 52){
            moteur.directionPersonnalisee(60, 0, 0, 0); // Se rapproche beaucoup
        }
        else{
            moteur.arreter(); // S'arrete si trop loin
            murDetecte = false;
        }
    }
    // Si le robot est a une distance plus petite que la distance cible par rapport au mur
    else{
        if(distance <= 75){
            moteur.directionPersonnalisee(45, 50, 0, 0); // S'eloigne tres peu
        }
        else if(distance <= 82){
            moteur.directionPersonnalisee(30, 50, 0, 0); // S'eloigne peu
        }
        else if(distance <= 93){
            moteur.directionPersonnalisee(15, 50, 0, 0); // S'eloigne moyennement
        }
        else if(distance <= 106){
            moteur.directionPersonnalisee(0, 60, 0, 0); // S'eloigne beaucoup
        }
        else{
            moteur.arreter(); // S'arrete si trop proche
            murDetecte = false;
        }
    }
    _delay_ms(20);
    return murDetecte;
}