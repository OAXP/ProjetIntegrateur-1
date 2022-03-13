/**
 * @file debug.h
 * @author Andy Tran (andy.tran@polymtl.ca)
 * @brief Classe Bouton pour gérer les appuis de bouton.
 * @date 2022-03-12
 * 
 */
#include <avr/io.h>
#include "rs232.h"

#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG
# define DEBUG_PRINT(donnee) printer(donnee);
#else
# define DEBUG_PRINT(donnee) do {} while (0) // code mort
#endif

void printer(uint8_t donnee);
