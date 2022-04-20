/**
 * @file rs232.cpp
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe rs232 pour gerer la communication serie.
 * @date 2022-03-12
 * 
 */
#include "rs232.h"

Rs232::Rs232(){
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0 ;
    UCSR0A |= (1<< TXC0) | (1<< UDRE0 ) | ( 1 << MPCM0);
    UCSR0B = (1 << RXCIE0) | ( 1 << TXCIE0) | ( 1 << UDRIE0) | ( 1 << RXEN0) | ( 1<< TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void Rs232::transmissionUART(uint8_t donnee){
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    _delay_ms(5);
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

uint8_t Rs232::receptionUART(void){
    /* Wait for data receive */
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}