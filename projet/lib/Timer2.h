
/**
 * @file Timer2.h
 * @author Ilias Bakhbukh (ilias.bakhbukh@polymtl.ca)
 * @brief Classe Timer2 permet de contrôler le timer 2,
 * elle donne accès aux modes Fast PWM et CTC
 * @date 2022-03-13
 * 
 */


#include <avr/io.h>
#include <avr/interrupt.h>

class Timer2 {

public :

    Timer2();
    void initialiser(uint8_t modeDeFonctionnement, uint16_t duree);
    void arreter();

};