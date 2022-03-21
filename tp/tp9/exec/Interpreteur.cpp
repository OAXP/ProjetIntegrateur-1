#include "Interpreteur.h"

Interpreteur::Interpreteur(){
    estContinu = false;
    boucleActif = false;
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
            double tempsAtt = operande * 25;
            _delay_ms(tempsAtt);
            break;
        case DAL:
            del.appliquerVertDel();
            break;
        case DET:
            del.appliquerEteintDel();
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
            uint8_t vitesse = (uint8_t) (operande/255 * 100);
            moteur.avancer(vitesse);
            break;
        case MRE:
            uint8_t vitesse = (uint8_t) (operande/255 * 100);
            moteur.reculer(vitesse);
            break;
        case TRD:
            moteur.tournerDroite();
            _delay_ms(500); // Temps pris pour tourner de 90 degrés sur du bois
            moteur.arreter();
            break;
        case TRG:
            moteur.tournerGauche(); // TODO 90 degrés
            _delay_ms(500); // Temps pris pour tourner de 90 degrés sur du bois
            moteur.arreter();
            break;
        case DBC:
            if (boucleActif==false){     //boucleActif false si on atteint pas DBC par FBC
                boucleActif = true;
                sauvegarde = addresse;   //addresse a retourner quand on atteint FBC
                compte = operande;      //compte = nombre de fois a repeter boucle
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