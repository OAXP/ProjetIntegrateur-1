#include "Interpreteur.h"

Interpreteur::Interpreteur(){
    estContinu = false;
}

void Interpreteur::faire(uint8_t code, uint8_t addresse) {
    switch (code)
    {
    case 0x01:
        estContinu = true;
        break;
    case 0x02:
        break;
    case 0x33:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0x01:
        estContinu = true;
        break;
    case 0xff:
        estContinu = false;
        break;
    
    default:
        break;
    }
}