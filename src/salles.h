#ifndef SALLE_H
#define SALLE_H

#include "map.h"

const int SAL_LIN;  // dimensions standard d'une salle
const int SAL_COL;  // (bord extérieur INCLUS)


/* représentation d'une salle */
struct salle
{
	int pos_lin;  // nécessaire pour la positionner sur la map
	int pos_col;
	// int contenu[SAL_LIN][SAL_COL]
	int contenu[8][24];  // ATTENTION : valeurs hardcodées car sinon erreur 
};

/* ajoute les éléments de la salle dans la map */
void ajoute_salle(struct salle s, int map[MAP_LIN][MAP_COL]);


#endif