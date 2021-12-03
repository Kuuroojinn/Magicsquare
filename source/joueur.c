#include <ncurses.h>
#include <assert.h>



struct joueur
{
	// sur la map
	int pos_lin;
	int pos_col;
	int dir;  // direction du joueur

	// pour les combats, à chager plus tard
	int pv = 1000;
};
