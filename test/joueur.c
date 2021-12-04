#include <stdio.h>
#include <ncurses.h>
#include <assert.h>

struct joueur{
	int pv = 1000;
	pos_x = 0;
	pos_y = 0;
}
if /*Touche = flèche haut*/ {
	joueur->pos_x -= 1;
} else if /*Touche = flèche bas*/ {
	joueur->pos_x += 1;
} else if /*Touche = flèche droite*/ {
	joueur->pos_y += 1;
} else if /*Touche = flèche gauche*/ {
	joueur->pos_y -= 1;
}
