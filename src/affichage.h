#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "map.h"

const int COUL_MUR;


/* affecte les paires de couleur à leur indice */
void setup_couleur();

/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL]);

/* affiche le caractère correspondant à val
 * aux coordonnées lin, col */
void affiche_char_val(int val, int lin, int col);

/* affiche une bordure autour de la map */
void affiche_bordure();

#endif