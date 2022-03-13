/**
 * @file debug.cpp
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe Bouton pour gérer les appuis de bouton.
 * @date 2022-03-12
 * 
 */
#include "debug.h"

Rs232 debugger;
void printer(uint8_t donnee){
    debugger.transmissionUART(donnee);
}
