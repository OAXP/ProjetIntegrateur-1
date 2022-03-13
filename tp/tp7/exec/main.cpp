#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Moteur.h"

int main(){
    Moteur moteur;


    while (true)
    {
        moteur.reculer();
    }
    
}
