/*

Auteurs : Ryan Kezouh, Ilias Bakhbukh

Description du programme : Ce programme implémente une machine a état de Moore.

Identification matérielle : Le microcontrolleur utilisé est Atmega324a
                            Les broches D2 et D3 sont les seules entrées du circuit.
                            La broche A1 est la sortie.

+--------------+----+----+--------------+--------+
| État présent | D2 | D3 | État suivant | Sorite |
+--------------+----+----+--------------+--------+
| INIT         | 0  | x  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| INIT         | 1  | x  | E1           | fermé  |
+--------------+----+----+--------------+--------+
| E1           | 1  | 0  | E1           | fermé  |
+--------------+----+----+--------------+--------+
| E1           | x  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E1           | 0  | 0  | E2           | fermé  |
+--------------+----+----+--------------+--------+
| E2           | 1  | 0  | E3           | fermé  |
+--------------+----+----+--------------+--------+
| E2           | x  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E2           | 0  | 0  | E2           | fermé  |
+--------------+----+----+--------------+--------+
| E3           | 1  | 0  | E3           | fermé  |
+--------------+----+----+--------------+--------+
| E3           | x  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E3           | 0  | 0  | E4           | fermé  |
+--------------+----+----+--------------+--------+
| E4           | 1  | 0  | E5           | fermé  |
+--------------+----+----+--------------+--------+
| E4           | x  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E4           | 0  | 0  | E4           | fermé  |
+--------------+----+----+--------------+--------+
| E5           | 1  | 0  | E5           | allumé |
+--------------+----+----+--------------+--------+
| E5           | x  | 1  | INIT         | allumé |
+--------------+----+----+--------------+--------+
| E5           | 0  | 0  | E6           | allumé |
+--------------+----+----+--------------+--------+
| E6           | 1  | 0  | E7           | allumé |
+--------------+----+----+--------------+--------+
| E6           | x  | 1  | INIT         | allumé |
+--------------+----+----+--------------+--------+
| E6           | 0  | 0  | E6           | allumé |
+--------------+----+----+--------------+--------+
| E7           | 1  | x  | E7           | fermé  |
+--------------+----+----+--------------+--------+
| E7           | 0  | x  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
*/

#define F_CPU 1000000UL  // 1 MHzs

#include <avr/io.h>
#include <util/delay.h>


enum State{INIT, E1, E2, E3};

uint16_t x = 0;
uint16_t max = 5000;

int main(){

    State state = INIT;

    DDRA = 0xFF;
    DDRD = 0x00;

    while(true){
        switch(state){
            case INIT :

                PORTA = 0x02;

                if(!(PIND & 0x04)){
                    state = E1;
                }

                break;
            case E1 :

                PORTA = 0x02;

                if(PIND & 0x04){
                    state = E2;
                }

                break;
            case E2 :

                PORTA = 0;
                for(uint16_t t=0;++t<x/40;){
                    _delay_us(2);
                }

                PORTA = 0x02;
                _delay_us(4000);
                
                x += 3;

                if(x >= max){
                    state = E3;
                }

                break;
            case E3 :

                PORTA = 0;

                x = 0;

                if(PIND & 0x04){
                    state = INIT;
                }
                break;
            default : state = INIT;
        }
    }

}