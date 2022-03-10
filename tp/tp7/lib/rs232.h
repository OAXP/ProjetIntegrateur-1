#include <avr/io.h>

class rs232{
    public:
        rs232();
        void transmissionUART(uint8_t donnee);
        
    private:
        uint8_t donnee;
};