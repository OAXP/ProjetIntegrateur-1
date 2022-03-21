#include "Interpreteur.h"

Interpreteur::Interpreteur(){
    estContinu = false;
}

void Interpreteur::faire(uint8_t code, uint8_t &addresse) {
    uint8_t operande;
    addresse += 0x08;
    memoire.lecture(addresse, &operande);
    switch (code)
    {
        case DBT:
            estContinu = true;
            break;
        case ATT:
            break;
        case DAL:
            del.appliquerVert(); // Choisir quel DEL allumer
            break;
        case DET:
            del.appliquerEteintDel(); // Choisir quel DEL éteindre
            break;
        case SGO:
            sonerie.jouerNote(operande);
            break;
        case SAR:
            sonerie.arreterNote();
            break;
        case MAR: case MAR1:
            moteur.arreter();
            break;
        case MAV:
            moteur.avancer(); // TODO remplacer par personnalisé
            break;
        case MRE:
            moteur.reculer(); // TODO remplacer par personnalisé
            break;
        case TRD:
            moteur.tournerDroite(); // TODO 90 degrés
            break;
        case TRG:
            moteur.tournerGauche(); // TODO 90 degrés
            break;
        case DBC:
            // Todo commencer la boucle
            boucle.faire(100, &addresse);
            break;
        case FBC:
            // Todo finir la boucle
            break;
        case FIN:
            estContinu = false;
            break;
        
        default:
            break;
    }
}