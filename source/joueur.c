#include <ncurses.h>
#include <assert.h>

struct joueur
{
	// sur la map
	int pos_x;
	int pos_y;

	// pour les combats, à chager plus tard
	int pv = 1000;
}
