#include <ncurses.h>
#include "map.h"
#include "salles.h"
#include "joueur.h"
#include "move.h"
#include "affichage.h"

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
		4,       // pos_lin
		9,       // pos_col
		DROITE,  // dir
		5,       // pv
		4        // atk
	};

    int map1[MAP_LIN][MAP_COL];
    initialise_map(map1);

    // salles de test (tjs démonstration)
    creation_salles(map1);

    ajoute_couloir_h(map1);
    ajoute_couloir_v(map1);
	

	affiche_bordure(SCR_LIN, SCR_COL);


    // test d'affichage des conteneurs à pv
	affiche_char_val(PV_VIDE, 1, 1);
	affiche_char_val(PV_PLEIN, 1, 2);


	// gameloop temporaire

	// inputchar doit être un int pour être comparé aux touches directionnelles
	int inputchar = -1;


	while (inputchar != 'q')
	{
		pivote_joueur_vers_map(j1, map1);

		affiche_map(map1, SCR_LIN, SCR_COL);
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
