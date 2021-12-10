#include "image.h"
#include <string.h>
#define n 20
typedef struct LMat {
	char* nom;
	Matrice mom;
	struct LMat* next;
}LMat;


LMat* creer(char* nomf, Matrice mat) {
	LMat* maille = malloc(sizeof(LMat));
	maille->nom = malloc((strlen(nomf)+1)*sizeof(char));
	strcpy(maille->nom, nomf);
	maille->mom = creerMatrice(mat.num, mat.N);
	maille->mom = mat;
	maille->next = NULL;
	return maille;
}
void chainage(LMat* root, LMat* maille) {
	LMat* current = root;
	while(current->next != NULL) { current = current->next;
	}
	current->next = maille;
}

void freeliste(LMat* root) {
	LMat* current = root, *temp = root->next; 
	while(temp->next != NULL) {
		free(current->nom);
		supprMatrice(&(current->mom));
		free(current);
		current = temp;
		temp = temp->next;
	}
	free(temp->nom);
	supprMatrice(&(temp->mom));
	free(temp);
}

Matrice lectureMatrice(char * nomfichier){
	int dim;
	FILE* f = fopen(nomfichier, "r");				// Ouverture du fichier
	if(f == NULL) {						// Vérification que le fichier à été ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier ");
		printf("\n nom : %s", nomfichier);
		exit(1);
	}

	fscanf ( f , "%d\n", &dim );
	Matrice mat= creerMatrice(1,dim);
	for(int i=0; i<=dim; i++){
        for(int j=0;j<=dim-i; j++){
            fscanf(f,"%lf",&(mat.tab[i][j]));
        }
	}
	fclose(f);
	return mat;
}

LMat* lectureBD(char* fname) {
	FILE* f = fopen(fname,"r");
	char* nom = malloc(30*sizeof(char));
	char* mom = malloc(30*sizeof(char));
	char PWD[200] = "BD/";
	fscanf(f,"%s\t", nom);
	fscanf(f,"%s\n", mom);
	Matrice leg = lectureMatrice(strcat(PWD,mom));
	LMat* root = creer(nom, leg);
	while(fscanf(f,"%s\t", nom) != EOF){
		fscanf(f,"%s\n", mom);
		char PWD[20] = "BD/";
		strcat(PWD,mom);
		Matrice leg = lectureMatrice(PWD);
		LMat* maille = creer(nom, leg);
		chainage(root, maille);
	}
	fclose(f);
	free(nom);
	free(mom);
	return root;
}

void EcritureBD(char* fname, LMat* root) {
	char PWD[20] = "BD/";
	strcat(PWD, fname);
	FILE* f = fopen(PWD, "w");
	LMat* current = root;
	char nommat[30];
	int i = 1;
	while(current->next != NULL) {
		sprintf(nommat, "BD/Legendre%d.txt", i);
		fprintf(f, "%s\t%s\n", current->nom, nommat);
		fopen(nommat, "w");
		ecritureMatrice(nommat, current->mom);
		i++;
		current = current->next;
	}
	sprintf(nommat, "BD/Legendre%d.txt", i);
	fprintf(f, "%s\t%s\n", current->nom, nommat);
	fopen(nommat, "w");
	ecritureMatrice(nommat, current->mom);

}

LMat* CreerBD() {
	char* PWD = calloc(20, sizeof(char));
	strcpy(PWD, "BD/");
	int flag = 1;
	int ordre = 0;
	printf("Nom de la base de donnée: ");
	char* nom = calloc(20, sizeof(char));
	char* nommat = calloc(40, sizeof(char));
	scanf("%s", nom);
	Matrice mat = creerMatrice(0, 1);
	LMat* root = creer(nom, mat);
	supprMatrice(&mat);
	strcat(PWD, nom);
	FILE* f = fopen(PWD, "w");
	while(flag > 0) {
		while(1) {
			printf("Veuillez donner le nom de l'image avec son extension :");
			scanf("%s", nom);
			strcpy(PWD,"BD/");
			strcat(PWD, nom);
			FILE* t = fopen(PWD, "r");
			if(t == NULL) {
				printf("L'image donnée n'existe pas, veuillez donner une image valide\n");
			}
			else {
				fclose(t);
				break;
			}
			fclose(t);

		}
		BmpImg pic = readBmpImage(PWD);
		printf("Veuillez donner l'ordre maximal à lequel vous voulez calculer vos moments géomètriques:");
		scanf("%d", &ordre);
		Matrice mat = mom_legendre(&pic, ordre);
		LMat* maille = creer(nom, mat);
		chainage(root, maille);
		fprintf(f,"%s\t",nom);
		printf("Veuillez donner le nom que vous souhaitez donner à votre matrice (ex: MomentAvion): ");
		scanf("%s", nom);
		sprintf(nommat, "%s.txt",nom);
		fprintf(f, "%s\n", nommat);
		sprintf(nommat, "BD/%s.txt",nom);
		ecritureMatrice(nommat, mat);
		printf("Avez vous terminé ?[o]/[n] ");
		char c;
		while(scanf(" %c", &c)){
		if (c == 'o') {
			flag = 0;
			break;
		}
		else if (c == 'n') {
			break;
		}
		else  {
			printf("Veuillez donner une réponse valide.\n");
		}
		}
		freeBmpImg(&pic);
	}
	
	fclose(f);
	LMat* temp = root->next;
	free(root->nom);
	free(root);
	free(nom);
	free(PWD);
	free(nommat);
	return temp;
}


void afficherliste(LMat* root) {
	LMat* current = root;
	while(current->next != NULL) {
		printf("Pointeur: %p\nNom: %s\n Pointeur next: %p\n", current, current->nom,  current->next);
		current = current->next;
	}
printf("Pointeur: %p\nNom: %s\n Pointeur next: %p\n", current, current->nom, current->next);

}

LMat* comparaison(LMat* root, Matrice moment, int ordre) {
	LMat* current = root;
	double res = distance_euclidienne(root->mom, moment, ordre), res2 = 0;
	LMat* forme = root;
	while(current->next != NULL) {
		res2 = distance_euclidienne(current->mom, moment, ordre);
		if (res2 < res) {
			forme = current;
		}
		current= current->next;
	}

	res2 = distance_euclidienne(current->mom, moment, ordre);
		if (res2 < res) {
			forme = current;
		}
	return forme;
}
int main(){
	while(1) {
	printf("------------------------Reconnaissance Des Fomes-------------------\n");
	printf("Voulez vous créer une nouvelle base de données?[o]/[n] ");
	char c;
	char nomImage[100];
	LMat* root = NULL;;
	while(scanf(" %c", &c)) {
		if (c == 'o') {
			while(root == NULL)
				root = CreerBD();
			break;
		}
		else if (c == 'n') {
			root = lectureBD("BD/BD.txt");
			break;
		}
		else  {
			printf("Veuillez donner une réponse valide.\n");
			printf("Voulez vous créer une nouvelle base de données?[o]/[n] ");
		}
	}
	while(1) {
		printf("veuillez donner le nom de l'image à comparer :");
		scanf(" %s", nomImage); 
		FILE* t = fopen(nomImage, "r");
		if(t == NULL) {
			printf("L'image donnée n'existe pas, veuillez donner une image valide\n");
		}
		else {
			fclose(t);
			break;
		}
		fclose(t);

	}
	BmpImg pic = readBmpImage(nomImage);

	int ordre;
	while(1) {
		printf("Ordre de comparaison: (<45) "); scanf(" %d", &ordre);
		if(ordre > 45) {
			printf("Ordre invalide\n");
		}
		else {
			break;
		}
	}
	Matrice moment = mom_legendre(&pic, ordre); 
	LMat* res = comparaison(root, moment, ordre);
	printf("L'image la plus proche est : %s\n", res->nom);
	
	//afficherliste(root);
	freeliste(root);
	supprMatrice(&moment);
	/**/
	freeBmpImg(&pic);
	}
	return 0;
}
	
