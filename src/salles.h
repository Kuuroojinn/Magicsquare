#ifndef SALLE_H
#define SALLE_H

#include "map.h"

#define SAL_LIN 8  // dimensions standard d'une salle (bord extérieur INCLUS)
#define SAL_COL 24  // définies ainsi pour pouvoir créer contenu dans struct salle


/* représentation d'une salle */
struct salle
{
	int pos_lin;  // position sur la map
	int pos_col;
	int contenu[SAL_LIN][SAL_COL];
};

/* entoure la salle de MURs et la remplit de VIDE */
void initialise_salle(struct salle* s);

/* ajoute les éléments de la salle dans la map */
void ajoute_salle(struct salle s, int map[MAP_LIN][MAP_COL]);


#endif