/**
 * @file Bouton.h
 * @author Ryan Kezouh (ryan.kezouh@polymtl.ca)
 * @brief Classe Bouton pour gérer les appuis de bouton.
 * @date 2022-03-12
 * 
 */

#include <avr/io.h>
#include <util/delay.h>

class Bouton {
    public:
        enum class Etat {
                INIT,
                APPUYE,
                MAINTENU,
                RELACHE
            };
        const uint8_t antirebond = 200;

        Bouton(uint8_t pin, uint8_t boutonID);
        bool appuiBouton();
        Etat getEtat();

    private:
        uint8_t _pin;
        uint8_t _boutonID;
        Etat _etatPresent = ETAT::INIT;
};