#include <avr/io.h>

class Rs232{
    public:
        Rs232();
        void transmissionUART(uint8_t donnee);
        
    private:
        uint8_t donnee;
};