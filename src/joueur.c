#include <ncurses.h>
#include <assert.h>
#include <stdio.h>
#include "joueur.h"  // contient le struct joueur

/* Définit tout ce qui est lié au joueur. */

/* directions */
const int HAUT = 1;
const int BAS = 2;
const int GAUCHE = 3;
const int DROITE = 4;

const int MAX_PV = 5;
