#include <ncurses.h>
#include <assert.h>
#include "salles.h"
#include "map.h"


// Dimension des salles : 8 lignes (SAL_LIN = 8) par 24 colonnes (SAL_COL = 24)
// Le bord extérieur est *INCLUS* ;
// ne pas aller chercher salle[SAL_LIN][3] par ex : dépassement de tableau


const int LONG_COULOIR_H = 7;  // longueur d'un couloir horizontal
const int LONG_COULOIR_V = 4; // longueur d'un couloir vertical

const int ORI_COULOIR_H_COL = 29; // origine des couloirs horizontaux (colonne)
const int ORI_COULOIR_H_LIN = 4; // origine des couloirs horizontaux (ligne)
const int ORI_COULOIR_V_COL = 16; // origine des couloirs verticaux (colonne)
const int ORI_COULOIR_V_LIN = 9; // origine des couloirs verticaux (ligne)


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
	int tmp_ori_couloir_h_lin = ORI_COULOIR_H_LIN;

	for (int rangee = 0; rangee < 3; rangee++) // 3 rangées de couloirs
	{
		for (int ori_couloir_actuel = ORI_COULOIR_H_COL; ori_couloir_actuel < MAP_COL - SAL_COL ; ori_couloir_actuel += LONG_COULOIR_H + SAL_COL - 2) 
		// ori_couloir_actuel est la colonne du début de chaque couloir sur la ligne
		//"-2" car le couloir est collé à la salle
		{
			for (int col = 0; col < LONG_COULOIR_H; col++)
			{
				map[tmp_ori_couloir_h_lin][ori_couloir_actuel+col] = MUR;
				map[tmp_ori_couloir_h_lin + 1][ori_couloir_actuel+col] = VIDE;
				map[tmp_ori_couloir_h_lin + 2][ori_couloir_actuel+col] = VIDE;
				map[tmp_ori_couloir_h_lin + 3][ori_couloir_actuel+col] = MUR;
			}
		}
		tmp_ori_couloir_h_lin += LONG_COULOIR_V + SAL_LIN - 2;
		//"-2" car le couloir et la salle sont connectés
	}
	return;
}


/* ajoute les couloirs verticaux */
void ajoute_couloir_v(int map[MAP_LIN][MAP_COL])
{	
	int tmp_ori_couloir_v_lin = ORI_COULOIR_V_LIN;

	for (int rangee = 0; rangee < 2; rangee++) // 2 rangées de couloirs
	{
		for (int ligne = 0; ligne < LONG_COULOIR_V; ligne++) 
		// le couloir prend 4 lignes
		{
			for (int ori_couloir_actuel = ORI_COULOIR_V_COL; ori_couloir_actuel < MAP_COL - 4; ori_couloir_actuel += LONG_COULOIR_H + SAL_COL - 2)  
			//ori_couloir_actuel est la colonne du côté gauche du couloir et le couloir ne doit pas dépasser la map (d'où 4 la largeur du couloir)
			{
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel]= MUR;
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 1] = VIDE;
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 2] = VIDE;
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 3] = MUR;
			}
			tmp_ori_couloir_v_lin += 1;
		}
		tmp_ori_couloir_v_lin += LONG_COULOIR_V + SAL_LIN - 6; 
		//"-6" car il faut retirer les 4 rajoutés dans la boucle précédente
	}
	return;
}