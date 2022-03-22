/**
 * @file main.cpp
 * @author Anas Barbouch, Andy Tran, Ryan Kezouh, Ilias Bakhbukh
 * @brief Ce fichier écrit dans la mémoire le bytecode reçu avec serieViaUSB et transmet de la mémoire en UART les données reçues.
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "rs232.h"
#include "memoire_24.h"

int main() {
    Rs232 rs232;
    Memoire24CXXX memoire;
    uint16_t addresse = 0x0000;
    uint16_t taille = (rs232.receptionUART() << 8) | (rs232.receptionUART() << 0); // La taille est dans les 2 premiers octets
    uint8_t code;

    // Écriture en mémoire
    while (addresse < taille - 2)
    {
        code = rs232.receptionUART();
        rs232.transmissionUART(code); // Pour débogage
        memoire.ecriture(addresse, code);
        _delay_ms(5);
        addresse++;
    }

    _delay_ms(5000);

    addresse = 0x0000;
    // Affichage de la mémoire écrite (pour débogage)
    while (addresse < taille - 2)
    {
        memoire.lecture(addresse, &code);
        rs232.transmissionUART(code);
        addresse++;
    }
}