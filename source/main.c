#include <ncurses.h>
#include "map.h"
#include "joueur.h"


int main()
{
	initscr();
    noecho();  // masque l'input utilisateur
	clear();

	// pas encore utile
	struct joueur j;
	j.pos_lin = 5;
	j.pos_col = 8;
	j.dir = HAUT;
	
	
	// démonstration seulement	
    int test_map1[MAP_LIN][MAP_COL];
    initialise_map(test_map1);
    test_map1[MAP_LIN/2][MAP_COL/2] = JOUEUR_BAS;

	affiche_map(test_map1);

	// gameloop temporaire
    char c = 'a';
    while (c != 'q')
    {
        c = getch();
    }    

    endwin();
	
	return 0;
}
