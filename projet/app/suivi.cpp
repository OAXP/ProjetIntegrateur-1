#include "suivi.h"

uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}

// Suivi Lumière
void suivreLumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD){
    uint8_t pourcentageD; // Pourcentage PWM droite
    uint8_t pourcentageG; // Pourcentage PWM gauche

    lecturePhotoD = (lecturePhotoD <= 20) ? 0 : lecturePhotoD - 20;
    
    pourcentageD = (lecturePhotoG >= LIMITE_MAX) ? 100 : (lecturePhotoG - LIMITE_AMBIANTE);
    pourcentageG = (lecturePhotoD >= LIMITE_MAX) ? 100 : (lecturePhotoD - LIMITE_AMBIANTE);

    pourcentageD = ((uint8_t) (pourcentageD/10.0)) * 10;
    pourcentageG = ((uint8_t) (pourcentageG/10.0)) * 10;

    if(lecturePhotoD <= LIMITE_AMBIANTE && lecturePhotoG > LIMITE_AMBIANTE + 20) // Rotation en sens antihoraire
    {
        pourcentageG = pourcentageD;
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 1, 0);
    } 
    else if (lecturePhotoG <= LIMITE_AMBIANTE && lecturePhotoD > LIMITE_AMBIANTE + 20) // Rotation en sens horaire
    {
        pourcentageD = pourcentageG;
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 1);
    }
    else if (lecturePhotoG > LIMITE_AMBIANTE && lecturePhotoD > LIMITE_AMBIANTE)
    {
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 0);
    }
    else
    {
        moteur.arreter();
    }

}

// Suivi Mur
bool suivreMur(Moteur& moteur, uint8_t& distance){

    bool murDetecte = true;

    // Si le robot est a la distance cible du mur
    if (distance == DISTANCE_CIBLE){
        moteur.directionPersonnalisee(60, 50, 0, 0);
    }
    // Si le robot est a une distance plus grande que la distance cible par rapport au mur
    else if(distance < DISTANCE_CIBLE){
        if(distance >= 65){
            moteur.directionPersonnalisee(60, 30, 0, 0); // Se rapproche tres peu
        }
        else if(distance >= 59){
            moteur.directionPersonnalisee(60, 20, 0, 0); // Se rapproche peu
        }
        else if(distance >= 56){
            moteur.directionPersonnalisee(60, 10, 0, 0); // Se rapproche moyennement
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
            moteur.directionPersonnalisee(50, 50, 0, 0); // S'eloigne tres peu
        }
        else if(distance <= 82){
            moteur.directionPersonnalisee(30, 50, 0, 0); // S'eloigne peu
        }
        else if(distance <= 93){
            moteur.directionPersonnalisee(20, 50, 0, 0); // S'eloigne moyennement
        }
        else{ //106
            moteur.directionPersonnalisee(10, 50, 0, 0); // S'eloigne beaucoup
        }
    }

    return murDetecte;
}