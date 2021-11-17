#include <stdio.h>
#include <ncurses.h>
#include <assert.h>

const int VIDE = 0;
const int JOUEUR = 1;
const int MUR = 8;

const int ENNEMI = -1;
const int BLOC = 4; 

struct salle{
	int longueur;
	int largeur;
}

void affiche_salle(struct salle s){
	for (int j = 1; j< s.longueur; j = j+1){
		mvprintw(1, 0, "---");
	for (int i = 1; i< s.largeur; i = i+1){
		printw("-                                                             -");
	}
	refresh();
	return;
}




int main(){
	struct salle salle1;
	salle1.longueur=64;
	salle1.largeur=64;
	affiche_salle(salle1);
	return 0;
}
			
