#include <avr/io.h>

class Pwm_T0 {
    public:
        Pwm_T0();

        void appliquerPourcentage(uint8_t pourcentage0, uint8_t pourcentage1);
};