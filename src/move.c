#include <stdbool.h>
#include <ncurses.h>
#include "move.h"
#include "map.h"

/////////////   Déplacements gérés dans ce fichier   //////////////


/* renvoie true si la case au-dessus du joueur n'est pas vide */
bool elt_en_haut(struct joueur j, int map[MAP_LIN][MAP_COL])
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur en haut de la map
	if (j.pos_lin == 0)
		return true;

	// case au-dessus du joueur
	else if (map[j.pos_lin - 1][j.pos_col] != VIDE)
		return true;

	else
		return false;
}


/* renvoie true si la case au-dessous du joueur n'est pas vide */
bool elt_en_bas(struct joueur j, int map[MAP_LIN][MAP_COL])
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur en bas de la map
	if (j.pos_lin == MAP_LIN - 1)
		return true;

	// case au-dessous du joueur
	else if (map[j.pos_lin + 1][j.pos_col] != VIDE)
		return true;

	else
		return false;
}


/* renvoie true si la case à gauche du joueur n'est pas vide */
bool elt_a_gauche(struct joueur j, int map[MAP_LIN][MAP_COL])
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur à gauche de la map
	if (j.pos_col == 0)
		return true;

	// case à gauche du joueur
	else if (map[j.pos_lin][j.pos_col - 1] != VIDE)
		return true;

	else
		return false;
}


/* renvoie true si la case à droite du joueur n'est pas vide */
bool elt_a_droite(struct joueur j, int map[MAP_LIN][MAP_COL])
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur à droite de la map
	if (j.pos_col == MAP_COL - 1)
		return true;

	// case à droite du joueur
	else if (map[j.pos_lin][j.pos_col + 1] != VIDE)
		return true;

	else
		return false;
}


// Modifie la position du joueur en fonction de l'entrée au clavier
// (on suppose que le déplacement est valide)
void deplacement(struct joueur* j_ptr, int map[MAP_LIN][MAP_COL], int inputchar)
{
	// le joueur doit être dans la map
	assert_joueur_dans_map(*j_ptr, map);

	map[j_ptr->pos_lin][j_ptr->pos_col] = VIDE;  // efface le joueur de sa position

	if (inputchar == KEY_UP)  // flèche du haut pressée
	{
		j_ptr->dir = HAUT;  // tourne le joueur vers le haut

		if (!elt_en_haut(*j_ptr, map))  // si la voie est libre
		{
			j_ptr->pos_lin -= 1;  // vrai déplacement
		}
	}

	else if (inputchar == KEY_DOWN)
	{
		j_ptr->dir = BAS;

		if ( !elt_en_bas(*j_ptr, map))
		{
			j_ptr->pos_lin += 1;
		}
	}

	else if (inputchar == KEY_LEFT)
	{
		j_ptr->dir = GAUCHE;

		if ( !elt_a_gauche(*j_ptr, map))
		{
			j_ptr->pos_col -= 1;
		}
	}

	else if (inputchar == KEY_RIGHT)
	{
		j_ptr->dir = DROITE;

		if ( !elt_a_droite(*j_ptr, map))
		{	
			j_ptr->pos_col += 1;
		}
	}

	// place le bon élément dans la map en fonction de la direction du joueur
	pivote_joueur_vers_map(*j_ptr, map);

	return;
}