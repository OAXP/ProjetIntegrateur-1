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
    uint16_t addresse = rs232.receptionUART(); //les 2 premiers octets (0x00)
    uint8_t binSize = rs232.receptionUART();

    for (uint16_t i = 0; i < binSize; i++)
    {
        memoire.ecriture(addresse, rs232.receptionUART());
        addresse += 0x0008;
    }
}