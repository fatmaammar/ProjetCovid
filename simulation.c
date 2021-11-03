#include "simulation.h"

void changement_gradient_malade(Case matrice[N][M], Bonhomme* personne) {
	for (int i=(personne->position.x)-2; i<=(personne->position.x)+2; i++) {
		for (int j=(personne->position.y)-2; j<=(personne->position.y)+2;j++) {
			if (i >= 0 && j >= 0 && i < N && j < M
			&& matrice[i][j].gradient!=2)
				matrice[i][j].gradient=1;
		}
	}
	for (int i=(personne->position.x)-1; i<=(personne->position.x)+1; i++) {
		for (int j=(personne->position.y)-1; j<=(personne->position.y)+1;j++) {
			if (i >= 0 && j >= 0 && i < N && j < M)
				matrice[i][j].gradient=2;
		}
	}
}

void changement_gradient_mort_ou_soin(Case matrice[N][M], Bonhomme* personne) {
	for (int i=(personne->position.x)-2; i<=(personne->position.x)+2; i++) {
		for (int j=(personne->position.y)-2; j<=(personne->position.y)+2; j++) {
			if (i >= 0 && j >= 0 && i < N && j < M)
				matrice[i][j].gradient=0;
		}
	}
}

void vers_malade(Case matrice[N][M], Bonhomme* soignant, int i, int j) {
	int add_i, add_j;
	bool moved=false;
	for (add_i=-2; add_i<=2; add_i++) {
		for (add_j=-2; add_j<=2; add_j++) {
			if (i+add_i >= 0 && j+add_j >= 0 && i+add_i < N && j+add_j < M) {
				if ((matrice[i + add_i][j + add_j].occupe) != NULL &&
				(matrice[i + add_i][j + add_j].occupe)->est_malade) {
					changer_case(matrice, soignant, i, j, i + (add_i*0.5), j + (add_j*0.5));
					moved = true;
					break;
				}
			}
		}
		if (moved)
			break;
	}
}

void soigner_malade(Case matrice[N][M], Bonhomme* soignant, int i, int j) {
	int add_i, add_j;
	bool soin=false;
	for (add_i=-2; add_i<=2; add_i++) {
		for (add_j=-2; add_j<=2; add_j++) {
			if (i+add_i >= 0 && j+add_j >= 0 && i+add_i < N && j+add_j < M) {
				if ((matrice[i + add_i][j + add_j].occupe) != NULL &&
				(matrice[i + add_i][j + add_j].occupe)->est_malade) {
					soignant->tour_de_soin++;
					(matrice[i + add_i][j + add_j].occupe)->tour_de_soin++;
					if (soignant->tour_de_soin==1) {
						changement_gradient_mort_ou_soin(matrice, (&matrice[i + add_i][j + add_j])->occupe);
					}
					if ((matrice[i + add_i][j + add_j].occupe)->tour_de_soin==2) {
						soignant->tour_de_soin=0;
						(matrice[i + add_i][j + add_j].occupe)->tour_de_soin=0;
						(matrice[i + add_i][j + add_j].occupe)->est_malade=false;
						(matrice[i + add_i][j + add_j].occupe)->est_infecte=false;
					}	
					soin = true;
					break;
				}
			}
		}
		if (soin)
			break;
	}
}

void fuir_malade(Case matrice[N][M], Bonhomme* lambda_en_fuite, int i, int j) {
	int add_i, add_j;
	bool moved=false;
	for (add_i=-2; add_i<=2; add_i++) {
		for (add_j=-2; add_j<=2; add_j++) {
			if (i+add_i >= 0 && j+add_j >= 0 && i+add_i < N && j+add_j < M) {
				if ((matrice[i + add_i][j + add_j].occupe) != NULL &&
				(matrice[i + add_i][j + add_j].occupe)->est_malade) {
					changer_case(matrice, lambda_en_fuite, i, j,
					i + (add_i * -0.5), j + (add_j * -0.5));
					moved = true;
					break;
				}
			}
		}
		if (moved)
			break;
	}
}	

void deplacement(Case matrice[N][M], Bonhomme* personne, int ancien_x, int ancien_y) {
	switch (personne->direction) {
		case 0:
			changer_case(matrice, personne, ancien_x, ancien_y, -1, -1); break;
		case 7:
			changer_case(matrice, personne, ancien_x, ancien_y, 1, 1); break;
		case 1:
			changer_case(matrice, personne, ancien_x, ancien_y, 0, -1); break;
		case 2:
			changer_case(matrice, personne, ancien_x, ancien_y, 1, -1); break;
		case 5:
			changer_case(matrice, personne, ancien_x, ancien_y, -1, 1); break;
		case 3:
			changer_case(matrice, personne, ancien_x, ancien_y, -1, 0); break;
		case 4:
			changer_case(matrice, personne, ancien_x, ancien_y, 1, 0); break;
		case 6:
			changer_case(matrice, personne, ancien_x, ancien_y, 0, 1); break;
		default:
			changer_case(matrice, personne, ancien_x, ancien_y, 0, 0); break;
	}
}

void changer_case(Case matrice[N][M], Bonhomme* personne, int ancien_x, int ancien_y, int i, int j) {
	int x=personne->position.x, y=personne->position.y;
	if (x + i >= N || y + j >= M || x + i < 0 || y + j < 0 || matrice[x+i][y+j].occupe!=NULL) {
		double proba = (rand() % 100);
		proba = proba / 100;
		if (proba >= PROBA_DEPLACEMENT_SI_OBSTACLE) {
			Case nouvelleCase = matrice[x - i][y - j];
			if (nouvelleCase.occupe == NULL) {
				personne->position.x -= i;
				personne->position.y -= j;
			}
		}
	}
	else {
		personne->position.x += i;
		personne->position.y += j;
	}
}

void jouer_tour(Case matrice[N][M], Bonhomme personnes[N*M], int index, int *nb) {
	Bonhomme* personne = &personnes[index];
	int i = personne->position.x;
	int j = personne->position.y;
	Case* current_cell = &matrice[i][j];
	double proba=0;
	bool mort;
	
	// Si bonhomme malade
	if (personne->est_malade) {
		if (personne->tour_de_soin==0)
			changement_gradient_malade(matrice, personne);
		proba=rand()%100;
		proba=proba/100;
		// Mort du bonhomme
		if (proba < VIRULENCE){
			current_cell->occupe = NULL;
			current_cell->contamine_pour_x_tours=4;
			changement_gradient_mort_ou_soin(matrice, personne);
			// On l'enlève du tableau
			personnes[index] = personnes[(*nb)-1];
			(*nb)--;
			mort=true;
		}
		else
			mort=false;
	}

	// Si bonhomme pas malade
	if (!personne->est_malade && !mort) {
		// Contamination de la case
		if (personne->est_infecte > 0) {
			proba=rand()%100;
			proba=proba/100;
			if (proba < PROBA_DISPERSION_VIRUS)
				current_cell->contamine_pour_x_tours=4;
		}
		
		// Déplacement si pas de malade à proximité
		if (current_cell->gradient==0 && personne->tour_de_soin==0) {
			proba=rand()%100;
			proba=proba/100;
			if (proba < PROBA_DEPLACEMENT) {
				proba=rand()%100;
				proba=proba/100;
				if (proba > PROBA_MEME_DIRECTION)
					personne->direction=rand()%8;
				deplacement(matrice, personne, i, j);
				current_cell->occupe=NULL;
				current_cell=&matrice[personne->position.x][personne->position.y];
        			current_cell->occupe=personne;
        			}
		}
		// Déplacement si malade à proximité
		else if (!personne->est_soignant && current_cell->gradient!=0) {
			fuir_malade(matrice, personne, i, j);
			current_cell = &matrice[personne->position.x][personne->position.y];
			current_cell->occupe = personne;
		}
		else if (personne->est_soignant && current_cell->gradient==1) {
			vers_malade(matrice, personne, i, j);
			current_cell = &matrice[personne->position.x][personne->position.y];
			current_cell->occupe = personne;
		}
		else if ((personne->est_soignant && current_cell->gradient==2)
		|| (current_cell->gradient==0 && personne->tour_de_soin==1)) {
			soigner_malade(matrice, personne, i, j);
		}
		
		
		if (personne->est_infecte > 0)
			personne->est_infecte--;
		
		// Contamination si la case est infectée et :
		// personne=soignant sur la même case qu'au tour d'avant ou
		// personne=lambda
		if (current_cell->contamine_pour_x_tours > 0 && ((!personne->est_soignant)
		|| (personne->est_soignant && current_cell==&matrice[i][j]))) {
			personne->est_infecte = 7;
			proba=rand()%100;
			proba=proba/100;
			if (proba < PROBA_MALADE_SI_INFECTE) {
				personne->est_malade = true;
				changement_gradient_malade(matrice, personne);
			}
		}
	}
}

void jouer_tour_lambdas(Case matrice[N][M], Bonhomme lambdas[N*M], int *nb_lambdas) {
	for (int i = 0; i < (*nb_lambdas); i++)
		jouer_tour(matrice, lambdas, i, nb_lambdas);
}

void jouer_tour_soignants(Case matrice[N][M], Bonhomme soignants[N*M], int *nb_soignants) {
	for (int i = 0; i < (*nb_soignants); i++)
		jouer_tour(matrice, soignants, i, nb_soignants);
}

void diminution_temps_de_vie(Case matrice[N][M]) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			if (matrice[i][j].contamine_pour_x_tours>1)
				matrice[i][j].contamine_pour_x_tours--;
		}
	}
}
