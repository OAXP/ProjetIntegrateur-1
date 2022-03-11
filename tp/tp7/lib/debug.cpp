#include "debug.h"
#include "rs232.h"

#define DEBUG // à mettre en commentaire ou non au besoin

#ifdef DEBUG

# define DEBUG_PRINT(donnee) {
rs232 printer;

void printer::DEBUG_PRINT(donnee){
    printer.transmissionUART(donnee)
}
}

#else

# define DEBUG_PRINT(donnee) do {} while (0) // code mort

#endif