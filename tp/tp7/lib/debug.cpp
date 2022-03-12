#include "debug.h"
#include "rs232.h"

void DEBUG_PRINT(donnee){
    Rs232.transmissionUART(donnee)
}
