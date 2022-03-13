#include "debug.h"

Rs232 debugger;
void printer(uint8_t donnee){
    debugger.transmissionUART(donnee);
}
