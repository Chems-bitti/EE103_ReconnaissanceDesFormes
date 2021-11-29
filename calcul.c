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

