/*
Auteurs : Anas Barbouch (2143541) et Andy Tran (2146959)

Description : La DEL est rouge quand la carte mère démarre. Si on appuie sur D2 ou D3, la DEL devient verte. 
Si D2 est pressé, le système retourne à son état initial (DEL rouge). 
Si l'on appuie sur D3, la DEL est désactivée. 
Lorsque la DEL est éteinte, la pression de D2 la ramène à son état initial où elle était verte.
Si on appuie sur D3 à la place, on revient à l'état initial (DEL rouge).

Broches en mode sortie utilisées : A0, A1
Broches en mode entrée utilisées : D2, D3

Tableau d'état problème 2, tp2
+--------------+----+----+--------------+---------+
| État présent | D2 | D3 | État suivant | Sortie  |
+--------------+----+----+--------------+---------+
| INIT         | 0  | 0  | INIT         | Rouge   |
+--------------+----+----+--------------+---------+
| INIT         | 1  | 0  | VERT         | Rouge   |
+--------------+----+----+--------------+---------+
| INIT         | 0  | 1  | VERT         | Rouge   |
+--------------+----+----+--------------+---------+
| VERT         | 0  | 0  | VERT         | VERT    |
+--------------+----+----+--------------+---------+
| VERT         | 1  | 0  | INIT         | VERT    |
+--------------+----+----+--------------+---------+
| VERT         | 0  | 1  | ETEINT       | VERT    |
+--------------+----+----+--------------+---------+
| ETEINT       | 0  | 0  | ETEINT       | ETEINT  |
+--------------+----+----+--------------+---------+
| ETEINT       | 1  | 0  | VERT         | ETEINT  |
+--------------+----+----+--------------+---------+
| ETEINT       | 0  | 1  | INIT         | ETEINT  |
+--------------+----+----+--------------+---------+
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

const uint8_t ETEINT = 0x00; // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;  // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;   // 0b00000001 Courant sur A0 pour avoir du VERT

enum class Etat
{ // Classe Enum pour identifier les états
    INIT,
    VERT,
    ETEINT
};
Etat etatCourant = Etat::INIT; // L'état actuel de la machine à états

bool estAppuye(uint8_t masque)
{
    if (PIND & masque) // Savoir si Bouton est appuyé
    {
        _delay_ms(10); // Délai pour debounce
        if (PIND & masque)
        {
            while (PIND & masque)
            {
                // Attente du relâchement de bouton
            }
            return true;
        }
    }
    return false;
}

int main()
{
    DDRA = 0xFF;   // PORT A est en mode sortie
    DDRD = 0x00;   // PORT D est en mode entrée
    PORTA = ROUGE; // PORT A ROUGE par défaut

    while (true)
    { // Machine à états
        switch (etatCourant)
        {
        case Etat::INIT:
            PORTA = ROUGE;
            if (estAppuye(_BV(PD2)))
            {
                etatCourant = Etat::VERT;
            }
            else if (estAppuye(_BV(PD3)))
            {
                etatCourant = Etat::VERT;
            }
            break;

        case Etat::VERT:
            PORTA = VERT;
            if (estAppuye(_BV(PD2)))
            {
                etatCourant = Etat::INIT;
            }
            else if (estAppuye(_BV(PD3)))
            {
                etatCourant = Etat::ETEINT;
            }
            break;

        case Etat::ETEINT:
            PORTA = ETEINT;
            if (estAppuye(_BV(PD2)))
            {
                etatCourant = Etat::VERT;
            }
            else if (estAppuye(_BV(PD3)))
            {
                etatCourant = Etat::INIT;
            }
            break;
        }
    }

    return 0;
}