# à changer au fur et à mesure
# que des modifs seront faites


# le jeu final
main: main.o map.o joueur.o salles.o
	gcc main.o map.o salles.o joueur.o -o main -lncurses

main.o: source/main.c source/map.h source/salles.h source/joueur.h
	gcc -c source/main.c

map.o: source/map.c source/map.h
	gcc -c source/map.c source/map.h

salles.o: source/salles.c 
	gcc -c source/salles.c

joueur.o: source/joueur.c
	gcc -c source/joueur.c

clean:
	rm -f *.o
	rm -f main
