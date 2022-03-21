#include <avr/io.h>

class Boucle {
    public:
    Boucle(uint8_t compte, uint8_t addresse);
    
    private:
    uint8_t compte;
    uint8_t addresse;
};