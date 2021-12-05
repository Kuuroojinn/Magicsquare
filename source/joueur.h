#ifndef JOUEUR_H
#define JOUEUR_H



/* directions */
extern const int HAUT;
extern const int BAS;
extern const int GAUCHE;
extern const int DROITE;

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