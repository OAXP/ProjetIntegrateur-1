/*

Auteurs : Ryan Kezouh, Ilias Bakhbukh

Description du programme : Ce programme implémente une machine a état de Moore.

Identification matérielle : Le microcontrolleur utilisé est l'Atmega324a.
                            Les broches D2 et D3 sont les seules entrées du circuit.
                            La broche A1 est la sortie.

+--------------+----+----+--------------+--------+
| État présent | D2 | D3 | État Suivant | Sortie |
+--------------+----+----+--------------+--------+
| INIT         | 0  | x  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| INIT         | 1  | 0  | E1           | fermé  |
+--------------+----+----+--------------+--------+
| E1           | 0  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E1           | 1  | 0  | E1           | fermé  |
+--------------+----+----+--------------+--------+
| E1           | 0  | 0  | E2           | fermé  |
+--------------+----+----+--------------+--------+
| E2           | 0  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E2           | 0  | 0  | E2           | fermé  |
+--------------+----+----+--------------+--------+
| E2           | 1  | 0  | E3           | fermé  |
+--------------+----+----+--------------+--------+
| E3           | 0  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E3           | 1  | 0  | E3           | fermé  |
+--------------+----+----+--------------+--------+
| E3           | 0  | 0  | E4           | fermé  |
+--------------+----+----+--------------+--------+
| E4           | 0  | 1  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E4           | 0  | 0  | E4           | fermé  |
+--------------+----+----+--------------+--------+
| E4           | 1  | 0  | E5           | fermé  |
+--------------+----+----+--------------+--------+
| E5           | 0  | 1  | INIT         | allumé |
+--------------+----+----+--------------+--------+
| E5           | 1  | 0  | E5           | allumé |
+--------------+----+----+--------------+--------+
| E5           | 0  | 0  | E6           | allumé |
+--------------+----+----+--------------+--------+
| E6           | 0  | 1  | INIT         | allumé |
+--------------+----+----+--------------+--------+
| E6           | 0  | 0  | E6           | allumé |
+--------------+----+----+--------------+--------+
| E6           | 1  | 0  | E7           | allumé |
+--------------+----+----+--------------+--------+
| E7           | 0  | x  | INIT         | fermé  |
+--------------+----+----+--------------+--------+
| E7           | 1  | 0  | E7           | fermé  |
+--------------+----+----+--------------+--------+
*/

#include <avr/io.h>

enum State{INIT, E1, E2, E3, E4, E5, E6, E7};

int main(){

    State etatPresent = INIT;

    int delEteint = 0x00;
    int delAllume = 0x02;

    DDRA = 0xFF;
    DDRD = 0x00;

    while(true){

        switch(etatPresent){

            case INIT :

                PORTA = delEteint;

                if(PIND & 0x04){
                    etatPresent = E1;
                }
                break;

            case E1 :

                PORTA = delEteint;

                if(!(PIND & 0x04)){
                    etatPresent = E2;
                }

                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E2 :

                PORTA = delEteint;

                if(PIND & 0x04){
                    etatPresent = E3;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E3 :

                PORTA = delEteint;

                if(!(PIND & 0x04)){
                    etatPresent = E4;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E4 :

                PORTA = delEteint;

                if(PIND & 0x04){
                    etatPresent = E5;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E5 :

                PORTA = delAllume;

                if(!(PIND & 0x04)){
                    etatPresent = E6;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E6 :

                PORTA = delAllume;

                if(PIND & 0x04){
                    etatPresent = E7;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            case E7 :

                PORTA = delEteint;

                if(!(PIND & 0x04)){
                    etatPresent = INIT;
                }

                break;

            default : 

                etatPresent = INIT;
        }
    }
}