#include <avr/io.h>
#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG
# define DEBUG_PRINT(donnee)
class debug {
    public:
        void print(donnee);
    private:
        uint8_t donnee;
};
#else
# define DEBUG_PRINT(donnee) do {} while (0) // code mort
#endif