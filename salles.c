#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include "salles.h"
#include "map.h"


// Dimension des salles (cf salles.h) : 8 lignes (SAL_LIN = 8) par 24 colonnes (SAL_COL = 24)
// Le bord extérieur est *INCLUS* ;
// ne pas aller chercher salle[SAL_LIN][3] par ex : dépassement de tableau

const int LONG_COULOIR_H = 7;     // longueur d'un couloir horizontal
const int LONG_COULOIR_V = 4;     // longueur d'un couloir vertical

const int ORI_SALLE1_LIN = 2;     // origine de la 1ère salle (ligne)
const int ORI_SALLE1_COL = 4;     // origine de la 1ère salle (colonne)

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


/* Calcule le nombre de rangées de couloirs horizontaux nécessaires */
int calcul_nbr_rangee_couloirs()
{
	// seuil (ligne) à partir duquel il ne faut plus ajouter de salles pour ne pas sortir de la map :
	int seuil_lin = MAP_LIN - SAL_LIN;
	// décalage d'une salle à la suivante (- 2 car le couloir commence dans la salle) :
	int decalage = SAL_LIN + LONG_COULOIR_V - 2;

	int nbr_couloirs = 0;
	for(int salle_actuelle_lin = ORI_SALLE1_LIN; salle_actuelle_lin < seuil_lin; salle_actuelle_lin += decalage)
	{
		nbr_couloirs += 1;
	}
	return nbr_couloirs;
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


/* Crée automatiquement les salles et les ajoute dans la map en les espaçant */
void creation_salles(int map[MAP_LIN][MAP_COL])
{
	// salle qui sera ajoutée
	struct salle s;
	initialise_salle(&s);

	int seuil_lin = MAP_LIN - SAL_LIN;  // seuil à ne pas dépasser pour ne pas sortir de la map
	int seuil_col = MAP_COL - SAL_COL;
	int decalage_lin = SAL_LIN + LONG_COULOIR_V - 2;  // décalage entre les salles (- 2 car le couloir commence dans la salle)
	int decalage_col = SAL_COL + LONG_COULOIR_H - 2;

	//Change la ligne de la salle actuelle
	for (s.pos_lin = ORI_SALLE1_LIN; s.pos_lin < seuil_lin; s.pos_lin += decalage_lin)
	{
		//Change la colonne de la salle actuelle
		for (s.pos_col = ORI_SALLE1_COL; s.pos_col < seuil_col; s.pos_col += decalage_col)
		{
			ajoute_salle(s, map);
		}
	
	}
	return;
}


/* ajoute les couloirs horizontaux, et un ennemi devant
 * chaque couloir si le paramètre ennemi vaut true */
void ajoute_couloirs_h(int map[MAP_LIN][MAP_COL], bool ennemi)
{	
	// seuil (colonne) à ne pas dépasser pour ne pas sortir de la map :
	int seuil_col = MAP_COL - SAL_COL - LONG_COULOIR_H;  
	// décalage (colonne) d'un couloir au suivant (- 2 car le couloir commence dans la salle) :
	int decalage_col = LONG_COULOIR_H + SAL_COL - 2;
	// décalage (ligne) d'un couloir au suivant (- 2 car le couloir commence dans la salle) :
	int decalage_lin = LONG_COULOIR_V + SAL_LIN - 2;

	int debut_coul_lin = ORI_COULOIR_H_LIN;  // ligne de début du couloir actuel

	// parcourt les rangées de couloirs horizontalement
	for (int rangee = 0; rangee < calcul_nbr_rangee_couloirs(); rangee++)
	{
		// debut_coul_col : colonne du début du couloir actuel
		for (int debut_coul_col = ORI_COULOIR_H_COL; debut_coul_col < seuil_col; debut_coul_col += decalage_col)
		{
			for (int col = 0; col < LONG_COULOIR_H; col++)  // ajoute le couloir, colonne par colonne
			{
				map[debut_coul_lin + 0][debut_coul_col + col] = MUR;
				map[debut_coul_lin + 1][debut_coul_col + col] = VIDE;
				map[debut_coul_lin + 2][debut_coul_col + col] = MUR;
			}
			if (ennemi) // place un ennemi devant le couloir
			{
				map[debut_coul_lin + 1][debut_coul_col - 1] = ENNEMI;
			}
		}
		debut_coul_lin += decalage_lin;  // décale la ligne de début du couloir
	}
	return;
}


/* ajoute les couloirs verticaux, et un ennemi devant
 * chaque couloir si le paramètre ennemi vaut true */
void ajoute_couloirs_v(int map[MAP_LIN][MAP_COL], bool ennemi)
{	
	// seuil (colonne) à ne pas dépasser pour ne pas sortir de la map :
	int seuil_col = MAP_COL - (SAL_COL / 2);
	// (colonne) d'un couloir au suivant (- 2 car le couloir commence dans la salle) :
	int decalage_col = LONG_COULOIR_H + SAL_COL - 2;
	// décalage (ligne) d'un couloir au suivant (- 2 car le couloir commence dans la salle) :
	int decalage_lin = LONG_COULOIR_V + SAL_LIN - 2;

	int debut_coul_lin = ORI_COULOIR_V_LIN;  // ligne de début du couloir actuel

	// parcourt les rangées de couloirs horizontalement ; -1 car il y a
	// 1 rangée de couloirs verticaux de moins que de couloirs horizontaux
	for (int rangee = 0; rangee < calcul_nbr_rangee_couloirs() - 1; rangee++)
	{
		//debut_coul_col : colonne du côté gauche du couloir et le couloir ne doit pas dépasser la map (d'où 4 la largeur du couloir)
		for (int debut_coul_col = ORI_COULOIR_V_COL; debut_coul_col < seuil_col; debut_coul_col += decalage_col)  
		{
			for (int lin = 0; lin < LONG_COULOIR_V; lin++)  // ajoute le couloir, ligne par ligne
			{
				map[debut_coul_lin + lin][debut_coul_col + 0] = MUR;                 
				map[debut_coul_lin + lin][debut_coul_col + 1] = VIDE;
				map[debut_coul_lin + lin][debut_coul_col + 2] = MUR;
			}
			if (ennemi) // place un ennemi devant le couloir
			{
				map[debut_coul_lin - 1][debut_coul_col + 1] = ENNEMI;
			}
		}
		debut_coul_lin += decalage_lin; 
	}
	return;
}
