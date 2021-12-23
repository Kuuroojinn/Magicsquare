#include <ncurses.h>
#include <string.h>
#include <assert.h>
#include "map.h"
#include "joueur.h"

// map contient 32 lignes et 128 colonnes
const int MAP_LIN = 32;
const int MAP_COL = 128;


// AFFICHAGE :

/* caractères pour affiche_char_val() */
const char CHR_VIDE = '.';
const char CHR_MUR = ' ';
const char CHR_JOUEUR_HAUT = '^';
const char CHR_JOUEUR_BAS = 'v';
const char CHR_JOUEUR_GAUCHE = '<';
const char CHR_JOUEUR_DROITE = '>';
const char CHR_ERREUR = '?';

/* couleurs pour affiche_char_val() 
 * NB : ne pas utiliser 0, ça ne marche pas */
const int COUL_VIDE = 1;
const int COUL_MUR = 2;
const int COUL_JOUEUR = 3;


/* affecte les paires de couleur à leur indice */
void setup_couleur()
{
    init_pair(COUL_MUR, COLOR_BLACK, COLOR_WHITE);
    init_pair(COUL_VIDE, COLOR_YELLOW, COLOR_GREEN);
    init_pair(COUL_JOUEUR, COLOR_YELLOW, COLOR_RED);
}


/* remplit la map de VIDE */
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


/* ajoute dans la map l'élément correspondant à la direction du joueur */
void pivote_joueur_vers_map(struct joueur j, int map[MAP_LIN][MAP_COL])
{
    assert(j.dir == HAUT || j.dir == BAS || j.dir == GAUCHE || j.dir == DROITE);

    if (j.dir == HAUT)
    {
        map[j.pos_lin][j.pos_col] = JOUEUR_HAUT;
    }
    else if (j.dir == BAS)
    {
        map[j.pos_lin][j.pos_col] = JOUEUR_BAS;
    }
    else if (j.dir == GAUCHE)
    {
        map[j.pos_lin][j.pos_col] = JOUEUR_GAUCHE;
    }
    else  // j.dir == DROITE
    {
        map[j.pos_lin][j.pos_col] = JOUEUR_DROITE;
    }
    return;
}


/* vérifie que le joueur est bien dans la map (assertion) */
void assert_joueur_dans_map(struct joueur j, int map[MAP_LIN][MAP_COL])
{
    assert(j.pos_lin >= 0);
    // la dernière ligne n'est pas incluse dans la map
    assert(j.pos_lin <= MAP_LIN - 1);
    assert(j.pos_col >= 0);
    // la dernière colonne n'est pas incluse dans la map
    assert(j.pos_col <= MAP_COL - 1);
    return;
}


/* affiche le caractère correspondant à val
 * aux coordonnées lin, col */
void affiche_char_val(int val, int lin, int col)
{
    switch(val)
    {
        case VIDE:
            attron(COLOR_PAIR(COUL_VIDE));
            mvaddch(lin, col, CHR_VIDE);
            attroff(COLOR_PAIR(COUL_VIDE));
            break;

        case MUR:
            attron(COLOR_PAIR(COUL_MUR));
            mvaddch(lin, col, CHR_MUR);
            attroff(COLOR_PAIR(COUL_MUR));
            break;

        case JOUEUR_HAUT:
            attron(COLOR_PAIR(COUL_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_HAUT);
            attroff(COLOR_PAIR(COUL_JOUEUR));
            break;

        case JOUEUR_BAS:
            attron(COLOR_PAIR(COUL_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_BAS);
            attroff(COLOR_PAIR(COUL_JOUEUR));
            break;

        case JOUEUR_GAUCHE:
            attron(COLOR_PAIR(COUL_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_GAUCHE);
            attroff(COLOR_PAIR(COUL_JOUEUR));
            break;

        case JOUEUR_DROITE:
            attron(COLOR_PAIR(COUL_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_DROITE);
            attroff(COLOR_PAIR(COUL_JOUEUR));
            break;

        default:  // erreur
            mvaddch(lin, col, CHR_ERREUR);
            break; 
    }
}


/* affiche la map au centre de l'écran. */
void affiche_map(int map[MAP_LIN][MAP_COL])
{
    // calcul du placement de la map sur l'écran :
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


/* affiche une bordure autour de la map */
void affiche_bordure()
{
	 /* calcul du placement de la map sur l'écran : */
    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);

    // coordonnées du coin supérieur gauche de la map dans l'écran
    int start_lin, start_col;
    start_lin = (scr_lin - MAP_LIN) / 2;
    start_col = (scr_col - MAP_COL) / 2;
    
    
    // haut
    move(start_lin - 1, start_col);
    hline(ACS_HLINE, MAP_COL);  // trace la ligne

    // bas
    move(start_lin + MAP_LIN, start_col);
    hline(ACS_HLINE, MAP_COL);

    //gauche
    move(start_lin, start_col - 1);
    vline(ACS_VLINE, MAP_LIN);

    // droite
    move(start_lin, start_col + MAP_COL);
    vline(ACS_VLINE, MAP_LIN);

    // coins
    mvaddch(start_lin - 1, start_col - 1, ACS_ULCORNER);
    mvaddch(start_lin - 1, start_col + MAP_COL, ACS_URCORNER);
    mvaddch(start_lin + MAP_LIN, start_col - 1, ACS_LLCORNER);
    mvaddch(start_lin + MAP_LIN, start_col + MAP_COL, ACS_LRCORNER);
    

    refresh();
    return;
}


