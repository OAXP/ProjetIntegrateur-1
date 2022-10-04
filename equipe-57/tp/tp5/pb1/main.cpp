#define F_CPU 8000000

#include <avr/io.h>
#include "memoire_24.h"

const uint16_t addresse = 0x0000;

void initialisation (void) {
    DDRA = 0xFF;
}

int main()
{
    initialisation();
    uint8_t tabPoly[] = {'P','O','L','Y','T','E','C','H','N','I','Q','U','E',' ','M','O','N','T','R','E','A','L', 0x00};
    uint8_t tabCmp[sizeof(tabPoly)];

    Memoire24CXXX memoire;

    memoire.ecriture(addresse, tabPoly, sizeof(tabPoly));

    memoire.lecture(addresse, tabCmp, sizeof(tabPoly));

    bool estPareil = true;

    for (uint8_t i = 0; i < sizeof(tabPoly); i++)
    {
        if(tabPoly[i] != tabCmp[i]) {
            estPareil = false;
            break;
        }
    }
    
    if(estPareil) {
        PORTA = 0x01;
    } else {
        PORTA = 0x02;
    }

    return 0;
}