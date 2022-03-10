#include "avr/io.h"
#include "Pwm_T0.h"

class Moteur {
    public:
        Moteur();

        void avancer();

        void reculer();

        void tournerDroite();

        void tournerGauche();

        void arreter();

        void directionPersonnalisee(uint8_t pourcentage0, uint8_t pourcentage1, uint8_t direction0, uint8_t direction1);
    
    private:
        Pwm_T0 _pwm;
};