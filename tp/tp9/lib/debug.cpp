/**
 * @file debug.cpp
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe Debug pour afficher la donnee en parametre.
 * @date 2022-03-12
 * 
 */
#include "debug.h"

Rs232 debugger;
void printer(char* donnee, uint8_t taille){
    for (uint8_t i = 0; i < taille; i++)
    {
        debugger.transmissionUART(donnee[i]);
    }
}
