#include "calcul.h"

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

