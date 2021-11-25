%% Lecture et Binairisation
% Lecture de l'image
I = imread('ImageBinaire.bmp');
% Conversion vers des double pour le calcul
I = double(I);
% Calcul de l'image niveaux de gris
I = (I(:,:,1)+I(:,:,2)+I(:,:,3))/3;
% Binairisation
I = I > 50;

%% Calcul des moments

% Téma les dimensions de l'image
[xmax, ymax] = size(I);

% Téma l'allocation de la matrice des moments
M = zeros(10);

% Boucle pour le calcul des moments, même logique qu'en C
for p = 0:9
    for q = 0:9-p
        for x = 1:xmax
            for y = 1:ymax
                if(I(x,y) == 1)
                M(p+1, q+1) = M(p+1,q+1) + (x^p)*(y^q)*I(x,y);
            
                end
            end
        end
    end
end
%% Ecriture des momens dans un fichier text

dlmwrite('Moments_Geometriques_en_MATLAB.txt',M,'delimiter','\t')

%% Calcul Erreure relative
% Allocation de la matrice des erreures relatives
ti = zeros(10);

% Boucle sur la matrice
for p = 1:10
    for q = 1:10-p+1

        % Calcul de l'erreure relative
        ti(p,q) = (M(p,q)-MomentGeometriquesenC(p,q))/M(p,q);
    
    end
end