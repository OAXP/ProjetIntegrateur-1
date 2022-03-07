/*

Auteurs : Ryan Kezouh, Ilias Bakhbukh

Description du programme : Ce programme implémente une machine a état de Moore.

Identification matérielle : Le microcontrolleur utilisé est l'Atmega324a.
                            Les broches D2 et D3 sont les seules entrées du circuit.
                            Les broches A0 et A1 sont les sorties.

+--------------+----+----+--------------+--------+
| État présent | D2 | D3 | État Suivant | Sortie |
+--------------+----+----+--------------+--------+
| INIT         | 1  | 0  | INIT         | rouge  |
+--------------+----+----+--------------+--------+
| INIT         | 0  | 1  | INIT         | rouge  |
+--------------+----+----+--------------+--------+
| INIT         | 0  | 0  | E1           | rouge  |
+--------------+----+----+--------------+--------+
| E1           | 0  | 0  | E1           | rouge  |
+--------------+----+----+--------------+--------+
| E1           | 1  | 0  | E2           | rouge  |
+--------------+----+----+--------------+--------+
| E1           | 0  | 1  | E2           | rouge  |
+--------------+----+----+--------------+--------+
| E2           | 1  | 0  | E2           | vert   |
+--------------+----+----+--------------+--------+
| E2           | 0  | 1  | E2           | vert   |
+--------------+----+----+--------------+--------+
| E2           | 0  | 0  | E3           | vert   |
+--------------+----+----+--------------+--------+
| E3           | 1  | 0  | INIT         | vert   |
+--------------+----+----+--------------+--------+
| E3           | 0  | 0  | E3           | vert   |
+--------------+----+----+--------------+--------+
| E3           | 0  | 1  | E4           | vert   |
+--------------+----+----+--------------+--------+
| E4           | 0  | 1  | E4           | éteint |
+--------------+----+----+--------------+--------+
| E4           | x  | 0  | E5           | éteint |
+--------------+----+----+--------------+--------+
| E5           | 0  | 1  | INIT         | éteint |
+--------------+----+----+--------------+--------+
| E5           | 1  | 0  | E2           | éteint |
+--------------+----+----+--------------+--------+
| E5           | 0  | 0  | E5           | éteint |
+--------------+----+----+--------------+--------+
*/

#include <avr/io.h>

enum State{INIT, E1, E2, E3, E4, E5};

int main(){

    State etatPresent = INIT;

    int delRouge = 0x02;
    int delVerte = 0x01;
    int delEteinte = 0x00;

    DDRA = 0xFF;
    DDRD = 0x00;

    while(true){

        switch(etatPresent){

            case INIT :

                PORTA = delRouge;

                if(!(PIND & 0x04 || PIND & 0x08)){
                    etatPresent = E1;
                }
                break;

            case E1 :

                PORTA = delRouge;

                if(PIND & 0x04 || PIND & 0x08){
                    etatPresent = E2;
                }
                break;

            case E2 :

                PORTA = delVerte;

                if(!(PIND & 0x04 || PIND & 0x08)){
                    etatPresent = E3;
                }
                break;

            case E3 :

                PORTA = delVerte;

                if(PIND & 0x04){
                    etatPresent = INIT;
                }
                if(PIND & 0x08){
                    etatPresent = E4;
                }
                break;

            case E4 :

                PORTA = delEteinte;

                if(!(PIND & 0x08)){
                    etatPresent = E5;
                }
                break;

            case E5 :

                PORTA = delEteinte;

                if(PIND & 0x04){
                    etatPresent = E2;
                }
                if(PIND & 0x08){
                    etatPresent = INIT;
                }
                break;

            default : 

                etatPresent = INIT;
        }
    }
}