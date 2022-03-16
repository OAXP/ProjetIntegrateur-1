/**
 * @file Del.cpp
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Del pour controler la couleur de la lumière
 * émise par une DEL bicolore.
 * @date 2022-03-12
 * 
 */

#include "Del.h"

Del::Del(volatile uint8_t *port, uint8_t pinDel0, uint8_t pinDel1) : _port(port), _pinDel0(pinDel0), _pinDel1(pinDel1) {

    if(port == &PORTA) {
        DDRA |= (1 << _pinDel0) | (1 << _pinDel1);
    }
    else if(port == &PORTB) {
        DDRB |= (1 << _pinDel0) | (1 << _pinDel1);
    }
    else if(port == &PORTC) {
        DDRC |= (1 << _pinDel0) | (1 << _pinDel1);
    }
    else if(port == &PORTD) {
        DDRD |= (1 << _pinDel0) | (1 << _pinDel1);
    }

}

void Del::appliquerEteintDel(){
    *_port &= ~((1 << _pinDel0) | (1 << _pinDel1));
}

void Del::appliquerRougeDel(){
    *_port &= ~(1 << _pinDel0);
    *_port |= (1 << _pinDel1);
}

void Del::appliquerVertDel(){
    *_port &= ~(1 << _pinDel1);
    *_port |= (1 << _pinDel0);
}