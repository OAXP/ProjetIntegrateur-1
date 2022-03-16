
/**
 * @file Timer0.h
 * @author Ilias Bakhbukh (ilias.bakhbukh@polymtl.ca)
 * @brief Classe Timer0 permet de contrôler le timer 0,
 * elle donne accès aux modes Fast PWM et CTC
 * @date 2022-03-13
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer0 {

public :

    Timer0(uint8_t modeDeFonctionnement, uint16_t duree);
    void initialiser(uint8_t modeDeFonctionnement, uint16_t duree);
    void arreter();

};