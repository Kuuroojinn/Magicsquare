#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>


/* differents types d'ennemis qui pourront exister
 * en plusieurs instances sur la map ? */

struct ennemi1{
	int pv = 100;
	int atk;
	int xe = ;
	int ye = ;
}

struct ennemi2{
	int pv = 200;
	int atk;
	int xe = ;
	int ye = ;
}

struct ennemi3{
	int atk;
	int pv = 300;
	int xe = ;
	int ye = ;
}

void combat (struct* joueur j, struct* ennemi e)
	pv_max = j->pv;
	while ((j->pv > 0) && (e->pv >0)){
		char entree;
		printw("Vous : %d | Ennemi : %d",j->pv,e->pv);
		printw("Que voulez vous faire : attaquer[a] ou defendre[d] ? ");
		scanw("%s",&entree);
		if (entree == 'a') {
			e->pv = e->pv - j->atk;
		}
	}
	if (e->pv <= 0) {
		j->atk +=1;
		j->pv = pv_max;
	} else {
		j->pv = pv_max;
	}
}
		
/* Je compte rajouter le système de combat :
 * - quand tu bump un ennemi, on te demande si tu veux combattre
 * - si oui, tu choisis entre te défendre ou attaquer (penser a rajouter atk et pv pour les ennemis et le joueur)
 * - et du coup tu combats jusqu'a ce que les pv d'un des deux combattants descends a 0
 * - si le joueur gagne, il récupère 1 atk en plus pour que ce soit plus facile de vaincre les autres ennemis
 * - je pense aussi a rajouter un boss a la fin pour créer un but
 * - pour l'instant je vais faire en sorte que ça ne fasse pas recommencer le jeu a chaque défaite du joueur (on verra pour la suite)
 * */
