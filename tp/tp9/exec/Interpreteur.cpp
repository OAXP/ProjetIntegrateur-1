#include "Interpreteur.h"

bool boucleActif = false;
uint16_t sauvegarde;
uint8_t compte;
uint8_t compteur;
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
            if (boucleActif==false){     //boucleActif false si on atteint pas DBC par FBC
                boucleActif = true;
                sauvegarde = addresse;   //addresse a retourner quand on atteint FBC
                compte = &operande;      //compte = nombre de fois a repeter boucle
            }
            break;
        case FBC:
            if (compteur == compte)
            {
                boucleActif = false; //exit boucle lorsque nb de repetition atteint
            }

            if (boucleActif==true)
            {
                compteur++;          //augmenter compteur si nb de repetition pas atteint
                addresse = sauvegarde;  //return to DBC
            } else if (boucleActif == false){
                sauvegarde = 0;      // reset
                compte = 0;
            }
            break;
        case FIN:
            estContinu = false;
            break;
        
        default:
            break;
    }
    
}