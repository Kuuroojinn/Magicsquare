#include <ncurses.h>
#include <locale.h>  // permet d'utiliser LC_ALL
#include "map.h"
#include "salles.h"
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




	
	// démonstration seulement	
    int map1[MAP_LIN][MAP_COL];
    initialise_map(map1);
   	
    // salle de test
   	struct salle salle1 = {
		14,
		20,
		{
			{MUR, MUR, MUR, MUR, VIDE, VIDE, MUR, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, MUR, MUR, MUR, MUR, MUR, MUR, MUR}
		}
	};

	ajoute_salle(salle1, map1);

    affiche_map(map1);
	affiche_bordure();


	// gameloop temporaire

	int c = -1;  //c doit être sous la forme d'un int pour être 
	             // comparé aux touches directionnelles 
	             // (on peut le laisser comme ça pour la map, ça dérange pas)

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
