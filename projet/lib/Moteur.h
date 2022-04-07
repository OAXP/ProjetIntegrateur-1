/**
 * @file Moteur.h
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Moteur pour contrôler les roues du robot, elle peut
 * contrôler la vitesse et la direction du robot.
 * @date 2022-03-12
 * 
 */

#include "avr/io.h"
#include "Pwm_T0.h"

class Moteur {
    public:
        Moteur();

        void avancer(uint8_t pourcentage);

        void reculer(uint8_t pourcentage);

        void tournerDroite();

        void tournerGauche();

        void arreter();

        void directionPersonnalisee(uint8_t pourcentage0, uint8_t pourcentage1, uint8_t direction0, uint8_t direction1);
    
    private:
        Pwm_T0 _pwm;
};