#include <ncurses.h>
#include <stdbool.h>
#include "map.h"

/* Déplacements gérés dans ce fichier */


/* renvoie true si élément en face du joueur n'est pas VIDE.
 * map : lin lignes, col colonnes*/
bool elt_en_face (struct joueur j, int map[MAP_LIN][MAP_COL])
{
	// cas où joueur sur bord de la map
	if (j.pos_col == 0 || j.pos_col == MAP_COL - 1)
		return true;

	else if (j.pos_lin == 0 || j.pos_lin == MAP_LIN - 1)
		return true;


	// teste la case en face du joueur
	if (j.dir == HAUT && map[j.pos_lin - 1][j.pos_col] != VIDE)
		return true;

	else if (j.dir == BAS && map[j.pos_lin + 1][j.pos_col] != VIDE)
		return true;

	else if (j.dir == GAUCHE && map[j.pos_lin][j.pos_col + 1] != VIDE)
		return true;
	
	else if (j.dir == DROITE && map[j.pos_lin][j.pos_col -1] != VIDE)
		return true;


	else  // rien en face
		return false;
}


