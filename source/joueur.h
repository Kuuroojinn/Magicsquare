#ifndef JOUEUR_H
#define JOUEUR_H


/* directions */
const int HAUT;
const int BAS;
const int GAUCHE;
const int DROITE;

struct joueur
{
	// sur la map
	int pos_lin;
	int pos_col;
	int dir;  // direction du joueur

	// pour les combats, à chager plus tard
	//int pv = 1000;
};

#endif