all:  main clean

simulation.o: simulation.c
	gcc -c -Wall simulation.c

affichage.o: affichage.c
	gcc -c -Wall affichage.c

initialisation.o: initialisation.c
	gcc -c -Wall initialisation.c

utils.o: utils.c
	gcc -c -Wall utils.c

main.o: main.c 
	gcc -c -Wall main.c

projetC: main.o utils.o initialisation.o affichage.o simulation.o
	gcc main.o utils.o initialisation.o affichage.o simulation.o -o projetC 
    
clean:
	rm *o
	./main
	
mrproper:
	rm *o projetC

