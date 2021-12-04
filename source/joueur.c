#include <ncurses.h>
#include <assert.h>
#include <stdio.h>



struct joueur
{
	// sur la map
	int pos_lin;
	int pos_col;
	int dir;  // direction du joueur

	// pour les combats, à chager plus tard
	int pv = 1000;
};

//Modifie la position du joueur en fonction de l'entrée au clavier
void deplacement(struct joueur* j,int c) {
	if (c == KEY_UP) {
		j->pos_lin -= 1;
	} else if (c == KEY_DOWN) {
		j->pos_lin += 1;
	} else if (c == KEY_RIGHT) {
		j->pos_col += 1;
	} else if (c == KEY_LEFT) {
		j->pos_col -= 1;
	}
}

/* Pour tester la fontction, j'ai réutillisé ce que j'avais écris dans la fonction test/map.c
La fonction à l'air de marcher, vous pouvez essayer de la tester sur vos pc au cas ou */
int main() {
	initscr();
	keypad(stdscr, TRUE); // a ne pas oublier pour utiliser KEY_UP, etc
	noecho();
	struct joueur j1;
	j1.pos_lin = -10;
	j1.pos_col = 10;
	int c = -1; //Bien penser à le laisser en int pour pouvoir être comparé avec KEY_UP, etc
	while (c != 'q') { //Marche aussi, il lit juste 'q' en tant que int pour y comparer
		c = getch();
		deplacement(&j1, c);
		printw("pos_x = %d\n",j1.pos_lin);
		printw("pos_y = %d\n",j1.pos_col);
	}
	endwin();
	return 0;
}
