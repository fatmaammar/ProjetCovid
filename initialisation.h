#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "utils.h"

const float PROBA_LAMBDA = 0.2;
const float PROBA_SOIGNANT = 0.1;
const float PROBA_VIRUS = 0.05;

void set_bonhomme(int nb, Bonhomme* personne, bool soignant, int i, int j);
void initialiser_matrice(Case matrice[N][M], Bonhomme lambdas[N*M], Bonhomme soignants[N*M], int* nb_lambdas, int* nb_soignants);

#endif
