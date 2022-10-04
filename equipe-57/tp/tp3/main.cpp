/**
 * Concept important Frequence - Periode - Pulse width modulation (PWM) - Duty Cycle
 * - Fréquence: Le nombre de cycle effectuer en 1 seconde (unité Hertz (Hz))
 * - Periode: Le temps que prends 1 cycle à être exécuter (unité seconde (s)). C'est le "b" dans l'explication du TP3
 * - PWM: Signal digital qui varie entre 1 (HIGH) et 0 (LOW) sur une période.
 * - Duty Cycle (Power Cycle): Ce terme désigne le temps que le signal est active (donc à 1) pendant un PWM. 
 * Vous pouvez le considérer comme le "a" dans l'explication du TP3
 * 
 * Formule important à comprendre/apprendre:
 * - Frequence = 1 / periode
 * - Periode = 1 / frequence
 * 
 * 
 * Documentation:
 * - Delay loop2: https://www.nongnu.org/avr-libc/user-manual/group__util__delay__basic.html
 * 
 * */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void show() {
    double b = 0.001;
    double a = b;
    const double REDUCE_A = 0.001/900.0;

    while(a >= 0){
        PORTA = 0x01;
        _delay_loop_2(a * F_CPU);
        PORTA = 0x00;
        _delay_loop_2((b-a) * F_CPU);
        a -= REDUCE_A;
    }
}

int main()
{
    DDRA = 0xFF;
    
    while (true)
    {
        show();
    }

    return 0;
} 