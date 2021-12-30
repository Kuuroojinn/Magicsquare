#include <ncurses.h>
#include <assert.h>
#include "salles.h"
#include "map.h"

// Dimension des salles : 8 lignes (SAL_LIN = 8) par 24 colonnes (SAL_COL = 24)
// Le bord extérieur est *INCLUS* ;
// ne pas aller chercher salle[SAL_LIN][3] par ex : dépassement de tableau

const int LONG_C_H = 7;  //longueur d'un couloir horizontal
const int LONG_C_V = 4; //longueur d'un couloir vertical

const int ORI_C_H_A = 29; //origine des couloirs horizontaux (colonne)
int ORI_C_H_O = 4; //origine des couloirs horizontaux (ligne)
const int ORI_C_V_A = 16; //origine des couloirs verticaux (colonne)
int ORI_C_V_O = 9; //origine des couloirs verticaux (ligne)

/* entoure la salle de MURs et la remplit de VIDE */
void initialise_salle(struct salle* s)
{
	// murs :
	for (int col = 0; col < SAL_COL; col++)  // murs horizontaux
	{
		s->contenu[0][col] = MUR;  // haut
		s->contenu[SAL_LIN - 1][col] = MUR;  // bas ( - 1 pour ne pas sortir de la salle)
	}
	for (int lin = 0; lin < SAL_LIN; lin++)  // murs verticaux
	{
		s->contenu[lin][0] = MUR;  // gauche
		s->contenu[lin][SAL_COL - 1] = MUR;  // droite
	}

	// vide :
	for (int lin = 1; lin < SAL_LIN - 1; lin++)  // valeurs extrêmes non comprises car des murs s'y trouvent
	{
		for (int col = 1; col < SAL_COL - 1; col++)  // idem
		{
			s->contenu[lin][col] = VIDE;
		}
	}
	return;

}


/* ajoute les éléments de la salle dans la map */
void ajoute_salle(struct salle s, int map[MAP_LIN][MAP_COL])
{
	// empêche de placer les éléments de la salle à des endroits trop loin dans la map
	assert(s.pos_lin >= 0 && s.pos_lin + SAL_LIN <= MAP_LIN);
	assert(s.pos_col >= 0 && s.pos_col + SAL_COL <= MAP_COL);


	for (int lin = 0; lin < SAL_LIN; lin++)  // lignes de la salle
	{
		for (int col = 0; col < SAL_COL; col++)  // colonnes de la salle
		{
			map[s.pos_lin + lin][s.pos_col + col] = s.contenu[lin][col];
		}
	}
	return;
}

/* ajoute les couloirs horizontaux */
void ajoute_couloir_h(int map[MAP_LIN][MAP_COL])
{	
	for (int j = 0; j < 3; j = j + 1) //3 lignes de couloirs
	{
		for (int i = ORI_C_H_A; i < MAP_COL - SAL_COL ; i = i + LONG_C_H + SAL_COL) 
		//i est la colonne du début de chaque couloir sur la ligne
		{
			for (int col = 0; col < LONG_C_H; col = col + 1)
			{
				map[ORI_C_H_O][i+col] = MUR;
				map[ORI_C_H_O + 1][i+col] = VIDE;
				map[ORI_C_H_O + 2][i+col] = VIDE;
				map[ORI_C_H_O + 3][i+col] = MUR;
			}
		}
		ORI_C_H_O = ORI_C_H_O + LONG_C_V + SAL_LIN - 2;
	}
}

/* ajoute les couloirs verticaux */
void ajoute_couloir_v(int map[MAP_LIN][MAP_COL])
{	
	for (int j = 0; j < 2; j = j + 1) //2 rangées de couloirs
	{
		for (int ligne = 0; ligne < LONG_C_V; ligne = ligne + 1) 
		//le couloir prend 4 lignes
		{
			for (int i = ORI_C_V_A; i < MAP_COL - 4; i = i + LONG_C_H + SAL_COL)  
			//on ne doit pas dépasser la map (avec 4 la largeur du couloir)
			{
				map[ORI_C_V_O][i]= MUR;
				map[ORI_C_V_O][i + 1] = VIDE;
				map[ORI_C_V_O][i + 2] = VIDE;
				map[ORI_C_V_O][i + 3] = MUR;
			}
			ORI_C_V_O = ORI_C_V_O + 1;
		}
		ORI_C_V_O = ORI_C_V_O + LONG_C_V + SAL_LIN - 6; 
		//"-6" car il faut retirer les 4 rajouter dans la boucle précédente
	}
}
