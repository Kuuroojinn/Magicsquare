# a changer au fur et a mesure
# que des modifs seront ajoutees


# le jeu final
jeu: main.o map.o salles.o
	gcc -o jeu main.o map.o salles.o 

main.o: main.c
	gcc -o main.o -c main.c -lncurses

map.o: map.c
	gcc -o map.o -c map.c -lncurses

salles.o: salles.c salles.h
	gcc -o salles.o -c salles.c

clean:
	rm -f *.o
	rm -f jeu
