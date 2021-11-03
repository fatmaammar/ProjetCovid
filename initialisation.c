#include "initialisation.h"

void set_bonhomme(int nb, Bonhomme* personne, bool soignant, int i, int j) {
	personne->est_soignant=soignant;
	personne->est_malade=false;
	personne->est_infecte=0;
	personne->direction=rand()%8;
	personne->position.y=j;
	personne->position.x=i;
	personne->tour_de_soin=0;
}

// on remplit tous les tableaux
void initialiser_matrice(Case matrice[N][M], Bonhomme lambdas[N*M], Bonhomme soignants[N*M], int* nb_lambdas, int* nb_soignants) {
	srand(time(NULL));
	int i=0, j=0;
	double proba=0;
	for (i=0; i<N; i++) {
		for (j=0; j<M; j++) {
			proba=rand()%100;
			proba=proba/100;
			// apparition d’un virus
			if (proba < PROBA_VIRUS) {
				matrice[i][j].contamine_pour_x_tours=4;
				matrice[i][j].occupe=NULL;
			}
			// apparition d’un soignant
			else if (proba < (PROBA_VIRUS + PROBA_SOIGNANT) && proba >= PROBA_VIRUS) {
				set_bonhomme(*nb_soignants, &soignants[*nb_soignants], true, i, j);				
				matrice[i][j].contamine_pour_x_tours=0;
				matrice[i][j].occupe=&soignants[*nb_soignants];
				(*nb_soignants)++;
			}
			// apparition d’un lambda
			else if (proba < (PROBA_VIRUS + PROBA_SOIGNANT + PROBA_LAMBDA) && proba >= (PROBA_VIRUS + PROBA_SOIGNANT)) {
				set_bonhomme(*nb_lambdas, &lambdas[*nb_lambdas], false, i, j);
				matrice[i][j].contamine_pour_x_tours=0;
				matrice[i][j].occupe=&lambdas[*nb_lambdas];
				(*nb_lambdas)++;
			}
			// ni virus, ni lambda, ni soignant
			else {
				matrice[i][j].contamine_pour_x_tours=0;
				matrice[i][j].occupe=NULL;
			}
			matrice[i][j].gradient=0;
		}
	}
}


