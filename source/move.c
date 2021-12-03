#include <ncurses.h>
#include <stdbool.h>


/* Déplacements gérés dans ce fichier */


/* directions */
const int HAUT = 1;
const int BAS = 2;
const int GAUCHE = 3;
const int DROITE = 4;


/* renvoie true si élément en face du joueur n'est pas VIDE.
 * map : lin lignes, col colonnes*/
bool collision (struct joueur j, int map[32][128], int map_lin, int map_col)
{
	// cas où joueur sur bord de la map
	if (j.pos_col == 0 || j.pos_col == map_col - 1)
		return false;

	else if (j.pos_lin == 0 || j.pos_lin == map_lin - 1)
		return false;


	// teste la case en face
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