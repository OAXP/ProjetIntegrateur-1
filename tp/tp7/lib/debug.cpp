#include "debug.h"
#include "rs232.h"

rs232 printer;

void printer::print(donnee){
    printer.transmissionUART(donnee)
}