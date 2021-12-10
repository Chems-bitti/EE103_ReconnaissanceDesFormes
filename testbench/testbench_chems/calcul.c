#include "calcul.h"


double distance_euclidienne(Matrice mat1, Matrice mat2, int ordre){

    int p,q;
    double res= 0;

    if (mat1.N < ordre || mat2.N < ordre){
        printf("ERREUR : Les matrices sont trop petites\n");
        return 0;
    }else{
        for(p = 0 ; p < ordre; p++){
            for(q = 0 ; q < ordre - p;q++){
                res += pow(mat1.tab[p][q]-mat2.tab[p][q],2);
            }
        }
    }
    return sqrt(res);
}


double base_legendre(double x, int n, Matrice coef){
    double res=0;
    x = (double) x;
    for(int i=0; i<=n; i++){
        res+=(coef.tab[n][i])*pow(x,i);
    }
    return res;
}

Matrice coefLegendre(int n) {
	Matrice an = creerMatrice(0, n);
	an.tab[0][0] = 1;
	if(n>0){
        	an.tab[1][0]=0;
        	an.tab[1][1]=1;
    	}
	for(int i=2; i<=n; i++){    //Détermination de tous les an jusqu'à l'ordre souhaité
        	for(int j=0; j<=i-2; j++){ // on veut pas que j==i
                	an.tab[i][j]= (-i+1)*(an.tab[i-2][j])/ i;
                }
		for(int j = 0; j <= i; j++) { // rebouclage pour avoir les bons termes
			an.tab[i][j] += (2*i-1)*an.tab[i-1][j-1]/ i;
		}
    	}
    	return an;
}

Matrice mom_legendre(BmpImg* pic, int n) {
	Matrice lambda = creerMatrice(1,n);
	Matrice eta = momcentre(pic, n);
	double Cpq = 0;
	Matrice coef = coefLegendre(n);
	for(int p = 0; p <= n; p++) {
		for(int q = 0; q <= n-p; q++){
			lambda.tab[p][q] = 0;
			Cpq = (2*p+1)*(2*q+1)/4.;
			for(int i = 0; i <= p; i++) {
				for(int j = 0; j <= q; j++) {
					lambda.tab[p][q] += Cpq*coef.tab[p][i]*coef.tab[q][j]*eta.tab[i][j];
				}
			}
		}
	}
	supprMatrice(&coef);
	supprMatrice(&eta);
	return lambda;
}
Matrice momcentre(BmpImg* pic, int n) {
	
	Matrice eta = creerMatrice(1,n); 	// allocation de la matrice
	Matrice mat = mom(pic, n);		// calcul des moments géometrique
	
	double omega = mat.tab[0][0]; 		// Nombre de pixels non nuls
	double x1 = mat.tab[1][0]/omega;	// x moyen
	double y1 = mat.tab[0][1]/omega;	// y moyen

	// Boucle sur p et q tq p+q < N
	for(int p = 0; p <= n; p++) {
		for(int q = 0; q <= n-p; q++) {
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
	supprMatrice(&mat);
	return eta;

}


Matrice mom(BmpImg* pic, int n) {
	Matrice mat = creerMatrice(1,n);
	/* On calcule les moments pour tout p,q tel que p+q < N
	 * Alors on aura N lignes
	 * à chaque ligne i, le nombre de colonnes sera N - i
	 * On obtiendra alors une matrice triangulaire inversé
	 */
	for(int p = 0; p <= n; p++) {			
		for(int q = 0; q <= n-p; q++) {			
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
