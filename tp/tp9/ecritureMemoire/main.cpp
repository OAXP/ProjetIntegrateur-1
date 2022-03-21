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
    uint16_t addresse = 0x0000; //les 2 premiers octets (0x00)
    uint16_t taille = (rs232.receptionUART() << 8) | (rs232.receptionUART() << 0);
    uint8_t code;

    while (addresse < taille - 2)
    {
        code = rs232.receptionUART();
        rs232.transmissionUART(code);
        memoire.ecriture(addresse, code);
        _delay_ms(5);
        addresse++;
    }

    _delay_ms(5000);

    addresse = 0x0000;
    while (addresse < taille - 2)
    {
        memoire.lecture(addresse, &code);
        rs232.transmissionUART(code);
        addresse++;
    }
}