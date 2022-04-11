#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "Moteur.h"
#include "debug.h"

const uint8_t ETEINT = 0x00;   // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;    // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;     // 0b00000001 Courant sur A0 pour avoir du VERT
const uint8_t DELAI_AMBRE = 3; // Délai en ms pour avoir la couleur ambre


uint8_t convertionHuitBits(uint16_t num){
    // Garde seulement les 8 bits pertinents des 16 bits fournis par le CAN
    return (num >> 2);
}

int main()
{
    char tamponDebug[100];
    int debugTaille;
    can convertisseurAnalog;
    uint8_t lecturePhotoD; // Photorésistance droite
    uint8_t lecturePhotoG; // Photorésistance gauche
    uint8_t pourcentageD; // Pourcentage PWM droite
    uint8_t pourcentageG; // Pourcentage PWM gauche
    DDRA &= ~(1 << PA3 | 1 << PA5);
    const uint8_t LIMITE_AMBIANTE = 120; // Limite pour lumière ambiante
    const uint8_t LIMITE_MAX = LIMITE_AMBIANTE + 100; // Limite pour la lumière max
    Moteur moteur;

    while (true)
    {
        lecturePhotoD = convertionHuitBits(convertisseurAnalog.lecture(PA3));
        lecturePhotoG = convertionHuitBits(convertisseurAnalog.lecture(PA5));
        pourcentageD = (lecturePhotoG >= LIMITE_MAX) ? 100 : (lecturePhotoG - LIMITE_AMBIANTE);
        pourcentageG = (lecturePhotoD >= LIMITE_MAX) ? 100 : (lecturePhotoD - LIMITE_AMBIANTE);
        
        debugTaille = sprintf(tamponDebug, "Gauche : %d ; Droite : %d\n", lecturePhotoG, lecturePhotoD); // TODO à changer pour respecter le format
        DEBUG_PRINT(tamponDebug, debugTaille);

        if(lecturePhotoD <= 120 && lecturePhotoG > 120) // Rotation en sens antihoraire
        {
            pourcentageG = pourcentageD;
            moteur.directionPersonnalisee(pourcentageG, pourcentageD, 1, 0);
        } 
        else if (lecturePhotoG <= 120 && lecturePhotoD > 120) // Rotation en sens horaire
        {
            pourcentageD = pourcentageG;
            moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 1);
        }
        else if (lecturePhotoG > 120 && lecturePhotoD > 120)
        {
            moteur.directionPersonnalisee(pourcentageG, pourcentageD, 0, 0);
        }
        else
        {
            moteur.arreter();
        }

        _delay_ms(200);
    }
    return 0;
}