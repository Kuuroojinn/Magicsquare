#include <ncurses.h>
#include "map.h"
#include "salles.h"
#include "joueur.h"
#include "move.h"

int main()
{
	// démarrage et réglage de ncurses
	clear();
	initscr();
    noecho();  // masque l'input utilisateur
	keypad(stdscr, TRUE);  // permet d'utiliser le clavier

	start_color();
	setup_couleur();

	// récupération de la taille de l'écran
	int SCR_LIN;  // taille écran : lignes
    int SCR_COL;  // et colonnes
    getmaxyx(stdscr, SCR_LIN, SCR_COL);




	/////////////////////  DEBUT DU JEU  ///////////////////////////

	// démonstration seulement
	struct joueur j1 = {
		16,
		12,
		DROITE
	};

    int map1[MAP_LIN][MAP_COL];
    initialise_map(map1);
   	
    // salle de test
   	struct salle salle1 = {
		2,
		6,
		{
			{MUR, MUR,  MUR, MUR, VIDE, VIDE, MUR, MUR, MUR, MUR,  MUR, MUR, VIDE, VIDE, MUR, MUR, MUR, MUR,  MUR, MUR, VIDE, VIDE, MUR, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR, MUR, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, MUR},
			{MUR, MUR,  VIDE, MUR, MUR, MUR, MUR, MUR}
		}
	};

	ajoute_salle(salle1, map1);

	affiche_bordure();


	// gameloop temporaire

	int inputchar = -1;  // inputchar doit être sous la forme d'un int pour être 
	             // comparé aux touches directionnelles 
	             // (on peut le laisser comme ça pour la map, ça dérange pas)

	while (inputchar != 'q') // Marche aussi avec KEY_DOWN, KEY_LEFT, KEY_RIGHT 
	{
		pivote_joueur_vers_map(j1, map1);

		affiche_map(map1);
		inputchar = getch();

		if (inputchar == KEY_UP   || inputchar == KEY_DOWN ||
			inputchar == KEY_LEFT || inputchar == KEY_RIGHT )
		{
			deplacement(&j1, map1, inputchar);
		}


	}


    endwin();
    return 0;
}
