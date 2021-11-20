# a changer au fur et a mesure
# que des modifs seront ajoutees


# le jeu final
jeu: main.o 
	gcc -o jeu main.o salles.o 

main.o: main.c
	gcc -o main.o -c main.c -lncurses 

salles.o: salles.c salles.h
	gcc -o salles.o -c salles.c
