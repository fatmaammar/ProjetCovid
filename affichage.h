#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "utils.h"
#define CLEAR "\033[H\033[J"

const int DEFAULT_COLOR = 0;
const int GREEN = 1;
const int ORANGE = 2;
const int RED = 3;
const int PURPLE = 4;
const int BLUE = 5;

void printf_colored(char* text, int color);
void afficher_bonhomme(Bonhomme personne);
void afficher_virus();
void afficher_case(Case cell);
void afficher_matrice(Case matrice[N][M]);
void simuler_tour(int etape, Case matrice[N][M]);

#endif
