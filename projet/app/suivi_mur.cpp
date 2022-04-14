// #include "suivi_mur.h"


// uint8_t convertionEnDistance(uint8_t valeur){
//     // Formule de conversion en distance prise sur 
//     return 2998.8 * pow(valeur, -1.173);
// }

// void suivre_mur(Moteur& moteur, uint8_t& lectureDistance){

//     //Si le robot est a la distance cible du mur
//     if (lectureDistance == DISTANCE_CIBLE){
//         moteur.directionPersonnalisee(80, 80, 0, 0);
//     }
//     //Si le robot est a une distance plus petite que la distance cible par rapport au mur
//     else if(lectureDistance < DISTANCE_CIBLE){
//         if(lectureDistance >= 18){
//             moteur.directionPersonnalisee(60, 80, 0, 0);
//         }
//         else if(lectureDistance >= 16){
//             moteur.directionPersonnalisee(40, 80, 0, 0);
//         }
//         else if(lectureDistance >= 14){
//             moteur.directionPersonnalisee(20, 80, 0, 0);
//         }
//         else if(lectureDistance >= 12){
//             moteur.directionPersonnalisee(0, 80, 0, 0);
//         }
//         else{
//             moteur.arreter();
//         }
//     }
//     //Si le robot est a une distance plus grande que la distance cible par rapport au mur
//     else{
//         if(lectureDistance <= 22){
//             moteur.directionPersonnalisee(80, 60, 0, 0);
//         }
//         else if(lectureDistance <= 24){
//             moteur.directionPersonnalisee(80, 40, 0, 0);
//         }
//         else if(lectureDistance <= 26){
//             moteur.directionPersonnalisee(80, 20, 0, 0);
//         }
//         else if(lectureDistance <= 28){
//             moteur.directionPersonnalisee(80, 0, 0, 0);
//         }
//         else{
//             moteur.arreter();
//         }
//     }
//     _delay_ms(100);
// }