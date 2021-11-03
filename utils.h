#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

const int N=80;
const int M=30;

// définition des structures

typedef struct Coordonnees {
	int x;
	int y;
} Coordonnees;

typedef struct Bonhomme {
	bool est_soignant;
	bool est_malade;
	int tour_de_soin;
	int est_infecte;
	Coordonnees position;
	int direction;
} Bonhomme;

typedef struct Case {
	int contamine_pour_x_tours;
	Bonhomme* occupe;
	int gradient;
} Case;

#endif
