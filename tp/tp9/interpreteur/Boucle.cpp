// Classe à ignorer pour le moment

#include "Boucle.h"

Boucle::Boucle() : compte(0), addresse(nullptr) {}

Boucle::Boucle(uint8_t compte, uint8_t *addresse) : compte(compte), addresse(addresse) {
    faire(compte, addresse);
}

void Boucle::faire(uint8_t compte, uint8_t *addresse) {
    // Faire ce qu'il y a après le début de l'addresse ou faire la boucle complète
}