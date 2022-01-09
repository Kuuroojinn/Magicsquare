#ifndef MOVE_H
#define MOVE_H


#include <stdbool.h>
#include "map.h"
#include "ennemi.h"


/*renvoie true si l'element recherché est dans la case au-dessus du joueur */
bool test_elt_en_haut(struct joueur j, int map[MAP_LIN][MAP_COL], int element);

/* renvoie true si l'element recherché est dans la case au-dessous du joueur */
bool test_elt_en_bas(struct joueur j, int map[MAP_LIN][MAP_COL], int element);

/* renvoie true si l'élément recherché est dans la case à gauche du joueur */
bool test_elt_a_gauche(struct joueur j, int map[MAP_LIN][MAP_COL], int element);

/* renvoie true si l'élément recherché est dans la case à droite du joueur */
bool test_elt_a_droite(struct joueur j, int map[MAP_LIN][MAP_COL], int element);

/* Modifie la position du joueur en fonction de l'entrée au clavier (on suppose que
 * le déplacement est valide) ; le cas échéant, lance un combat ou la fin du jeu */
void deplacement(struct joueur* j_ptr, int map[MAP_LIN][MAP_COL], int inputchar, struct ennemi* e_ptr);


#endif
