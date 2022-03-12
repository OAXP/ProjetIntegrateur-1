#include <avr/io.h>
#include "rs232.h"

#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG
# define DEBUG_PRINT(donnee) Rs232.transmissionUART(donnee);
#else
# define DEBUG_PRINT(donnee) do {} while (0) // code mort
#endif