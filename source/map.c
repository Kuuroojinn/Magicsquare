#include <ncurses.h>
#include <string.h>
#include "salles.h"


const int VIDE = 0;
const int JOUEUR = 1;
const int MUR = 8;
const int ENNEMI = -1;
const int BLOC = 4;


// map : 32 lignes, 128 colonnes


/* pour pouvoir s'en servir ci-dessous et le changer facilement
 * NB : difficile d'utiliser ACS_QQCH ici... à voir
 * TODO : à déplacer à un meilleur endroit */
const char char_vide = '#';
const char char_mur = '=';
// TODO : char_mur1, mur2, etc. pour les différents murs
const char char_joueur = 'O';
const char char_erreur = '?';



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

/* pour debugger : attendre qu'on appuie sur q */
void wait_q()
{
    char c = 'a';
        while (c != 'q')
        c = getch();
    return;
}


/* affiche la taille de l'écran en bas */
void debug_scr_size()
{
    int scr_lin;  // taille écran : lignes
    int scr_col;  // et colonnes
    // récupère les dimensions de l'écran
    getmaxyx(stdscr, scr_lin, scr_col);
    move(scr_lin - 2, 1);
    printw("DEBUG : scr_lin = %d ; scr_col = %d", scr_lin, scr_col);
}


/* sert au debug : affiche l'input (int) en bas */
void debug_int(int input)
{
    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);
    move(scr_lin -1, 1);
    printw("DEBUG : %d", input);
    refresh();
    return;
}


/* affiche le caractère correspondant à val
 * aux coordonnées lin, col;
 * TODO : à compléter plus tard */
void affiche_char_val(int val, int lin, int col)
{
    if (val == VIDE)
    {
        mvaddch(lin, col, char_vide);
    }
    else if (val == MUR)  // TODO : à changer pour les diff. murs
    {
        mvaddch(lin, col, char_mur);
    }
    else if (val == JOUEUR)
    {
        mvaddch(lin, col, char_joueur);
    }
    else  // erreur
    {
        mvaddch(lin, col, char_erreur);
    }
}


/* affiche la map au centre de l'écran. 
 * Dimensions : map_lin lignes, map_col colonnes.
 * Attention : la taille du terminal ne doit pas varier */
void affiche_map(int map[32][128], int map_lin, int map_col)
{

    /* calcul du placement de la map sur l'écran : */
    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);

    // coordonnées du coin supérieur gauche de la map dans l'écran
    int start_lin, start_col;
    start_lin = (scr_lin - map_lin) / 2;
    start_col = (scr_col - map_col) / 2;
    

    int current_lin = start_lin;  // sera itéré pour placer le caractère
    int current_col = start_col;  // à cet emplacement sur l'écran

    /* affichage des éléments de la map */
    for (int lin = 0; lin < map_lin; lin++)  // lignes
    {
        for (int col = 0; col < map_col; col++)  // colonnes
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


/* remplit une map (dimensions : lin par col) de VIDE */
void initialise_map(int map[32][128], int lin, int col)
{
    for (int i = 0; i < lin; i++)  // lignes
    {
        for (int j = 0; j < col; j++)  // colonnes
        {
            map[i][j] = VIDE;
        }
    }
    return;
}


// test pour le moment
int main()
{
    clear();

    initscr();

    // noecho();  // masque l'input utilisateur

    // scr_setup();

    // démonstration seulement
    int test_lin = 32;
    int test_col = 128;

    int test_map1[test_lin][test_col];

    initialise_map(test_map1, test_lin, test_col);

    test_map1[1][2] = JOUEUR;
    

    affiche_map(test_map1, test_lin, test_col);

    // debug pour la taille du terminal
    char c = 'a';
    while (c != 'q')
    {
        debug_scr_size();
        c = getch();
    }    

    endwin();
}