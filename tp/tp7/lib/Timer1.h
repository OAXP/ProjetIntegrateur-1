
/**
 * @file Timer1.h
 * @author Ilias Bakhbukh (ilias.bakhbukh@polymtl.ca)
 * @brief Classe Timer1 permet de contrôler le timer 1,
 * elle donne accès aux modes Fast PWM et CTC
 * @date 2022-03-13
 * 
 */


#include <avr/io.h>
#include <avr/interrupt.h>

class Timer1 {

public :

    Timer1(uint8_t modeDeFonctionnement, uint16_t duree);
    void initialiser(uint8_t modeDeFonctionnement, uint16_t duree);
    void arreter();

};