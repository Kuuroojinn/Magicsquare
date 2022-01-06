#include <ncurses.h>
#include <assert.h>
#include "map.h"
#include "joueur.h"
#include "affichage.h"


// dimensions d'une map
const int MAP_LIN = 32;
const int MAP_COL = 128;


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