/**
 * @file Interpreteur.h
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief La classe Interpreteur lit les instructions fournies puis éxecute le code correspondant.
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "instructions_robot.h"
#include "Del.h"
#include "Midi.h"
#include "Moteur.h"
#include "memoire_24.h"
// #include "Boucle.h" En phase de test

class Interpreteur {
    public:
    Interpreteur();
    void faire(uint8_t code, uint16_t &addresse); // Cette méthode interprète une instruction à une addresse

    private:
    bool estContinu;
    Del del;
    Midi sonerie;
    Moteur moteur;
    Memoire24CXXX memoire;
    // Boucle boucle; En phase de test
    uint16_t sauvegarde;
    uint8_t compte;
    bool boucleActif;
    uint8_t compteur;
};