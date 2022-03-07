#include "led.h"
#include <avr/io.h>

void setGreen(){
    PORTA = 0x01;
}

void setRed(){
    PORTA = 0x02;
}