/**
 * @file suivi.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier gère les suivi de lumière et de mur.
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "suivi.h"

uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}

// Suivi Lumière
void suivreLumiere(Moteur& moteur, uint8_t& lecturePhotoG, uint8_t& lecturePhotoD){
    uint8_t pourcentageD; // Pourcentage PWM droite
    uint8_t pourcentageG; // Pourcentage PWM gauche

    // La photorésistance a l'air plus sensible que la gauche, donc nous avons ajouté cette correction
    lecturePhotoD = (lecturePhotoD <= CORRECTION_PHOTO) ? 0 : lecturePhotoD - CORRECTION_PHOTO;
    
    // Créer un pourcentage PWM à partir de la valeur obtenue
    pourcentageD = (lecturePhotoG >= LIMITE_MAX) ? 100 : (lecturePhotoG - LIMITE_AMBIANTE);
    pourcentageG = (lecturePhotoD >= LIMITE_MAX) ? 100 : (lecturePhotoD - LIMITE_AMBIANTE);

    // Ces deux lignes ont été ajoutées pour une des méthodes utilisée pour la mémoire
    pourcentageD = ((uint8_t) (pourcentageD/10.0)) * 10;
    pourcentageG = ((uint8_t) (pourcentageG/10.0)) * 10;

    // Traitement des valeurs reçues
    if(lecturePhotoD <= LIMITE_AMBIANTE && lecturePhotoG > LIMITE_AMBIANTE + CORRECTION_PHOTO) // Rotation en sens antihoraire
    {
        pourcentageG = pourcentageD;
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 1, 0);
    } 
    else if (lecturePhotoG <= LIMITE_AMBIANTE && lecturePhotoD > LIMITE_AMBIANTE + CORRECTION_PHOTO) // Rotation en sens horaire
    {
        pourcentageD = pourcentageG;
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 1);
    }
    else if (lecturePhotoG > LIMITE_AMBIANTE && lecturePhotoD > LIMITE_AMBIANTE) // Avancer par rapport à la lumière
    {
        moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 0);
    }
    else // Arrêter tout
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