#ifndef GRILLE_H
#define GRILLE_H

/* Codes numériques pour désigner les differents éléments du terrain */

const int VIDE;
const int JOUEUR;
const int MUR;
const int ENNEMI;
const int BLOC;


/* salle représentée par un struct qui pourra évoluer */
struct salle
{
	int pos_x;  // nécessaire pour la positionner sur la map
	int pos_y;
	int longueur;
	int largeur;
}

/* Affiche la salle à l'écran */  // ou la transfère à map ?
void affiche_salle(struct salle s);


#endif