miniGame: main.c miniGame.h
	gcc -ansi -Wall -o miniGame main.c

clean: miniGame move.txt
	rm miniGame move.txt

