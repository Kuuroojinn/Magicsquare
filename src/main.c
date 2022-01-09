#include <ncurses.h>
#include <stdbool.h>
#include "map.h"
#include "salles.h"
#include "joueur.h"
#include "move.h"
#include "ennemi.h"
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

	setup_taille_ecran(&SCR_LIN, &SCR_COL, &ZONE_TXT_LIN, &ZONE_TXT_COL);

	/////////////////////  DEBUT DU JEU  ///////////////////////////

	struct joueur j1 = {
		4,       // pos_lin
		9,       // pos_col
		DROITE,  // dir
		115,     // pv
		4        // atk
	};
	struct ennemi e1 = {
		10, //pv
		15  //atk
	};

    int map1[MAP_LIN][MAP_COL];
    initialise_map(map1);

    // salles de test (tjs démonstration)
    creation_salles(map1);
    
	map1[MAP_LIN-9][MAP_COL-14] = END;  // A modfier, place juste de caractère END dans la salle du bas, c'est juste pour faire mes tests

    ajoute_couloirs_h(map1, true);  // true : les ennemis sont présents
    ajoute_couloirs_v(map1, true);
	

	affiche_bordures();

	affiche_texte(0, (TAILLE_ZONE_TXT_COL - 28) / 2, "Bienvenue dans Magicsquare !");
	affiche_texte(1, 0, "Le but du jeu est d'atteindre la sortie, située dans la salle en bas à droite.");
	




	int inputchar = -1;  // doit être un int pour être comparé aux touches directionnelles
	while (inputchar != 'q')
	{
		pivote_joueur_vers_map(j1, map1);

		affiche_map(map1);
		inputchar = getch();

		if (inputchar == KEY_UP   || inputchar == KEY_DOWN ||
			inputchar == KEY_LEFT || inputchar == KEY_RIGHT )
		{
			echo();     	// Affiche la saisie du joueur pendant les combats
			deplacement(&j1, map1, inputchar,&e1);
			// noecho();	//Arrete d'afficher la saisie un fois le combat terminé
		}
	}


    endwin();
    return 0;
}
