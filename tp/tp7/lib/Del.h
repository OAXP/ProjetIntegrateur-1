/**
 * @file Del.h
 * @author Anas Barbouch (anas.barbouch@polymtl.ca)
 * @brief Classe Del pour controler la couleur de la lumière
 * émise par une DEL bicolore.
 * @date 2022-03-12
 * 
 */

#include <avr/io.h>

class Del {
    public:
        Del(volatile uint8_t *port, uint8_t pinDel0, uint8_t pinDel1);

        void appliquerRougeDel();
        void appliquerVertDel();
        void appliquerEteintDel();

    private:
        volatile uint8_t *_port;
        uint8_t _pinDel0;
        uint8_t _pinDel1;
};