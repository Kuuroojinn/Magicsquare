#include <stdio.h>
#include <ncurses.h>
#include <assert.h>

struct joueur{
	int pv;
	int pos_x;
	int pos_y;
};
void deplacement(struct joueur* j,int c) {
	if (c == KEY_UP) {
		j->pos_x -= 1;
	} else if (c == KEY_DOWN) {
		j->pos_x += 1;
	} else if (c == KEY_RIGHT) {
		j->pos_y += 1;
	} else if (c == KEY_LEFT) {
		j->pos_y -= 1;
	}
}

int main() {
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	struct joueur j1;
	j1.pos_x = -10;
	j1.pos_y = 10;
	int c = -1;
	while (c != 'q') {
		c = getch();
		deplacement(&j1, c);
		printw("pos_x = %d\n",j1.pos_x);
		printw("pos_y = %d\n",j1.pos_y);
	}
	endwin();
	return 0;
}
