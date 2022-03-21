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
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
}

void Rs232::transmissionUART(uint8_t donnee){
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

uint8_t Rs232::receiveUART(){
    /* Wait for data receive */
    while(!(UCSR0A) & (1<<RXC0));
    ret UDR0;
}