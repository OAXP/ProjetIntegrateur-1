#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "instructions_robot.h"
#include "Del.h"
#include "Midi.h"
#include "Moteur.h"
#include "memoire_24.h"
#include "Boucle.h"

class Interpreteur {
    public:
    Interpreteur();
    void faire(uint8_t code, uint8_t &addresse);

    private:
    bool estContinu;
    Del del;
    Midi sonerie;
    Moteur moteur;
    Memoire24CXXX memoire;
    Boucle boucle;
    uint16_t sauvegarde;
    uint8_t compte;
    bool boucleActif;
    uint8_t compteur;
};