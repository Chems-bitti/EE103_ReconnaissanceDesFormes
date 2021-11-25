Fonction moments centrés et normés.(A tester)


long double **(BmpImg* pic, int n){


    long double** eta = alloc(n,n);	 //allocation de la matrice moment centrés et normés
    long double **res= mom(*pic,n);   //recuperation des moments de l'image
    double omega = res[0][0];
    double x1 = res[1][0]/ res[0][0];
    double y1 = res[0][1]/ res[0][0];
    int x,y;
    int p,q;


    for(p = 0; p < n; p++){
        for(q = 0;q < n-p;q++){
              eta[p][q]=0;
            for(x = 0; x < pic->dimX; x++){
				        for(y = 0; y < pic->dimY; y++) {
				            if(getPixel(*pic, x,y) != 0){  //pour recuperer seulement les pixels non nuls;
                        eta[p][q]+= (pow(x-x1,p)*pow(y-y1,q))/pow(abs(omega),(p+q+2)/2);
				    }
                }
        }
    }
    }
        return eta;
}


