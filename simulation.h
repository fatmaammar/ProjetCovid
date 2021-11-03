#ifndef SIMULATION_H
#define SIMULATION_H

#include "utils.h"

const float PROBA_MALADE_SI_INFECTE = 0.33;
const float PROBA_DISPERSION_VIRUS = 0.25;
const float VIRULENCE = 0.1;
const float PROBA_DEPLACEMENT = 0.7;
const float PROBA_MEME_DIRECTION = 0.75;
const float PROBA_DEPLACEMENT_SI_OBSTACLE = 0.5;

void changement_gradient_malade(Case matrice[N][M], Bonhomme* personne);
void changement_gradient_mort_ou_soin(Case matrice[N][M], Bonhomme* personne);
void vers_malade(Case matrice[N][M], Bonhomme* soignant, int i, int j);
void fuir_malade(Case matrice[N][M], Bonhomme* lambda_en_fuite, int i, int j);
void deplacement(Case matrice[N][M], Bonhomme* personne, int ancien_x, int ancien_y);
void changer_case(Case matrice[N][M], Bonhomme* personne, int ancien_x, int ancien_y, int i, int j);
void jouer_tour(Case matrice[N][M], Bonhomme personnes[N*M], int index, int *nb);
void jouer_tour_lambdas(Case matrice[N][M], Bonhomme lambdas[N*M], int *nb_lambdas);
void jouer_tour_soignants(Case matrice[N][M], Bonhomme soignants[N*M], int *nb_soignants);
void diminution_temps_de_vie(Case matrice[N][M]);

#endif
