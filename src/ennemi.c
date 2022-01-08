#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "joueur.h"


/* differents types d'ennemis qui pourront exister
 * en plusieurs instances sur la map ? */

struct ennemi {
	int pv;
	int atk;
	int lin;  // position 
	int col;
};

struct ennemi e1 = {1};


bool combat (struct joueur* j, struct ennemi* e){
	char entree;
	int action;
	printw("Etes-vous sur de vouloir combattre ? Oui[o] ou Non [n]");
	scanw("%s",&entree);
	if (entree == 'n'){
		return false;   //ON considère donc que le joueur a perdu le combat
	}
	
	int pv_max = j->pv;
	int pv_ennemi = e->pv;
	while ((j->pv > 0) && (e->pv >0)){
		printw("Vous : %d | Ennemi : %d",j->pv,e->pv);
		printw("Que voulez vous faire : attaquer[a] ou defendre[d] ? ");
		scanw("%s",&entree);
		if (entree == 'a') {
			action = rand()&1; //Genere un nombre aléatoire entre 0 et 1
			if (action == 0) {
				printw("L'adversaire attaque aussi\n");
				e->pv = e->pv - j->atk;
				j->pv = j->pv - e->atk;
			} else {
				printw("L'adversaire se défends\n");
				e->pv = e->pv - (j->atk / 2);
			}
		} else if (entree == 'd') {
			action = rand()&1;
			if (action == 0) {
				printw("L'aversaire se défends\n");
				j->pv = j->pv - (e->pv / 2);
			} else {
				printw("L'adversaire se défends aussi\n");
			}
		}
	}
	if (e->pv <= 0) {
		j->atk +=1;
		j->pv = pv_max;         //Remets les pv du joueur a ceux d'avant le combat
		e->pv = pv_ennemi + 5; //la vie des ennemis augmente au fur et a mesure pour rajouter un peu de difficulté (peut être modifié)
		e->atk = e->atk + rand()&1; //Augmente de 1 ou de 0 l'attaque de l'adversaire pour corser le jeu
		return true;
	} else {
		j->pv = pv_max;
		e->pv = pv_ennemi;
		return false;
	}
	return false;
}		
/* Je compte rajouter le système de combat :
 * - quand tu bump un ennemi, on te demande si tu veux combattre
 * - si oui, tu choisis entre te défendre ou attaquer (penser a rajouter atk et pv pour les ennemis et le joueur)
 * - et du coup tu combats jusqu'a ce que les pv d'un des deux combattants descends a 0
 * - si le joueur gagne, il récupère 1 atk en plus pour que ce soit plus facile de vaincre les autres ennemis
 * - je pense aussi a rajouter un boss a la fin pour créer un but
 * - pour l'instant je vais faire en sorte que ça ne fasse pas recommencer le jeu a chaque défaite du joueur (on verra pour la suite)
 * */
