# à changer au fur et à mesure
# que des modifs seront faites


# le jeu final
main: main.o map.o joueur.o salles.o move.o affichage.o
	gcc main.o map.o salles.o joueur.o move.o affichage.o -o main -lncurses

main.o: src/main.c src/map.h src/salles.h src/joueur.h src/move.h src/affichage.h
	gcc -c src/main.c

map.o: src/map.c src/map.h
	gcc -c src/map.c 

salles.o: src/salles.c 
	gcc -c src/salles.c

joueur.o: src/joueur.c
	gcc -c src/joueur.c

move.o: src/move.c src/map.h
	gcc -c src/move.c -lncurses

affichage.o: src/affichage.c src/map.h
	gcc -c src/affichage.c -lncurses

clean:
	rm -f *.o
	rm -f main
