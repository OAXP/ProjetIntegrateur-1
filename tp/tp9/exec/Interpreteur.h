#include <avr/io.h>

class Interpreteur {
    public:
    Interpreteur();
    void faire(uint8_t code, uint8_t addresse);

    private:
    bool estContinu;

};