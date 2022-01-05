#include <ncurses.h>
#include <assert.h>
#include "salles.h"
#include "map.h"


// Dimension des salles : 8 lignes (SAL_LIN = 8) par 24 colonnes (SAL_COL = 24)
// Le bord extérieur est *INCLUS* ;
// ne pas aller chercher salle[SAL_LIN][3] par ex : dépassement de tableau


const int LONG_COULOIR_H = 7;     // longueur d'un couloir horizontal
const int LONG_COULOIR_V = 3;     // longueur d'un couloir vertical

const int ORI_SALLE1_LIN = 2;     // origine de la 1ère salle (ligne)
const int ORI_SALLE1_COL = 6;     // origine de la 1ère salle (colonne)

// origine des couloirs horizontaux (ligne) ;
// + (SAL_LIN / 2) - 2 : centre le couloir au milieu du mur
const int ORI_COULOIR_H_LIN = ORI_SALLE1_LIN + (SAL_LIN / 2) - 2;
// origine des couloirs horizontaux (colonne) ; - 1 car le couloir commence dans la salle
const int ORI_COULOIR_H_COL = ORI_SALLE1_COL + SAL_COL - 1;

// origine des couloirs verticaux (ligne)
const int ORI_COULOIR_V_LIN = ORI_SALLE1_LIN + SAL_LIN - 1;
// origine des couloirs verticaux (colonne)
// + (SAL_COL / 2) - 2 : centre le couloir au milieu du mur
const int ORI_COULOIR_V_COL = ORI_SALLE1_COL + (SAL_COL / 2) - 2; 

struct salle salle_actuelle; //struct de la salle ici pour l'utiliser dans plusieurs fonctions

int calcul_nbr_rangee_couloirs() //Calcule le nombre de rangées de couloirs nécéssaire
{
	int nb_c = 0;
	for (salle_actuelle.pos_lin = ORI_SALLE1_LIN; salle_actuelle.pos_lin < MAP_LIN - SAL_LIN; salle_actuelle.pos_lin += LONG_COULOIR_V + SAL_LIN - 2)
	{
		nb_c = nb_c + 1;
	}
return nb_c;
}

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

//J'ai réduit la largeur des couloirs pour pouvoir placer un ennemi devant

/* ajoute les couloirs horizontaux */
void ajoute_couloirs_h(int map[MAP_LIN][MAP_COL])
{	
	int tmp_ori_couloir_h_lin = ORI_COULOIR_H_LIN;

	for (int rangee = 0; rangee < calcul_nbr_rangee_couloirs(); rangee++) 
	{
		for (int ori_couloir_actuel = ORI_COULOIR_H_COL; ori_couloir_actuel < MAP_COL - SAL_COL - LONG_COULOIR_H; ori_couloir_actuel += LONG_COULOIR_H + SAL_COL - 2) 
		// ori_couloir_actuel est la colonne du début de chaque couloir sur la ligne
		//"-2" car le couloir est collé à la salle
		{
			for (int col = 0; col < LONG_COULOIR_H; col++)
			{
				//map[tmp_ori_couloir_h_lin][ori_couloir_actuel+col] = MUR;
				map[tmp_ori_couloir_h_lin + 1][ori_couloir_actuel+col] = MUR;
				map[tmp_ori_couloir_h_lin + 2][ori_couloir_actuel-1] = ENNEMI;
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
void ajoute_couloirs_v(int map[MAP_LIN][MAP_COL])
{	
	int tmp_ori_couloir_v_lin = ORI_COULOIR_V_LIN;
	int couloir_lin = ORI_COULOIR_V_LIN;
	
	for (int rangee = 0; rangee < calcul_nbr_rangee_couloirs() - 1; rangee++) // "-1" car on a 1 rangée de couloirs verticaux de moins que d'horizontaux
	{
		for (int ligne = 0; ligne < LONG_COULOIR_V; ligne++) 
		{
			for (int ori_couloir_actuel = ORI_COULOIR_V_COL; ori_couloir_actuel < MAP_COL - SAL_COL; ori_couloir_actuel += LONG_COULOIR_H + SAL_COL - 2)  
			//ori_couloir_actuel est la colonne du côté gauche du couloir et le couloir ne doit pas dépasser la map (d'où 4 la largeur du couloir)
			{
				//map[tmp_ori_couloir_v_lin][ori_couloir_actuel]= MUR;
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 1] = MUR;
				map[couloir_lin-1][ori_couloir_actuel + 2] = ENNEMI;
				
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 2] = VIDE;
				
				map[tmp_ori_couloir_v_lin][ori_couloir_actuel + 3] = MUR;
			}
			tmp_ori_couloir_v_lin += 1;
		}
		couloir_lin += LONG_COULOIR_V + SAL_LIN - 2;
		tmp_ori_couloir_v_lin += LONG_COULOIR_V + SAL_LIN - 6; 
		//"-6" car il faut retirer les 4 rajoutés dans la boucle précédente
	}
	return;
}


/* Crée automatiquement les salles */
void creation_salles(int map[MAP_LIN][MAP_COL])
{
	initialise_salle(&salle_actuelle);

	for (salle_actuelle.pos_col = ORI_SALLE1_COL; salle_actuelle.pos_col < MAP_COL - SAL_COL; salle_actuelle.pos_col += LONG_COULOIR_H + SAL_COL - 2)
	//Change la colonne de la salle actuelle
	{
		for (salle_actuelle.pos_lin = ORI_SALLE1_LIN; salle_actuelle.pos_lin < MAP_LIN - SAL_LIN; salle_actuelle.pos_lin += LONG_COULOIR_V + SAL_LIN - 2)
		//Change la ligne de la salle actuelle
		{
			ajoute_salle(salle_actuelle, map);
		}
	}
	return;
}
