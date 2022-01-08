#ifndef ENNEMI_H
#define ENNEMI_H

#include "joueur.h"

struct ennemi{
	int pv;
	int atk;
	int xe;
	int ye;
};
bool combat (struct joueur* j, struct ennemi* e);

#endif
