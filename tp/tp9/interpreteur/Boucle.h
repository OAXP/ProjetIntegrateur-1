// Classe à ignorer pour le moment

#include <avr/io.h>

class Boucle {
    public:
    Boucle();
    Boucle(uint8_t compte, uint8_t *addresse);
    void faire(uint8_t compte, uint8_t *addresse);
    
    private:
    uint8_t compte;
    uint8_t *addresse;
};