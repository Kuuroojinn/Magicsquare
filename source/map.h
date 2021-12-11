#ifndef MAP_H
#define MAP_H

// dimensions de la map
const int MAP_LIN;
const int MAP_COL;

const int JOUEUR_HAUT;
const int JOUEUR_BAS;

/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL]);

/* remplit une map de VIDE */
void initialise_map(int map[MAP_LIN][MAP_COL]);

void affiche_bordure();


#endif