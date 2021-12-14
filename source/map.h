#ifndef MAP_H
#define MAP_H

// dimensions de la map
const int MAP_LIN;
const int MAP_COL;


/* éléments que peut contenir la map ;
 * NB : #define employé pour pouvoir utiliser switch dans map.c */
#define VIDE 0
#define MUR 1
#define JOUEUR_HAUT 2
#define JOUEUR_BAS 3
#define JOUEUR_GAUCHE 4
#define JOUEUR_DROITE 5
//#define ENNEMI 6
//#define BLOC 7

const int COUL_MUR;


/* affecte les paires de couleur à leur indice */
void setup_couleur();


/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL]);

/* remplit la map de VIDE */
void initialise_map(int map[MAP_LIN][MAP_COL]);


void affiche_bordure();


#endif