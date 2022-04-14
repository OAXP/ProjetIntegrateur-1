#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "Moteur.h"


bool suivre_mur(Moteur& moteur, uint8_t& distance);

const uint8_t DISTANCE_CIBLE = 69; // Valeur correspondante a une distance de 20cm par rapport a une surface