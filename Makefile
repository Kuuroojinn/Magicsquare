# à changer au fur et à mesure
# que des modifs seront faites


# le jeu final
main: main.o map.o joueur.o
	gcc main.o map.o joueur.o -o main -lncurses

main.o: source/main.c source/joueur.h source/map.h
	gcc -c source/main.c

map.o: source/map.c
	gcc -c source/map.c

joueur.o: source/joueur.c
	gcc -c source/joueur.c

# pas utile pour le moment
#salles.o: salles.c 
#	gcc -c salles.c

clean:
	rm -f *.o
	rm -f main
