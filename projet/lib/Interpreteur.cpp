/**
 * @file Interpreteur.cpp
 * @author Anas Barbouch et Andy Tran
 * @brief La classe Interpreteur lit les instructions fournies puis éxecute le code correspondant.
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Interpreteur.h"

Interpreteur::Interpreteur(){
    estContinu = false;
    boucleActif = false;
}

void Interpreteur::faire(uint8_t code, uint16_t &addresse) {
    uint8_t operande;
    addresse++; // Aller à l'addresse de l'opérande
    memoire.lecture(addresse, &operande);
    if(code != DBT && !estContinu){
        return; // Si instruction FIN lue ou pas de DBT
    }
    switch (code)
    {
        case DBT:
            estContinu = true;
            break;
        case ATT:
            for (uint8_t i = 0; i < operande; i++)
            {
                _delay_ms(25); // Délai de 25 ms operande fois
            }
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
            {
                uint8_t vitesse = (uint8_t) (operande/255.0 * 100);
                moteur.avancer(vitesse);
            }
            break;
        case MRE:
            {
                uint8_t vitesse = (uint8_t) (operande/255.0 * 100);
                moteur.reculer(vitesse);
            }
            break;
        case TRD:
            moteur.tournerDroite();
            _delay_ms(1000); // Temps pris pour tourner de 90 degrés sur du bois
            moteur.arreter();
            break;
        case TRG:
            moteur.tournerGauche();
            _delay_ms(1000); // Temps pris pour tourner de 90 degrés sur du bois
            moteur.arreter();
            break;
        case DBC:
            if (boucleActif==false){     // boucleActif false si on atteint pas DBC par FBC
                boucleActif = true;
                sauvegarde = addresse;   // addresse a retourner quand on atteint FBC
                compte = operande;      // compte = nombre de fois a repeter boucle
            }
            break;
        case FBC:
            if (compteur == compte)
            {
                boucleActif = false; // exit boucle lorsque nb de repetition atteint
            }

            if (boucleActif==true)
            {
                compteur++;          // augmenter compteur si nb de repetition pas atteint
                addresse = sauvegarde;  // return to DBC
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
    
    addresse++;
}