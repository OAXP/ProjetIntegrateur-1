/**
 * @file rs232.h
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe rs232 pour gerer la communication serie.
 * @date 2022-03-12
 * 
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

class Rs232{
    public:
        Rs232();
        void transmissionUART(uint8_t donnee);
        uint8_t receptionUART();
        
    private:
        uint8_t donnee;
};