#include <ncurses.h>
#include "map.h"
#include "joueur.h"


int main()
{
	initscr();
    noecho();  // masque l'input utilisateur
	clear();
	keypad(stdscr, TRUE);

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
    while (true){
		int c = -1;  //c doit être sous la forme d'un int pour être comparé aux touches directionnelles (on peut le laisser comme ça pour la map, ça dérange pas
		while (c != 'q') //Marche aussi avec KEY_DOWN, KEY_LEFT, KEY_RIGHT 
		{
        //debug_scr_size(); //Je l'ai caché vu que c'était pas utile pour tester la fonction
			c = getch();
			//printw("%d",c); //affiche la touche préssée sous la forme d'un int 
		}    //Ici ferme la map dès qu'on presse la touche fléche du haut
		//On va donc surement réutliiser cette partie du code pour le déplacement du personnage
		char d;
		echo();
		printw("\nVoulez vous vraiment quitter ? [Y/n]");
		scanw("%s",&d);
		noecho();
		if (d == 'Y') {
			endwin();
			return 0;
		}
	}

    endwin();
}
