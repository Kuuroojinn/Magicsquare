#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "map.h"

const int COUL_MUR;

/* dimensions de la zone de texte */
const int TAILLE_ZONE_TXT_LIN;
const int TAILLE_ZONE_TXT_COL;


/* affecte les paires de couleur à leur indice */
void setup_couleur();

/* affiche la map au centre de l'écran de dimensions 
 * scr_lin lignes par scr_col colonnes */
void affiche_map(int map[MAP_LIN][MAP_COL], int scr_lin, int scr_col);

/* affiche le caractère correspondant à val
 * aux coordonnées lin, col */
void affiche_char_val(int val, int lin, int col);

/* affiche une bordure autour de la map et une autour de la zone de texte,
 * dans un écran de dimensions scr_lin lignes par scr_col colonnes */
void affiche_bordures(int scr_lin, int scr_col);

/* affiche une string dans la zone de texte, aux coordonnées indiquées. */
void affiche_texte(int ligne, int colonne, char* string);

/* efface la ligne indiquée dans la zone de texte */
void efface_ligne_texte(int ligne);

#endif