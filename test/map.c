#include <ncurses.h>
#include <string.h>
//#include "salles.h"


const int VIDE = 0;
const int JOUEUR = 1;
const int MUR = 8;
const int ENNEMI = -1;
const int BLOC = 4;




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

/* pour debugger : attendre */
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
    printw("DEBUG : scr_lin = %d ; scr_col = %d\n", scr_lin, scr_col);
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
void affiche_map(int map[32][64], int map_lin, int map_col)
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
void initialise_map(int map[32][64], int lin, int col)
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
    keypad(stdscr, TRUE); //J'ai trouvé ça sur un forum et grâce à ça, on peut utliser les touches directionnelles

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
    int c = -1;  //c doit être sous la forme d'un int pour être comparé aux touches directionnelles (on peut le laisser comme ça pour la map, ça dérange pas
    while (c != KEY_UP) //Marche aussi avec KEY_DOWN, KEY_LEFT, KEY_RIGHT ou les touches sous la forme 'q' (elles sont comparées en tant que int du coup c'est bon)
    {
        //debug_scr_size(); //Je l'ai caché vu que c'était pas utile pour tester la fonction
        c = getch();
        printw("%d",c); //affiche la touche préssée sous la forme d'un int 
    }    //Ici ferme la map dès qu'on presse la touche fléche du haut
    //On va donc surement réutliiser cette partie du code pour le déplacement du personnage

    endwin();
}
