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

/* Lance un combat du joueur contre un ennemi,
 * On peut changer manuellement la difficulté du jeu en changeant 
 * combien de pv on gagne après une victoire ou une défaite 
 * Renvoie true si le combat est gagné par le joueur
 * et false sinon
 * */
 
bool combat (struct joueur* j, struct ennemi* e)
{
	char entree;
	int action;
	int pv_max = j->pv;				//On garde les pv du joueur pour pouvoir s'en resservir par la suite
	int pv_ennemi = e->pv;			
	printw("Etes-vous sur de vouloir combattre ? Oui[o] ou Non [n]");
	scanw("%s",&entree); 
	
	if (entree == 'o') 				//On lance le combat si le joueur a rentré 'o'
	{
	
		while ((j->pv > 0) && (e->pv >0))    //Tant qu'aucun des combattants n'a la vie a 0
		{
			printw("Vous : %d | Ennemi : %d   ",j->pv,e->pv);
			printw("Que voulez vous faire : attaquer[a] ou defendre[d] ? ");
			scanw("%s",&entree);
			
			if (entree == 'a') 
			{
				action = rand()&1; //Genere un nombre aléatoire entre 0 et 1
				
				if (action == 0) 
				{
					printw("L'adversaire attaque aussi\n");
					e->pv = e->pv - j->atk;
					j->pv = j->pv - e->atk;
				} 
				else 
				{
					printw("L'adversaire se défends\n");
					e->pv = e->pv - (j->atk / 2);
				}
			} 
			else if (entree == 'd') 
			{
				action = rand()&1;
				
				if (action == 0) 
				{
					printw("L'aversaire se défends\n");
					j->pv = j->pv - (e->pv / 2);
				} 
				else 
				{
					printw("L'adversaire se défends aussi\n");
				}
			}
		}
	} 
	else 
	{
		return false;
	}
	if (e->pv <= 0) 
	{
		j->atk +=1;						//Ajoute 1 atk au joueur (équivalent d'une montée de niveau
		
		//j->pv = pv_max;       		//Remets les pv du joueur a ceux d'avant le combat
		
		j->pv +=5;                 		//redonne 5 pv a la fin d'un combat
		e->pv = pv_ennemi + 5; 			//la vie des ennemis augmente au fur et a mesure pour rajouter un peu de difficulté (peut être modifié)
		e->atk = e->atk + rand()&1; 	//Augmente de 1 ou de 0 l'attaque de l'adversaire pour corser le jeu
		
		return true;					//Renvoie true si le combat est gagné pour pouvoir supprimer l'ennemi de la map
	} 
	else 
	{
		j->pv = pv_max;					//En cas de défaite on rend les pv du joueur (peut être changé pour plus de difficulté
		e->pv = pv_ennemi;				//En cas de défaite, on remets les pv de l'ennemi a son max (sinon trop facile)
		return false;					//Indique que le combat n'est pas gagné
	}
	return false;
}		

