/**
 * @file rs232.h
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe rs232 pour gerer la communication serie.
 * @date 2022-03-12
 * 
 */
#include <avr/io.h>

class Rs232{
    public:
        Rs232();
        void transmissionUART(uint8_t donnee);
        
    private:
        uint8_t donnee;
};