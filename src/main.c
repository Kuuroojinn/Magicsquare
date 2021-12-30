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
		4,
		9,
		DROITE,
		5  // pv
	};

    int map1[MAP_LIN][MAP_COL];
    initialise_map(map1);
    ajoute_couloir_h(map1);
    ajoute_couloir_v(map1);
	
    // salle de test (tjs démonstration)
	struct salle salle1;
	initialise_salle(&salle1);
	salle1.contenu[3][SAL_COL - 1] = VIDE;  // portes (à mettre dans une fonction)
	salle1.contenu[4][SAL_COL - 1] = VIDE;
	salle1.contenu[SAL_LIN - 1][11] = VIDE;
	salle1.contenu[SAL_LIN - 1][12] = VIDE;

	salle1.pos_lin = 2;
	salle1.pos_col = 6;
	ajoute_salle(salle1, map1);

	salle1.pos_lin = 12;
	salle1.contenu[0][11] = VIDE;
	salle1.contenu[0][12] = VIDE;
	ajoute_salle(salle1, map1);

	salle1.pos_lin = 22;
	ajoute_salle(salle1, map1);


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
