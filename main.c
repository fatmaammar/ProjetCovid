#include "utils.c"
#include "initialisation.c"
#include "affichage.c"
#include "simulation.c"

int main(int argc, char const *argv[]) {
	Case matrice[N][M];
	Bonhomme lambdas[N*M];
	Bonhomme soignants[N*M];
	int nb_lambdas, nb_soignants;
	nb_lambdas=0;
	nb_soignants=0;
	initialiser_matrice(matrice, lambdas, soignants, &nb_lambdas, &nb_soignants);
	afficher_matrice(matrice);
	int tours_restants;
	int etape = 0;
	printf("Combien de tours de simulation souhaitez-vous jouer?\n");
	scanf("%d", &tours_restants);
	while (tours_restants!=0) {
		jouer_tour_lambdas(matrice, lambdas, &nb_lambdas);
		jouer_tour_soignants(matrice, soignants, &nb_soignants);
		diminution_temps_de_vie(matrice);
		simuler_tour(++etape, matrice);
		tours_restants--;
	}
	return 0;
}
