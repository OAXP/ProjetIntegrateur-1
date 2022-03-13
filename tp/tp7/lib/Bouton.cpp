/**
 * @file Bouton.cpp
 * @author Ryan Kezouh (anas.barbouch@polymtl.ca)
 * @brief Classe Bouton pour gérer les appuis de bouton.
 * @date 2022-03-12
 * 
 */

 #include <Bouton.h>
 #include <util/delay.h>

 Bouton::Bouton(uint8_t pin, uint8_t boutonID) : _pin(pin), _boutonID(boutonID) {

    if(pin == &PINA) {
        DDRA |= (0 << _boutonID);
    }
    else if(pin == &PINB) {
        DDRB |= (0 << _boutonID);
    }
    else if(pin == &PINC) {
        DDRC |= (0 << _boutonID);
    }
    else if(pin == &PIND) {
        DDRD |= (0 << _boutonID);
    }

}

 bool Bouton::appuiBouton()
{
  if (_pin & _boutonID)
  {
    _delay_ms(antirebond);

    return true;
  }

  return false;
}