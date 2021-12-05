#include <ncurses.h>
#include <assert.h>
#include "salles.h"


/* ne faudrait-il mieux pas faire une fonction ajoute_salle qui
 * ajouterait les éléments à la map ? */
void affiche_salle(struct salle s)
{
	for (int j = 1; j< s.longueur; j = j+1)
	{
		mvprintw(1, 0, "---"); 
	}
	for (int i = 1; i< s.largeur; i = i+1)
	{
		printw("--");
	}
	refresh();
	return;
}

void ajoute_salle(struct salle s)
{

}