#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "map.h"  // contient, et inclut donc aussi joueur.h
#include "ennemi.h"

const int COUL_MUR;

/* dimensions de l'écran */
int SCR_LIN, SCR_COL;

/* coordonnées du coin supérieur gauche de la zone de texte : */
int ZONE_TXT_LIN, ZONE_TXT_COL;

/* dimensions de la zone de texte */
const int TAILLE_ZONE_TXT_LIN;
const int TAILLE_ZONE_TXT_COL;


/* affecte leurs tailles aux constantes dépendant de la taille de l'écran */
void setup_taille_ecran(int* scr_lin, int* scr_col, int* zone_txt_lin, int* zone_txt_col);

/* affecte les paires de couleur à leur indice */
void setup_couleur();

/* affiche le caractère correspondant à val
 * aux coordonnées lin, col */
void affiche_char_val(int val, int lin, int col);

/* affiche la map au centre de l'écran, moins un décalage pour la zone de texte */
void affiche_map(int map[MAP_LIN][MAP_COL]);

/* affiche une bordure autour de la map et une autour de la zone de texte */
void affiche_bordures();

/* affiche une string dans la zone de texte, aux coordonnées indiquées. */
void affiche_texte(int ligne, int colonne, char* string);

/* affiche les PV du joueur et ceux de l'ennemi sur la ligne 0 de la
 * zone de texte. à utiliser en combat */
void affiche_pv_combat(struct joueur j, struct ennemi e);

/* efface la ligne indiquée dans la zone de texte */
void efface_ligne_texte(int ligne);

/* efface toute la zone de texte */
void efface_zone_texte();

#endif