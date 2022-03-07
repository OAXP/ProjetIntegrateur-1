/*
Auteurs : Anas Barbouch (2143541) et Andy Tran (2146959)

Description : Attendre que l'utilisateur appuie sur le bouton poussoir.
Une fois le bouton pressé, un compteur s'incrémente toutes les 0.1s.
S'arrête lorsque le bouton est relâché ou que le compteur atteint 120.
Ensuite, la LED clignote en vert pendant 0,5s. Rien ne se passe les prochain 2s. 
Ensuite, la LED clignote rouge compteur/2 fois a un rythme de deux fois par seconde.
Ensuite, la LED devient verte pendant une seconde et le robot revient à son état initial (éteint).

Broches en mode sortie utilisées : B0, B1
Broches en mode entrée utilisées : D2

Tableau d'état problème 1, tp6
+--------------+----+--------------+--------+
| État présent | D2 | État suivant | Sortie |
+--------------+----+--------------+--------+
| INIT         | 1  | INIT         | ETEINT |
+--------------+----+--------------+--------+
| INIT         | 0  | DEROULEMENT  | -      |
+--------------+----+--------------+--------+
| DEROULEMENT  | -  | INIT         | ETEINT |
+--------------+----+--------------+--------+
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t ETEINT = 0x00;   // 0b00000000 Aucun courant pour aucune lumière
const uint8_t ROUGE = 0x02;    // 0b00000010 Courant sur A1 pour avoir du Rouge
const uint8_t VERT = 0x01;     // 0b00000001 Courant sur A0 pour avoir du VERT
volatile uint8_t compteur = 0; // compteur general
volatile uint8_t compteurClignottements = 0;
volatile bool timerFini = false;
volatile bool poussoirAppuye = false;
volatile bool estExpirer = false;        //true apres que compteur passe 120
volatile bool btnPese = false;
const uint8_t DELAI_CLIGNOTTANT = 100;
const uint8_t DELAI_CLIGNOTTANT_DEUX = 100;

enum class Etat
{ // Classe Enum pour identifier les états
    INIT,
    DEROULEMENT
};
Etat etatCourant = Etat::INIT; // L'état actuel de la machine à états

void clignoter() //del libre clignotte pour 0.5s
{
    while (timerFini == false)
    {
        PORTB = VERT;
        _delay_ms(DELAI_CLIGNOTTANT);
        PORTB = ETEINT;
        _delay_ms(DELAI_CLIGNOTTANT);
    }
    timerFini = false;
}

void partirMinuterie(uint16_t duree)
{
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    cli();
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // mode CTC du timer 1 avec horloge divisée par 1024
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A); // Pour créer une interruption avec le flag OCIE1A
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    timerFini = true;
    cli();
    TCCR1B &= ~(1 << CS10 | 1 << CS12); // clear et reset timer
}

void initialisation(void)
{ //initialiser external interrupt
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);
    sei();
}

ISR(INT0_vect)
{
    _delay_ms(10); //debounce
    while (true)
    {
        if (estExpirer == true) //sortir de la boucle si compteur passe 120
        {
            break;
        }
        while (!(PIND & 0x04)) //while bouton poussoir est pressed
        {
            poussoirAppuye = true;
            compteur++;
            if (compteur >= 120)
            {
                compteur = 120;
                estExpirer = true;
                break;
            }
            _delay_ms(100); //delay 100ms pour compteur++ 10 fois/s
        }
        if ((PIND & 0x04) && (poussoirAppuye == true)) //sortir de la boucle apres relachement de bouton
        {
            break;
        }
    }
    cli();
    EIMSK &= 0; //fermer input du bouton
    btnPese = true;
    poussoirAppuye = false;
    estExpirer = false;
    EIFR |= (1 << INTF0);
}

void clignoter2xSec() //del libre clignotte selon le compteur
{
    while (compteurClignottements <= compteur)
    {
        PORTB = ROUGE;
        _delay_ms(DELAI_CLIGNOTTANT_DEUX);
        PORTB = ETEINT;
        _delay_ms(DELAI_CLIGNOTTANT_DEUX);
        compteurClignottements++;
    }
    compteurClignottements = 0;
    compteur = 0;
    PORTB = ETEINT;
}

int main()
{
    DDRB = 0xFF;
    DDRD = 0x00;
    PORTB = ETEINT;

    while (true)
    {
        switch (etatCourant)
        {
        case Etat::INIT:
            initialisation();
            while (btnPese == false)
            {
                //attend pour interrupt
            }
            btnPese = false; //remettre a false pour prochaine boucle
            etatCourant = Etat::DEROULEMENT;
            break;
        case Etat::DEROULEMENT:
            partirMinuterie(3906);
            clignoter();
            _delay_ms(2000);
            clignoter2xSec();
            PORTB = VERT;
            _delay_ms(1000);
            PORTB = ETEINT;
            etatCourant = Etat::INIT;
            break;
        }
    }
    return 0;
}
