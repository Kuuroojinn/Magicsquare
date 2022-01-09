/* Ce fichier stocke des fonctions de debug à utiliser si besoin, 
 * qui ne devraient pas rester dans le code principal du jeu */


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


/* pour debugger : attendre qu'on appuie sur q */
void wait_q()
{
    char c = 'a';
        while (c != 'q')
        c = getch();
    return;
}
