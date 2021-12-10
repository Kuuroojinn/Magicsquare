#include <ncurses.h>
#include <string.h>
//#include "salles.h"


// map contient 32 lignes et 128 colonnes
const int MAP_LIN = 32;
const int MAP_COL = 128;


/* contenu de la map */
const int VIDE = 0;
const int JOUEUR_HAUT = 1;  // différentes directions du joueur
const int JOUEUR_BAS = 2;  // en fonction de joueur.dir
const int JOUEUR_GAUCHE = 3;
const int JOUEUR_DROITE = 4;
const int MUR = 5;
const int ENNEMI = 6;
const int BLOC = 7;


/* pour affiche_char_val() ;
 * NB : difficile d'utiliser ACS_QQCH ici... à voir
 * TODO : à déplacer à un meilleur endroit */
const char CHR_VIDE = '.';
const char CHR_MUR = '=';
const char CHR_JOUEUR_HAUT = '^';
const char CHR_JOUEUR_BAS = 'v';
const char CHR_JOUEUR_GAUCHE = '<';
const char CHR_JOUEUR_DROITE = '>';
const char CHR_ERREUR = '?';


// TODO : à mettre dans un autre fichier (?)

/* récupère des infos sur l'écran du joueur
 * pour configurer l'affichage de la map */
void scr_setup()
{
    int scr_lin;  // taille écran : lignes
    int scr_col;  // et colonnes

    // récupère les dimensions de l'écran
    getmaxyx(stdscr, scr_lin, scr_col);
    return;
}

/* pour pouvoir s'en servir ci-dessous et le changer facilement
 * NB : difficile d'utiliser ACS_QQCH ici... à voir
 * TODO : à déplacer à un meilleur endroit */
const char char_vide = '#';
const char char_mur = '=';
// TODO : char_mur1, mur2, etc. pour les différents murs
const char char_joueur = 'O';
const char char_erreur = '?';


/* affiche le caractère correspondant à val
 * aux coordonnées lin, col;
 * TODO : à compléter plus tard */
void affiche_char_val(int val, int lin, int col)
{
    if (val == VIDE)
    {
        mvaddch(lin, col, CHR_VIDE);
    }
    else if (val == MUR)
    {
        mvaddch(lin, col, CHR_MUR);
    }
    else if (val == JOUEUR_HAUT)
    {
        mvaddch(lin, col, CHR_JOUEUR_HAUT);
    }
    else if (val == JOUEUR_BAS)
    {
        mvaddch(lin, col, CHR_JOUEUR_BAS);
    }
    else if (val == JOUEUR_GAUCHE)
    {
        mvaddch(lin, col, CHR_JOUEUR_GAUCHE);
    }
    else if (val == JOUEUR_DROITE)
    {
        mvaddch(lin, col, CHR_JOUEUR_DROITE);
    }
    else  // erreur
    {
        mvaddch(lin, col, CHR_ERREUR);
    }
}



/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL])

{
    /* calcul du placement de la map sur l'écran : */
    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);

    // coordonnées du coin supérieur gauche de la map dans l'écran
    int start_lin, start_col;
    start_lin = (scr_lin - MAP_LIN) / 2;
    start_col = (scr_col - MAP_COL) / 2;
    

    int current_lin = start_lin;  // sera itéré pour placer le caractère
    int current_col = start_col;  // à cet emplacement sur l'écran

    /* affichage des éléments de la map */
    for (int lin = 0; lin < MAP_LIN; lin++)  // lignes
    {
        for (int col = 0; col < MAP_COL; col++)  // colonnes
        {
            int tmp = map[lin][col];  // case actuelle

            affiche_char_val(tmp, current_lin, current_col);

            current_col++;  // colonne suivante
        }

        current_lin++;  // ligne suivante
        current_col = start_col;  // revenir au début
    }
    refresh();
    return;
}



/* remplit une map de VIDE */
void initialise_map(int map[MAP_LIN][MAP_COL])

{
    for (int i = 0; i < MAP_LIN; i++)  // lignes
    {
        for (int j = 0; j < MAP_COL; j++)  // colonnes
        {
            map[i][j] = VIDE;
        }
    }
    return;
}
