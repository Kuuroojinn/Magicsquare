# à changer au fur et à mesure
# que des modifs seront faites


# le jeu final
main: main.o map.o joueur.o salles.o move.o affichage.o ennemi.o
	gcc main.o map.o salles.o joueur.o move.o affichage.o ennemi.o -o main -lncurses

main.o: src/main.c src/map.h src/salles.h src/joueur.h src/move.h src/affichage.h src/ennemi.h
	gcc -c src/main.c

map.o: src/map.c src/map.h src/joueur.h src/affichage.h
	gcc -c src/map.c 

salles.o: src/salles.c src/salles.h src/map.h
	gcc -c src/salles.c

joueur.o: src/joueur.c src/joueur.h
	gcc -c src/joueur.c

move.o: src/move.c src/map.h src/ennemi.h src/affichage.h
	gcc -c src/move.c -lncurses

affichage.o: src/affichage.c src/affichage.h src/joueur.h src/ennemi.h src/map.h
	gcc -c src/affichage.c -lncurses
	
ennemi.o: src/ennemi.c src/joueur.h src/affichage.h
	gcc -c src/ennemi.c -lncurses

clean:
	rm -f *.o
	rm -f main
