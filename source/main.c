#include <ncurses.h>
#include <locale.h>  // permet d'utiliser LC_ALL
#include "map.h"
#include "joueur.h"


int main()
{
	// démarrage et réglage de ncurses
	clear();
	initscr();
    noecho();  // masque l'input utilisateur
	keypad(stdscr, TRUE);  // permet d'utiliser le clavier
	setlocale(LC_ALL, "");  // permet d'utiliser ACS_BLOCK, etc.


	// récupération de la taille de l'écran
	int SCR_LIN;  // taille écran : lignes
    int SCR_COL;  // et colonnes
    getmaxyx(stdscr, SCR_LIN, SCR_COL);


	// pas encore utile
	struct joueur j;
	j.pos_lin = 5;
	j.pos_col = 8;
	j.dir = HAUT;
	
	
	// démonstration seulement	
    int test_map1[MAP_LIN][MAP_COL];
    initialise_map(test_map1);
    test_map1[j.pos_lin][j.pos_col] = j.dir;

    affiche_map(test_map1);
	affiche_bordure();


	// gameloop temporaire

	int c = -1;  //c doit être sous la forme d'un int pour être 
	             // comparé aux touches directionnelles 
	             // (on peut le laisser comme ça pour la map, ça dérange pas

	while (c != 'q') //Marche aussi avec KEY_DOWN, KEY_LEFT, KEY_RIGHT 
	{
		c = getch();
	}

		//On va donc surement réutliiser cette partie du code pour le déplacement du personnage
		/*
		char d;
		printw("\nVoulez vous vraiment quitter ? [Y/n]");
		scanw("%s",&d);
		if (d == 'Y') {
			endwin();
			return 0;
		}
		*/

    endwin();
}
