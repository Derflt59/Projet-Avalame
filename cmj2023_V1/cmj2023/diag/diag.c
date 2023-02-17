/* Le but de ce programme est de reçevoir en ligne de commande une lingne 
en FEN avec : 
>>> Minuscule pour les jaunes ;
>>> Majuscule pour les rouges ;
>>> Avec les caractères         u ; d ; t ; q ; c 
Correspondant à des tours de    1 ; 2 ; 3 ; 4 ; 5 de hauteur ;
>>> Si la lettre est suivie par m ou b cela correspond au malus et au bonus ;
>>> ordre des lettres correspond à leur position. 
>>> les deux derniers caractère de la chaine sont le nombre de cases restant ;
>>> Cette chaine se termine par " r"

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chaineFEN();
void EcritModification();
void analyse(char chaine);
void EcritBasique(char chaine);
void MalusBonnusModifica(char* chaine,int* mJ,int* mR,int* bJ,int* bR);



void main{
    char FEN[100] = chaineFEN();
    EcritBasique(FEN);
    EcritModification(FEN);
}

char chaineFEN(){
    char chaine[100];
    printf("Entrez une chaine de caractères : \n");
    scanf("%s", chaine);
    printf("La chaine est : %s\n" , chaine);
    return chaine;
    }

void EcritBasique(char* chaine){
    int mJ, mR, bJ,bR;
    MalusBonnusModifica(chaine,mJ, mR, bJ,bR)
    FILE *fic = fopen("teste.js", "w+");
    fprintf("teste.js", "traiterJson({\n
        \"trait\":2,\n
        \"numDiag\":2,\n
        \"notes\": \"Une position à nombre de pièces réduit. Ici, pour gagner, les rouges jouent 4->0. Pour ne pas faire apparaître de pions évolution, il suffit de les affecter par paires bonus/malus aux mêmes colonnes\",\n
        \"fen\": \"%s\",\n
        \"bonusJ\":%d,\n
        \"malusJ\":%d,\n
        \"bonusR\":%d,\n
        \"malusR\":%d,\n
        ", chaine,mJ, mR, bJ,bR);
    fclose("teste.js");
}
            
//fonction détection de la postion malus et bonnus et une modification : 
void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR){
    int i, j; 
    for (i=0; i<strlen(FEN); i++){
        if(FEN[i] = 'B' || FEN[i-1] = 'u'|| FEN[i-1] = 'd'|| FEN[i-1] = 't'|| FEN[i-1] = 'q'|| FEN[i-1] = 'c'|| FEN[i-1] = 'U'|| FEN[i-1] = 'D'|| FEN[i-1] = 'T'|| FEN[i-1] = 'Q'|| FEN[i-1] = 'C'){
           &bR = i-1;
           for(j=i;j<(strlen(FEN));j++){
                FEN[i]=FEN[i+1];
            }} //Dans le cas où 1 seul lettre de bonus rouge
        if(FEN[i] = 'M' || FEN[i-1] = 'u'|| FEN[i-1] = 'd'|| FEN[i-1] = 't'|| FEN[i-1] = 'q'|| FEN[i-1] = 'c'|| FEN[i-1] = 'U'|| FEN[i-1] = 'D'|| FEN[i-1] = 'T'|| FEN[i-1] = 'Q'|| FEN[i-1] = 'C'){
            &mR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[i]=FEN[i+1];
            }} //Dans le cas où 1 seul lettre de malus rouge
        if(FEN[i] = 'b' || FEN[i-1] = 'u'|| FEN[i-1] = 'd'|| FEN[i-1] = 't'|| FEN[i-1] = 'q'|| FEN[i-1] = 'c'|| FEN[i-1] = 'U'|| FEN[i-1] = 'D'|| FEN[i-1] = 'T'|| FEN[i-1] = 'Q'|| FEN[i-1] = 'C'){
            &bR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[i]=FEN[i+1];
            }
        } //Dans le cas où 1 seul lettre de bonus jaune
        if(FEN[i] = 'm' || FEN[i-1] = 'u'|| FEN[i-1] = 'd'|| FEN[i-1] = 't'|| FEN[i-1] = 'q'|| FEN[i-1] = 'c'|| FEN[i-1] = 'U'|| FEN[i-1] = 'D'|| FEN[i-1] = 'T'|| FEN[i-1] = 'Q'|| FEN[i-1] = 'C'){
            &mR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[i]=FEN[i+1];
            }} //Dans le cas où 1 seul lettre de malus jaune
        }
}

void EcritModification(char *FENin){
    char writing[1653] = analyse(&FENin);
    FILE *fic = fopen("teste.js", "a+");
    fprintf("teste.js", "%s", writing);
    fclose("teste.js");
}
void analyse(char chaine, int mJ,int mR,int bJ,int bR){
    int i=0, j, nb=0, check=0;
    int couleur=0, valeur=0;
    char implementation[28] = "\a{\"nb\":0, \"couleur\":0},\n"
    for(j=0;j<strlen(chaine);j++){
        if(chaine[j] == 'u') {
            couleur = 2; 
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'd') {
            couleur = 2; 
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 't') {
            couleur = 2; 
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'q') {
            couleur = 2; 
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'c') {
            couleur = 2; 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'U') {
            couleur = 1; 
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'D') {
            couleur = 1; 
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'T') {
            couleur = 1; 
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'Q') {
            couleur = 1; 
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        if(chaine[j] == 'C') {
            couleur = 1; 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(chaine,implementation);
        }
        
        if((chaine[j] == '1' || chaine[j] == '2' || chaine[j] == '3' || chaine[j] == '4' || chaine[j] == '5' || chaine[j] == '6' || chaine[j] == '7' || chaine[j] == '8' || chaine[j] == '9' || chaine[j] == '0' )&& check != 0){
            if(chaine[j+1] == '1' || chaine[j+1] == '2' || chaine[j+1] == '3' || chaine[j+1] == '4' || chaine[j+1] == '5' || chaine[j+1] == '6' || chaine[j+1] == '7' || chaine[j+1] == '8' || chaine[j+1] == '9' || chaine[j+1] == '0'){
                check = 2; 
            }
            else{
                check = 1;
            }
        }
        
        
    }
    if (check == 2){
        nb = (chaine[j-3]-'0') + (chaine[j-4]-'0') *10;
    }

    for(i;i<nb;i++) strcat(chaine,"\a{\"nb\":0, \"couleur\":0},\n");    //permet d'affichier toute les casses vides
    
    strcat(chaine,"]\n });\n")
}
