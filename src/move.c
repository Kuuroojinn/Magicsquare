#include <stdbool.h>
#include <ncurses.h>
#include "move.h"
#include "map.h"
#include "ennemi.h"
#include "affichage.h"

/////////////   Déplacements gérés dans ce fichier   //////////////


/* renvoie true si l'element recherché est dans la case au-dessus du joueur */
bool test_elt_en_haut(struct joueur j, int map[MAP_LIN][MAP_COL], int element) 
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur en haut de la map
	if (j.pos_lin == 0)
		return true;

	// case au-dessus du joueur
	else if (map[j.pos_lin - 1][j.pos_col] == element)
		return true;

	else
		return false;
}


/* renvoie true si l'element recherché est dans la case au-dessous du joueur */
bool test_elt_en_bas(struct joueur j, int map[MAP_LIN][MAP_COL], int element)
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur en bas de la map
	if (j.pos_lin == MAP_LIN - 1)
		return true;

	// case au-dessous du joueur
	else if (map[j.pos_lin + 1][j.pos_col] == element)
		return true;

	else
		return false;
}


/* renvoie true si l'élément recherché est dans la case à gauche du joueur */
bool test_elt_a_gauche(struct joueur j, int map[MAP_LIN][MAP_COL], int element)
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur à gauche de la map
	if (j.pos_col == 0)
		return true;

	// case à gauche du joueur
	else if (map[j.pos_lin][j.pos_col - 1] == element)
		return true;

	else
		return false;
}


/* renvoie true si l'élément recherché est dans la case à droite du joueur */
bool test_elt_a_droite(struct joueur j, int map[MAP_LIN][MAP_COL], int element)
{
	// le joueur doit se trouver dans la map
	assert_joueur_dans_map(j, map);

	// cas où joueur à droite de la map
	if (j.pos_col == MAP_COL - 1)
		return true;

	// case à droite du joueur
	else if (map[j.pos_lin][j.pos_col + 1] == element)
		return true;

	else
		return false;
}


/* Modifie la position du joueur en fonction de l'entrée au clavier (on suppose que
 * le déplacement est valide) ; le cas échéant, lance un combat ou la fin du jeu */
void deplacement(struct joueur* j_ptr, int map[MAP_LIN][MAP_COL], int inputchar, struct ennemi* e_ptr)
{
	// le joueur doit être dans la map
	assert_joueur_dans_map(*j_ptr, map);

	efface_zone_texte();  // pour pouvoir afficher les dialogues si besoin
	map[j_ptr->pos_lin][j_ptr->pos_col] = VIDE;  // efface le joueur de sa position

	if (inputchar == KEY_UP)  // flèche du haut pressée
	{
		j_ptr->dir = HAUT;  // tourne le joueur vers le haut

		if (test_elt_en_haut(*j_ptr, map, VIDE))  // si la voie est libre
		{
			j_ptr->pos_lin -= 1;  // vrai déplacement
		} 
		else if (test_elt_en_haut(*j_ptr, map, ENNEMI)) 
		{
			pivote_joueur_vers_map(*j_ptr, map);  // le joueur se tourne vers l'ennemi
			affiche_map(map);                     // et on l'affiche
			if (combat(j_ptr,e_ptr))              // lance un combat ; s'il est gagné :
			{
				map[j_ptr->pos_lin - 1][j_ptr->pos_col] = VIDE;  // remplace la case où était l'ennemi par du vide
			}
		}
		else if (test_elt_en_haut(*j_ptr, map, END))
		{
			efface_zone_texte();
			affiche_texte(1, 0, "Bravo, vous avez atteint la fin !");
			affiche_texte(2, 0, "Merci d'avoir joue a notre jeu :)");
			affiche_texte(3, 0, "Appuyez sur [q] pour quitter ou vous pouvez continuer en battant tous les ennemis");
		}
	}

	else if (inputchar == KEY_DOWN)
	{
		j_ptr->dir = BAS;

		if (test_elt_en_bas(*j_ptr, map, VIDE))
		{
			j_ptr->pos_lin += 1;
		}
		else if (test_elt_en_bas(*j_ptr, map, ENNEMI))
		{
			pivote_joueur_vers_map(*j_ptr, map);
			affiche_map(map);
			if (combat(j_ptr,e_ptr))
			{
				map[j_ptr->pos_lin + 1][j_ptr->pos_col] = VIDE;
			}
		}
		else if (test_elt_en_bas(*j_ptr, map, END))
		{
			efface_zone_texte();
			affiche_texte(1, 0, "Bravo, vous avez atteint la fin !");
			affiche_texte(2, 0, "Merci d'avoir joue a notre jeu :)");
			affiche_texte(3, 0, "Appuyez sur [q] pour quitter ou vous pouvez continuer en battant tous les ennemis");
		}
	}

	else if (inputchar == KEY_LEFT)
	{
		j_ptr->dir = GAUCHE;

		if (test_elt_a_gauche(*j_ptr, map, VIDE))
		{
			j_ptr->pos_col -= 1;
		}
		else if (test_elt_a_gauche(*j_ptr, map, ENNEMI))
		{
			pivote_joueur_vers_map(*j_ptr, map);
			affiche_map(map);
			if (combat(j_ptr,e_ptr))
			{
				map[j_ptr->pos_lin][j_ptr->pos_col - 1] = VIDE;
			}
		}
		else if (test_elt_a_gauche(*j_ptr, map, END)) 
		{
			efface_zone_texte();
			affiche_texte(1, 0, "Bravo, vous avez atteint la fin !");
			affiche_texte(2, 0, "Merci d'avoir joue a notre jeu :)");
			affiche_texte(3, 0, "Appuyez sur [q] pour quitter ou vous pouvez continuer en battant tous les ennemis");
		}
	}

	else if (inputchar == KEY_RIGHT)
	{
		j_ptr->dir = DROITE;

		if (test_elt_a_droite(*j_ptr, map, VIDE))
		{	
			j_ptr->pos_col += 1;
		}
		else if (test_elt_a_droite(*j_ptr, map, ENNEMI))
		{
			pivote_joueur_vers_map(*j_ptr, map);
			affiche_map(map);
			if (combat(j_ptr,e_ptr)) 
			{
				map[j_ptr->pos_lin][j_ptr->pos_col + 1] = VIDE;
			}
		}
		else if (test_elt_a_droite(*j_ptr, map, END))
		{
			efface_zone_texte();
			affiche_texte(1, 0, "Bravo, vous avez atteint la fin !");
			affiche_texte(2, 0, "Merci d'avoir joue a notre jeu :)");
			affiche_texte(3, 0, "Appuyez sur [q] pour quitter ou vous pouvez continuer en battant tous les ennemis");
		}
	}

	// place le bon élément dans la map en fonction de la direction du joueur
	pivote_joueur_vers_map(*j_ptr, map);

	return;
}
