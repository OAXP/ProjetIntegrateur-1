#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Del.h"
#include "Moteur.h"

int main(){

    Moteur m;

    m.avancer();

    while(true){
       
    }
}
