#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "joueur.h"
#include "affichage.h"


// un type d'ennemi qui a 1 pv
struct ennemi e1 = {1};


/* effectue un tour de combat entre un joueur et un ennemi.
 * (choix : attaque ou défense) */
void tour_de_combat(struct joueur* j, struct ennemi* e)
{
	char entree;
	int action_ennemi;

	affiche_pv_combat(j, e);
	affiche_texte(1, 0, "Que voulez-vous faire : attaquer [a] ou defendre [d] ? ");
	scanw("%c", &entree);
	
	if (entree == 'a')  // le joueur attaque
	{
		// Génère un nombre aléatoire : 0 (attaque) ou 1 (défense)
		action_ennemi = (rand() % 2);  // nombre aléatoire entre 0 et 1
		
		if (action_ennemi == 0)  // l'ennemi attaque
		{
			efface_ligne_texte(2);
			efface_ligne_texte(3);
			affiche_texte(2, 0, "L'adversaire attaque aussi !");
			e->pv -= j->atk;
			j->pv -= e->atk;
			affiche_degats_subis(3, 'b', e->atk, j->atk);
		} 
		else  // l'ennemi se défend
		{
			efface_ligne_texte(2);
			efface_ligne_texte(3);
			affiche_texte(2, 0, "Vous attaquez, mais l'adversaire se défend.");
			e->pv -= (j->atk / 2);
			affiche_degats_subis(3, 'e', (j->atk / 2), 0);
		}
	} 
	else if (entree == 'd')  // le joueur se défend
	{
		action_ennemi = rand()&1;
		
		if (action_ennemi == 0)  // l'ennemi attaque
		{
			efface_ligne_texte(2);
			efface_ligne_texte(3);
			affiche_texte(2, 0, "L'adversaire attaque. Vous bloquez une partie des dégâts.");
			j->pv -= (e->atk / 2);
			affiche_degats_subis(3, 'j', (e->atk / 2), 0);
		} 
		else  // l'ennemi se défend
		{
			efface_ligne_texte(2);
			efface_ligne_texte(3);
			affiche_texte(2, 0, "L'adversaire se défend aussi ! Dommage...");
			affiche_degats_subis(3, 'b', 0, 0);
		}
	}
	else // entrée invalide
	{
		efface_ligne_texte(2);
		efface_ligne_texte(3);
		affiche_texte(2, 0, "Vous vous emmêlez les pieds et tombez (entrée invalide).");
		j->pv -= 1;  // 1 point de dégât pour la peine
		affiche_degats_subis(3, 'j', 1, 0);

	}
	return;
}


/* Lance un combat du joueur contre un ennemi.
 * Renvoie true si le combat est gagné par le joueur et false sinon */
bool combat(struct joueur* j, struct ennemi* e)
{
	char entree;
	int pv_max = j->pv;				// On garde les pv du joueur pour pouvoir s'en resservir par la suite
	int pv_ennemi = e->pv;

	//
	efface_ligne_texte(0);
	efface_ligne_texte(1);
	affiche_texte(0, 0, "Un ennemi garde le couloir !");
	affiche_texte(1, 0, "Etes-vous sûr de vouloir l'affronter ? Oui [o] ou Non [n] : ");
	scanw("%c", &entree); 
	
	if (entree == 'n')  // pas de combat
	{
		efface_ligne_texte(0);
		efface_ligne_texte(1);
		affiche_texte(0, 0, "Vous vous enfuyez avant que l'ennemi vous attaque.");
		affiche_texte(1, 0, "Il ne bronche pas...");
		return false;
	}
	else if (entree == 'o')  // le combat démarre
	{
		while ((j->pv > 0) && (e->pv > 0))  // Tant qu'aucun des combattants n'a les pv à 0 ou moins
		{
			efface_ligne_texte(0);
			efface_ligne_texte(1);
			tour_de_combat(j, e);  // ils s'affrontent
		}
	}
	else  // entrée invalide
	{
		efface_zone_texte();
		affiche_texte(0, 0, "Vous restez planté devant l'ennemi (entrée invalide).");
		affiche_texte(1, 0, "Il vous lance un caillou dessus.");
		j->pv -= 1;
		affiche_degats_subis(2, 'j', 1, 0);
		return false;  // quitte le dialogue
	}

    affiche_texte(0, 0, "Le combat est terminé, et...");

	if (j->pv <= 0) // défaite
	{
		efface_ligne_texte(1);
		efface_ligne_texte(2);
		efface_ligne_texte(3);
		affiche_texte(2, 0, "Vous avez perdu...");
		j->pv = pv_max;				 // En cas de défaite on rend les pv du joueur (peut être changé pour plus de difficulté
		e->pv = pv_ennemi;			 // En cas de défaite, on remets les pv de l'ennemi a son max (sinon trop facile)

		return false;				 // Indique que le combat n'est pas gagné
	}

	/* On peut changer manuellement la difficulté du jeu en changeant combien de pv on gagne après une victoire */

	else if (e->pv <= 0)  // victoire
	{
		efface_ligne_texte(1);
		efface_ligne_texte(2);
		efface_ligne_texte(3);
		affiche_texte(2, 0, "Vous avez gagné. Votre attaque augmente !");
		j->atk += 1;					 
		
		affiche_texte(3, 0, "Vous regagnez tous vos PV, et vos PV max. augmentent !");
		j->pv  = pv_max + 5;       	      // Remet les pv du joueur au niveau d'avant le combat et rajoute 5 pv
		// plus de difficulté :
		e->pv  = pv_ennemi + 7; 		  // la vie des ennemis augmente au fur et a mesure
		e->atk = e->atk + (rand() % 2);   // Augmente de 1 ou de 0 l'attaque de l'adversaire
		
		return true;				      // Renvoie true si le combat est gagné pour pouvoir supprimer l'ennemi de la map
	}

	return false;
}
