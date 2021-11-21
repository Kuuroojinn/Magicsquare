#include <ncurses.h>
#include <string.h>
#include "salles.h"


const int VIDE = 0;
const int JOUEUR = 1;
const int MUR = 8;
const int ENNEMI = -1;
const int BLOC = 4;




// TODO : à mettre dans un autre fichier (?)

/* récupère des infos sur l'écran du joueur
 * pour configurer l'affichage de la map 
 * et pour debugger */
void scr_setup()
{
    int scr_lin;  // taille écran : lignes
    int scr_col;  // et colonnes

    // récupère les dimensions de l'écran
    getmaxyx(stdscr, scr_lin, scr_col);

    // debug
    move(scr_lin - 2, 1);
    printw("DEBUG : scr_lin = %d ; scr_col = %d", scr_lin, scr_col);
    move(scr_lin -1, 1);
    printw("DEBUG : appuyer sur q pour quitter");
    refresh();

    return;
}





/* sert au debug : affiche en bas les valeurs des variables */
void debug()
{
    // TODO : afficher en bas...
    return;
}






/* pour pouvoir s'en servir ci-dessous et le changer facilement
 * NB : difficile d'utiliser ACS_QQCH ici... à voir
 * TODO : à déplacer à un meilleur endroit */
const char char_vide = '#';
const char char_mur = '=';
// TODO : char_mur1, mur2, etc. pour les différents murs
const char char_joueur = 'o';
const char char_erreur = '?';




/* affiche la map au centre de l'écran. 
 * Dimensions : map_lin lignes, map_col colonnes.
 * Attention : la taille du terminal ne doit pas varier */

void affiche_map(int map[3][5], int map_lin, int map_col)
{

    /* calcul du placement de la map sur l'écran */

    int start_lin;   // coordonnées du coin supérieur
    int start_col;   // gauche de la map dans le terminal

    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);

    start_lin = (scr_lin - map_lin) / 2;
    start_col = (scr_col - map_col) / 2;

    // DEBUG
    char c = 'a';
    while (c != 'q')
    {
        c = getch();
        debug();
    }


    /* affichage des éléments de la map */

    for (int lin = start_lin; lin < (start_lin + scr_lin); lin++)  // lignes
    {
        for (int col = start_col; col < start_col + scr_col; col++)  // colonnes
        {
            /* gère les différents éléments de la map ;
             * rempli de placeholders pour le moment */

            int tmp = map[lin][col];  // case actuelle

            if (tmp == VIDE)
            {
                // ou ne rien mettre ?
                mvaddch(lin, col, char_vide);
            }
            else if (tmp == MUR)  // TODO : à changer pour les diff. murs
            {
                mvaddch(lin, col, char_mur);
            }
            else if (tmp == JOUEUR)
            {
                mvaddch(lin, col, char_joueur);
            }
            else  // erreur
            {
                mvaddch(lin, col, char_erreur);
            }

        }
    }
    refresh();
    return;
}

// test pour le moment
int main()
{
    clear();

    initscr();

    // noecho();  // masque l'input utilisateur

    scr_setup();

    // démonstration seulement
    int test_map1[3][5] = {
        {JOUEUR, VIDE, MUR, MUR, MUR},
        {VIDE, VIDE, VIDE, VIDE, MUR},
        {MUR, MUR, VIDE, VIDE, MUR}
    };
    
    affiche_map(test_map1, 3, 5);

    // debug pour la taille du terminal
    char c = 'a';
    while (c != 'q')
    {
        c = getch();
        scr_setup();
    }    

    endwin();
}