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