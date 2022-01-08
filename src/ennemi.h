#ifndef ENNEMI_H
#define ENNEMI_H

#include "joueur.h"

struct ennemi{
	int pv;
	int atk;
	int xe;
	int ye;
};

//Fonction de combat contre un ennemi présent sur la map
//Renvoie true si le combat est gagné par le joueur
bool combat (struct joueur* j, struct ennemi* e);

#endif
