#include <ncurses.h>
#include <string.h>
#include <assert.h>
#include "affichage.h"
#include "joueur.h"
#include "map.h"


// contient toutes les fonctions liées à l'affichage


/* caractères pour affiche_char_val() */
#define CHR_VIDE ACS_BULLET
const char CHR_MUR = ' ';
const char CHR_JOUEUR_HAUT = '^';
const char CHR_JOUEUR_BAS = 'v';
const char CHR_JOUEUR_GAUCHE = '<';
const char CHR_JOUEUR_DROITE = '>';
const char CHR_ERREUR = '?';
const char CHR_ENNEMI = '!';
#define CHR_PV ACS_DIAMOND


/* couleurs pour affiche_char_val() 
 * NB : ne pas utiliser 0, ça ne marche pas */
const int COULEUR_VIDE = 1;
const int COULEUR_MUR = 2;
const int COULEUR_JOUEUR = 3;
const int COULEUR_PV_VIDE = 4;
const int COULEUR_PV_PLEIN = 5;
const int COULEUR_ENNEMI = 6;


/* dimensions de la zone de texte */
const int TAILLE_ZONE_TXT_LIN = 4;
const int TAILLE_ZONE_TXT_COL = 128;



/* affecte les paires de couleur à leur indice */
void setup_couleur()
{
    init_pair(COULEUR_MUR, COLOR_BLACK, COLOR_WHITE);
    init_pair(COULEUR_VIDE, COLOR_YELLOW, COLOR_GREEN);
    init_pair(COULEUR_JOUEUR, COLOR_YELLOW, COLOR_RED);
    init_pair(COULEUR_PV_VIDE, COLOR_BLACK, COLOR_WHITE);
    init_pair(COULEUR_PV_PLEIN, COLOR_RED, COLOR_WHITE);
    init_pair(COULEUR_ENNEMI, COLOR_BLUE, COLOR_WHITE);
}


/* affiche le caractère correspondant à val
 * aux coordonnées lin, col */
void affiche_char_val(int val, int lin, int col)
{
    switch(val)
    {
        case VIDE:
            attron(COLOR_PAIR(COULEUR_VIDE));
            mvaddch(lin, col, CHR_VIDE);
            attroff(COLOR_PAIR(COULEUR_VIDE));
            break;

        case MUR:
            attron(COLOR_PAIR(COULEUR_MUR));
            mvaddch(lin, col, CHR_MUR);
            attroff(COLOR_PAIR(COULEUR_MUR));
            break;

        case JOUEUR_HAUT:
            attron(COLOR_PAIR(COULEUR_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_HAUT);
            attroff(COLOR_PAIR(COULEUR_JOUEUR));
            break;

        case JOUEUR_BAS:
            attron(COLOR_PAIR(COULEUR_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_BAS);
            attroff(COLOR_PAIR(COULEUR_JOUEUR));
            break;

        case JOUEUR_GAUCHE:
            attron(COLOR_PAIR(COULEUR_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_GAUCHE);
            attroff(COLOR_PAIR(COULEUR_JOUEUR));
            break;

        case JOUEUR_DROITE:
            attron(COLOR_PAIR(COULEUR_JOUEUR));
            mvaddch(lin, col, CHR_JOUEUR_DROITE);
            attroff(COLOR_PAIR(COULEUR_JOUEUR));
            break;

		case ENNEMI:
			attron(COLOR_PAIR(COULEUR_ENNEMI));
			mvaddch(lin, col, CHR_ENNEMI);
			attroff(COLOR_PAIR(COULEUR_ENNEMI));
			break;

        default:  // erreur
            mvaddch(lin, col, CHR_ERREUR);
            break; 
    }
}



/* affiche la map au centre de l'écran, moins un décalage pour la zone de texte 
 * dimensions écran : (scr_lin x scr_col) */
void affiche_map(int map[MAP_LIN][MAP_COL], int scr_lin, int scr_col)
{
    assert(scr_lin > 0);  // la taille de l'écran est strictement positive
    assert(scr_col > 0);

    // coordonnées du coin supérieur gauche de la map dans l'écran
    int start_lin, start_col;
    // centre du décalage entre la map et l'écran :
    start_lin = (scr_lin - MAP_LIN) / 2 - TAILLE_ZONE_TXT_LIN;  // - TAILLE_ZONE_TXT_LIN : décalage
    start_col = (scr_col - MAP_COL) / 2;
    
    // l'affichage doit bien se faire dans l'écran
    assert(start_lin >= 0);
    assert(start_lin + MAP_LIN <= scr_lin);
    assert(scr_col >= 0);
    assert(start_col + MAP_COL <= scr_col);


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
        current_col = start_col;  // revenir à la pemière colonne
    }
    refresh();
    return;
}



/* affiche une bordure autour de la map et une autour de la zone de texte,
 * dans un écran de dimensions scr_lin lignes par scr_col colonnes */
void affiche_bordures(int scr_lin, int scr_col)
{
    assert(scr_lin > 0);  // la taille de l'écran est strictement positive
    assert(scr_col > 0);

	/* calcul du placement de la bordure sur l'écran */
    int map_start_lin, txt_start_lin, start_col;
    // ligne du coin supérieur gauche de la map :
    map_start_lin = (scr_lin - MAP_LIN) / 2 - TAILLE_ZONE_TXT_LIN;
    // ligne du coin sup. gauche de la zone de texte :
    txt_start_lin = (scr_lin + MAP_LIN) / 2 - TAILLE_ZONE_TXT_LIN;
    // colonne du coin sup. gauche des deux zones ci-dessus :
    start_col = (scr_col - MAP_COL) / 2;

    int taille_bord_lin, taille_bord_col;  // dimensions de la bordure

    int start_lin;  // ligne de départ
    for (int iter = 0; iter < 2; iter++)  // itération pour chaque bordure
    {
        if (iter == 0)  // bordure de la map
        {
            start_lin = map_start_lin;
            taille_bord_lin = MAP_LIN;
            taille_bord_col = MAP_COL;
        }
        else  // bordure de la zone de texte
        {
            start_lin = txt_start_lin + 2;  // + 2 car il y a les deux lignes
            taille_bord_lin = TAILLE_ZONE_TXT_LIN;
            taille_bord_col = TAILLE_ZONE_TXT_COL;
        }

        /* lignes : */
        // haut
        move(start_lin - 1, start_col);
        hline(ACS_HLINE, taille_bord_col);  // trace la ligne   

        // bas
        move(start_lin + taille_bord_lin, start_col);
        hline(ACS_HLINE, taille_bord_col);  

        //gauche
        move(start_lin, start_col - 1);
        vline(ACS_VLINE, taille_bord_lin);  

        // droite
        move(start_lin, start_col + taille_bord_col);
        vline(ACS_VLINE, taille_bord_lin);  

        // coins
        mvaddch(start_lin - 1, start_col - 1, ACS_ULCORNER);
        mvaddch(start_lin - 1, start_col + taille_bord_col, ACS_URCORNER);
        mvaddch(start_lin + taille_bord_lin, start_col - 1, ACS_LLCORNER);
        mvaddch(start_lin + taille_bord_lin, start_col + taille_bord_col, ACS_LRCORNER);
    }

    refresh();
    return;
}



/* affiche une string dans la zone de texte, à la ligne indiquée. */
void affiche_texte(int ligne, char* string)
{
    int scr_lin, scr_col;
    getmaxyx(stdscr, scr_lin, scr_col);

    assert(scr_lin > 0);  // taille de l'écran strictement positive
    assert(scr_col > 0);
    assert(ligne >= 0);                   // la ligne doit exister
    assert(ligne < TAILLE_ZONE_TXT_LIN);  // dans la zone de texte

    /* coordonnées du début (haut, gauche) la zone de texte :
     * - TAILLE_ZONE_TXT_LIN : décalage du texte
     * + 2 : pour les bordures */
    int zone_txt_lin = (scr_lin + MAP_LIN) / 2 - TAILLE_ZONE_TXT_LIN + 2 + ligne;  
    int zone_txt_col = (scr_col - MAP_COL) / 2;

    mvprintw(zone_txt_lin, zone_txt_col, string);
    return;
}
