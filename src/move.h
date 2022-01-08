#ifndef MOVE_H
#define MOVE_H


#include <stdbool.h>
#include "map.h"
#include "ennemi.h"


/* renvoie true si la case au-dessus du joueur n'est pas vide */
bool elt_en_haut(struct joueur j, int map[MAP_LIN][MAP_COL]);

/* renvoie true si la case au-dessous du joueur n'est pas vide */
bool elt_en_bas(struct joueur j, int map[MAP_LIN][MAP_COL]);

/* renvoie true si la case à gauche du joueur n'est pas vide */
bool elt_a_gauche(struct joueur j, int map[MAP_LIN][MAP_COL]);

/* renvoie true si la case à droite du joueur n'est pas vide */
bool elt_a_droite(struct joueur j, int map[MAP_LIN][MAP_COL]);

//renvoie true si la case au dessus est un ennemi
bool ennemi_en_haut(struct joueur j, int map[MAP_LIN][MAP_COL]);

//renvoie true si la case en dessous est un ennemi
bool ennemi_en_bas(struct joueur j, int map[MAP_LIN][MAP_COL]);

//renvoie true si la case à gauche est un ennemi
bool ennemi_a_gauche(struct joueur j, int map[MAP_LIN][MAP_COL]);

//renvoie true si la case a droite est un ennemi
bool ennemi_a_droite(struct joueur j, int map[MAP_LIN][MAP_COL]);



void deplacement(struct joueur* j, int map[MAP_LIN][MAP_COL], int inputchar,struct ennemi* e_ptr);


#endif
