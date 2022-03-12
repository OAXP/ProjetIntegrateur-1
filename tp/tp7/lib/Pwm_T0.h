/**
 * @file Pwm_T0.cpp
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Pwm_T0 pour activer le Fast PWM sur le Timer 0.
 * @date 2022-03-12
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

class Pwm_T0 {
    public:
        Pwm_T0();

        void appliquerPourcentage(uint8_t pourcentage0, uint8_t pourcentage1);
    
    private:
        void initialiserTimer0();
};