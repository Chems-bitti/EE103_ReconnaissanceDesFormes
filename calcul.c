#include "calcul.h"


double distance_euclidienne(Matrice mat1, Matrice mat2){

    int p,q;
    double res= 0;

    if (mat1.N != mat2.N){
        printf("ERREUR : Les matrices ne sont pas de meme ordre\n");
        return 0;
    }else{
        for(p = 0 ; p < mat1.N; p++){
            for(q = 0 ; q < mat1.N - p;q++){
                res += pow(mat1.tab[p][q]-mat2.tab[p][q],2);
            }
        }
    }
    return sqrt(res);
}


double base_legendre(int x, int n){
    double res=0;
    Matrice an = creerMatrice(0,n);

    an.tab[0][0]=1;
    if(n>0){
        an.tab[1][0]=0;
        an.tab[1][1]=1;
    }

    for(int i=2; i<=n; i++){    //Détermination de tous les an jusqu'à l'ordre souhaité
        for(int j=0; j<=i; j++){
            if(j==0){
                an.tab[i][j]=-(i-1)*(an.tab[i-2][j])/i;
            }
            else if(j==i){
                an.tab[i][j]=(2*(i-1)+1)*(an.tab[i-1][i-1])/i;
            }
            else{
                an.tab[i][j]=((2*(i-1)+1)*(an.tab[i-1][j-1])-(an.tab[i-2][j]))/i;
            }
        }
    }

    for(int i=0; i<=n; i++){
        res+=(an.tab[n][i])*pow(x,i);
    }
    supprMatrice(&an);

    return res;
}

Matrice momcentre(BmpImg* pic, int n) {
	
	Matrice eta = creerMatrice(1,n); 	// allocation de la matrice
	Matrice mat = mom(pic, n);		// calcul des moments géometrique
	
	double omega = mat.tab[0][0]; 		// Nombre de pixels non nuls
	double x1 = mat.tab[1][0]/omega;	// x moyen
	double y1 = mat.tab[0][1]/omega;	// y moyen

	// Boucle sur p et q tq p+q < N
	for(int p = 0; p < n; p++) {
		for(int q = 0; q < n-p; q++) {
			eta.tab[p][q]=0;
			for(int x = 0; x < pic->dimX; x++){
				for(int y = 0; y < pic->dimY; y++) {
					if(getPixel(*pic, x,y) != 0){	//pour recuperer seulement les pixels non nuls;
						/* Verification si l'exposant de omega est pair ou impair
						 * si oui : utilisation de l'expression fournie
						 */
						if((p+q+2)%2 == 0) {
							eta.tab[p][q]+= (pow(x-x1,p)*pow(y-y1,q))/pow(abs(omega),(p+q+2)/2.);
						}
						/* sinon:
						 * division par la racine de omega
						 */
						else {
							eta.tab[p][q]+= (pow(x-x1,p)*pow(y-y1,q))/(pow(abs(omega),(p+q+1)/2.)*sqrt(abs(omega)));

						}
					}
				}
			}
		}
	}
	return eta;

}


Matrice mom(BmpImg* pic, int n) {
	Matrice mat = creerMatrice(1,n);
	/* On calcule les moments pour tout p,q tel que p+q < N
	 * Alors on aura N lignes
	 * à chaque ligne i, le nombre de colonnes sera N - i
	 * On obtiendra alors une matrice triangulaire inversé
	 */
	for(int p = 0; p < n; p++) {			
		for(int q = 0; q < n-p; q++) {			
			mat.tab[p][q] = 0;				// Initialisation à 0, je fais pas confiance au calloc;
			// Boucle sur les pixels de l'image
			for(int x = 0; x < pic->dimX; x++){
				for(int y = 0; y < pic->dimY; y++) {
					if(getPixel(*pic, x,y) != 0)	// Vérification que le pixel est non nul
						mat.tab[p][q] += pow(x,p)*pow(y,q);	// somme
				}
				

			}
		}	
		
	}
	return mat;
}
