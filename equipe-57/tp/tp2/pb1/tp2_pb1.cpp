/*
Auteurs : Anas Barbouch (2143541) et Andy Tran (2146959)

Description : La DEL est éteinte au départ. Après avoir appuyé trois fois sur D2, la DEL devient ROUGE. 
Après une nouvelle pression sur D2, la DEL revient à son état initial et s'éteint. D3 agit comme un reset 
et ramène le système à son état initial (DEL éteinte).

Broches en mode sortie utilisées : A0, A1
Broches en mode entrée utilisées : D2, D3

Tableau d'état problème 1, tp2
+--------------+----+----+--------------+--------+
| Etat present | D3 | D2 | Etat suivant | Sortie |
+==============+====+====+==============+========+
| INIT         | 0  | 0  | INIT         | Eteint |
+--------------+----+----+--------------+--------+
| INIT         | 0  | 1  | ETAT1        | Eteint |
+--------------+----+----+--------------+--------+
| INIT         | 1  | -- | INIT         | Eteint |
+--------------+----+----+--------------+--------+
| ETAT1        | 0  | 0  | ETAT1        | Eteint |
+--------------+----+----+--------------+--------+
| ETAT1        | 0  | 1  | ETAT2        | Eteint |
+--------------+----+----+--------------+--------+
| ETAT1        | 1  | -- | INIT         | Eteint |
+--------------+----+----+--------------+--------+
| ETAT2        | 0  | 0  | ETAT2        | Eteint |
+--------------+----+----+--------------+--------+
| ETAT2        | 0  | 1  | ROUGE        | Eteint |
+--------------+----+----+--------------+--------+
| ETAT2        | 1  | -- | INIT         | Eteint |
+--------------+----+----+--------------+--------+
| ROUGE        | 0  | 0  | ROUGE        | ROUGE  |
+--------------+----+----+--------------+--------+
| ROUGE        | 0  | 1  | INIT         | ROUGE  |
+--------------+----+----+--------------+--------+
| ROUGE        | 1  | -- | INIT         | ROUGE  |
+--------------+----+----+--------------+--------+
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

const uint8_t ETEINT = 0x00; // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02; // 0b00000010 Courant sur A1 pour avoir du ROUGE

enum class Etat
{ // Classe Enum pour identifier les états
    INIT,
    ETAT1,
    ETAT2,
    ROUGE
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
    DDRA = 0xFF; // PORT A est en mode sortie
    DDRD = 0x00; // PORT D est en mode entrée
    PORTA = ETEINT; // PORT A ETEINT par défaut

    while (true)
    { // Machine à états
        if (estAppuye(_BV(PD3)))
        {
            etatCourant = Etat::INIT;
            PORTA = ETEINT;
            // Passer à la prochaine itération pour empêcher une intervention de D2
            continue;
        }
        switch (etatCourant)
        {
            case Etat::INIT:
                PORTA = ETEINT;
                if (estAppuye(_BV(PD2)))
                {
                    etatCourant = Etat::ETAT1;
                }
                else
                {
                    etatCourant = Etat::INIT;
                }
                break;
            case Etat::ETAT1:
                PORTA = ETEINT;
                if (estAppuye(_BV(PD2)))
                {
                    etatCourant = Etat::ETAT2;
                }
                else
                {
                    etatCourant = Etat::ETAT1;
                }
                break;
            case Etat::ETAT2:
                PORTA = ETEINT;
                if (estAppuye(_BV(PD2)))
                {
                    etatCourant = Etat::ROUGE;
                }
                else
                {
                    etatCourant = Etat::ETAT2;
                }
                break;
            case Etat::ROUGE:
                PORTA = ROUGE;
                if (estAppuye(_BV(PD2)))
                {
                    etatCourant = Etat::INIT;
                }
                else
                {
                    etatCourant = Etat::ROUGE;
                }
                break;
        }
    }

    return 0;
}