clear all;
close all;

%% On suppose que l'image est en noir et blanc

I = imread("car.png"); % ouverture d'image et stockage d'une matrice

% Affichage de l'image originale
figure(1)
imshow(I)

%% Binairisation image
I = I > 50;
% Affichage de l'imagie binairisé
figure(2)
imshow(I);

%% Écriture Fichier format BMP
imwrite(I,"test.bmp");