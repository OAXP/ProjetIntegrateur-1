#include "suivi_lumiere.h"


uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}

void suivre_lumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD){
    uint8_t pourcentageD; // Pourcentage PWM droite
    uint8_t pourcentageG; // Pourcentage PWM gauche

    
    pourcentageD = (lecturePhotoG >= LIMITE_MAX) ? 100 : (lecturePhotoG - LIMITE_AMBIANTE);
    pourcentageG = (lecturePhotoD >= LIMITE_MAX) ? 100 : (lecturePhotoD - LIMITE_AMBIANTE);

    if(lecturePhotoD <= LIMITE_AMBIANTE && lecturePhotoG > LIMITE_AMBIANTE) // Rotation en sens antihoraire
    {
        pourcentageG = pourcentageD;
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 1, 0);
    } 
    else if (lecturePhotoG <= LIMITE_AMBIANTE && lecturePhotoD > LIMITE_AMBIANTE) // Rotation en sens horaire
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