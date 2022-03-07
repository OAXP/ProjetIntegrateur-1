#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main(){
    DDRA = 0xFF;
    while(true){
        setGreen();
        _delay_ms(1000);
        setRed();
        _delay_ms(1000);
    }
}
