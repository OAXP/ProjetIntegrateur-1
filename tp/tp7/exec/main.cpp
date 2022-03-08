#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Del.h"

int main(){
    Del del(&PORTA, PA0, PA1);
    while(true){
        del.appliquerVertDel();
        _delay_ms(1000);
        del.appliquerRougeDel();
        _delay_ms(1000);
    }
}
