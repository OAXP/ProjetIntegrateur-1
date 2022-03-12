#include "debug.h"
#include "rs232.h"

rs232 debugger;
void printer(donnee){
    debugger.transmissionUART(donnee);
}
