/**
 * @file Bouton.h
 * @author Ryan Kezouh (anas.barbouch@polymtl.ca)
 * @brief Classe Bouton pour gérer les appuis de bouton.
 * @date 2022-03-12
 * 
 */

#include <avr/io.h>

class Bouton {
    public:
        const uint8_t antirebond = 200;

        Bouton(uint8_t pin, uint8_t boutonID);

        bool appuiBouton();

    private:
        uint8_t _pin;
        uint8_t _boutonID;
};