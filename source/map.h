#ifndef MAP_H
#define MAP_H

// dimensions de la map
const int MAP_LIN;
const int MAP_COL;


/* éléments que peut contenir la map */
const int VIDE;
const int JOUEUR_HAUT;
const int JOUEUR_BAS;
const int JOUEUR_GAUCHE;
const int JOUEUR_DROITE;
const int MUR;
const int ENNEMI;
const int BLOC;


/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL]);

/* remplit la map de VIDE */
void initialise_map(int map[MAP_LIN][MAP_COL]);


void affiche_bordure();


#endif