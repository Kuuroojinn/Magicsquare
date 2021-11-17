#ifndef GRILLE_H

#define GRILLE_H

/* Codes numériquespour désigner le vide, le joueur et le mur */

const int VIDE;
const int JOUEUR;
const int MUR;

const int ENNEMI;
const int BLOC; 

/* La salle sera représentée par le type int ...[64][64] */

/* Affiche la salle à l'écran */
void affiche_salle(int asalle[64][64]);


#endif
