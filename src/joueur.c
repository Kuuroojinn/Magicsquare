#include <ncurses.h>
#include <assert.h>
#include <stdio.h>
#include "joueur.h"  // contient le struct joueur

/* Définit tout ce qui est lié au joueur. */

/* directions */
const int HAUT = 1;
const int BAS = 2;
const int GAUCHE = 3;
const int DROITE = 4;


/* Hugo : Pour tester la fonction, j'ai réutilisé ce que
 * j'avais écrit dans la fonction test/map.c
 * La fonction à l'air de marcher, vous pouvez essayer 
 * de la tester sur vos pc au cas où */

/* Clément : je commente pour pouvoir utiliser le main de main.c
int main() {
	initscr();
	keypad(stdscr, TRUE);  // à ne pas oublier pour utiliser KEY_UP, etc.
	noecho();
	struct joueur j1;
	j1.pos_lin = -10;
	j1.pos_col = 10;
	int c = -1;  // Bien penser à le laisser en int pour pouvoir être comparé avec KEY_UP, etc.
	while (c != 'q') {  // Marche aussi, il lit juste 'q' en tant que int pour y comparer
		c = getch();
		deplacement(&j1, c);
		printw("pos_lin = %d\n",j1.pos_lin);
		printw("pos_col = %d\n",j1.pos_col);
	}
	endwin();
	return 0;
}
*/
