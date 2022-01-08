#ifndef MAP_H
#define MAP_H

#include "joueur.h"

// dimensions de la map :
const int MAP_LIN;
const int MAP_COL;

/* éléments que peut contenir la map.
 * NB : #define employé pour pouvoir utiliser switch dans affichage.c */
#define VIDE 0
#define MUR 1
// différentes directions du joueur :
#define JOUEUR_HAUT 2
#define JOUEUR_BAS 3
#define JOUEUR_GAUCHE 4
#define JOUEUR_DROITE 5
#define ENNEMI 6


/* remplit la map de VIDE */
void initialise_map(int map[MAP_LIN][MAP_COL]);

/* ajoute dans map l'élément correspondant à la direction du joueur */
void pivote_joueur_vers_map(struct joueur j, int map[MAP_LIN][MAP_COL]);

/* vérifie que le joueur est bien dans la map (assertion) */
void assert_joueur_dans_map(struct joueur j, int map[MAP_LIN][MAP_COL]);


#endif