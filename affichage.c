#include "affichage.h"

void printf_colored(char* text, int color) {
	if (color == 1)
        	printf("\033[38;5;10m%s\033[0m", text);
  	else if (color == 2)
        	printf("\033[38;5;209m%s\033[0m", text);
    	else if (color == 3)
        	printf("\033[31m%s\033[0m", text);
    	else if (color == 4)
        	printf("\033[35m%s\033[0m", text);
	else if (color == 5)
        	printf("\033[34m%s\033[0m", text);
   	else
        	printf("%s", text);
}


void afficher_bonhomme(Bonhomme personne) {
	if (personne.est_malade) {
        	printf_colored("M", 3);
        }
	else if (personne.est_soignant) {
        	if (personne.est_infecte>0)
        		printf_colored("S", 2);
   		else
        		printf_colored("S", 1);
	}
    	else {
        	char* output;
        	switch (personne.direction) {
			case 0:
			case 7:
				output = "\\"; break;
			case 1:
				output = "^"; break;
			case 2:
			case 5:
				output = "/"; break;
			case 3:
				output = "<"; break;
			case 4:
				output = ">"; break;
			case 6:
				output = "v"; break;
			default:
				output = " "; break;
		}
	printf_colored(output, personne.est_infecte > 0 ? 3 : 0);
	}
}

void afficher_virus() {
	printf_colored("V", 4);
}

void afficher_case(Case cell) {
	if (cell.occupe!=NULL)
		afficher_bonhomme(*(cell.occupe));
	else if (cell.contamine_pour_x_tours>0 && cell.occupe==NULL)
		afficher_virus();
	else if (cell.occupe==NULL && cell.contamine_pour_x_tours==0 && cell.gradient!=0) {
		if (cell.gradient==2)
			printf_colored("2", 5);
        	if (cell.gradient==1)
        		printf_colored("1", 1);
        }
	else
		printf(" ");
}

void afficher_matrice(Case matrice[N][M]) {
	int i=0, j=0;
	for (i=0; i<N; i++) {
		for (j=0; j<M; j++) {
			afficher_case(matrice[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

void simuler_tour(int etape, Case matrice[N][M]) {
	//printf(CLEAR);
	printf("Etape numero %d :\n", etape);
	afficher_matrice(matrice);
	sleep(1);
}
