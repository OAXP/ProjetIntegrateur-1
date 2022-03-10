#include <avr/io.h>
#include <avr/interrupt.h>

class Pwm_T0 {
    public:
        Pwm_T0();

        void appliquerPourcentage(uint8_t pourcentage0, uint8_t pourcentage1);
    
    private:
        void initialiserTimer0();
};