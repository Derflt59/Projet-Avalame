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

char* chaineFEN();
char analyse(char* chaine, int mJ,int mR,int bJ,int bR);
void MalusBonnusModifica(char* chaine,int* mJ,int* mR,int* bJ,int* bR, int* color);

int main(int Num, char **FEN){
    int mJ=0, mR=0, bJ=0,bR=0,color=0;
    char* include = (char*) malloc(strlen(FEN) + 1);
    MalusBonnusModifica(FEN, &mJ, &mR, &bJ, &bR, &color);
    strcpy(include, FEN);

    FILE *PremierEcrit = fopen("teste.js", "w+");
    fprintf(PremierEcrit, "traiterJson({\n\"trait\":%d,\n\"numDiag\":%d,\n\"notes\": \"Une position à nombre de pièces réduit. Ici, pour gagner, les rouges jouent 4->0. Pour ne pas faire apparaître de pions évolution, il suffit de les affecter par paires bonus/malus aux mêmes colonnes\",\n\"fen\": \"%s\",\n\"bonusJ\":%d,\n\"malusJ\":%d,\n\"bonusR\":%d,\n\"malusR\":%d,\n",color, Num, include,mJ, mR, bJ,bR);
    fclose(PremierEcrit);

    FILE *DesiemeEcrit = fopen("teste.js", "a+");
    fprintf(DesiemeEcrit, "%s", analyse(FEN,mJ, mR, bJ,bR));
    fclose(DesiemeEcrit);

    free(include);
    return 0;
}

/* 
Nom de fonction : chaineFEN
Principe de fonctionnement : Récupère la chaine FEM 
Returne : la chaine FEN
*/
char* chaineFEN(){
    char chaine[100];
    printf("Entrez une chaine de caractères : \n");
    fgets(chaine, 100, stdin);
    getchar();
    printf("La chaine est : %s\n" , chaine);
    return chaine;
}

/* 
Nom de fonction : MalusBonnusModifica
Principe de fonctionnement : Passe en revue toute les postitions jusqu'a trouvé les bonus / maluse de chaque couleur
Returne : la chaine FEN modiffier : sans les indications bonus / maluse ; ainsi que les positions de chacun d'entre eu 
*/

void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR, int* color){
    int i, j; 
    for (i=0; i<strlen(FEN); i++){
        if(FEN[i] == 'B' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            *bR = i-1;
           for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }} //Dans le cas où 1 seul lettre de bonus rouge
        if(FEN[i] == 'M' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            *mR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }} //Dans le cas où 1 seul lettre de malus rouge
        if(FEN[i] == 'b' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            *bR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } //Dans le cas où 1 seul lettre de bonus jaune
        if(FEN[i] == 'm' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            *mR = i-1;
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }} //Dans le cas où 1 seul lettre de malus jaune
        }
    if (FEN[i] == 'r') *color = 2;
    if (FEN[i] == 'j') *color = 1;
}

char analyse(char* FEM, int mJ,int mR,int bJ,int bR){
    int i=0, j, nb=0;
    int couleur=0, valeur=0;
    char implementation[28] = "\a{\"nb\":0, \"couleur\":0},\n";
    char envoi[2000];
    
    for(j=0;j<strlen(FEM);j++){
        if(FEM[j] == 'u') {
            couleur = 2; 
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'd') {
            couleur = 2; 
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 't') {
            couleur = 2; 
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'q') {
            couleur = 2; 
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'c') {
            couleur = 2; 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'U') {
            couleur = 1; 
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'D') {
            couleur = 1; 
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'T') {
            couleur = 1; 
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'Q') {
            couleur = 1; 
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        if(FEM[j] == 'C') {
            couleur = 1; 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            implementation[7] = valeur;
            implementation[19] = couleur;
            strcat(envoi,implementation);
        }
        
        //Pour vérifier le nombre de case vide 
        if((FEM[j] >= '1' && FEM[j] <= '9' )){
            nb = nb*10 + (FEM[j]-'0');
        }
        
    }


    for(i;i<nb;i++) strcat(envoi,"\a{\"nb\":0, \"couleur\":0},\n");    //permet d'affichier toute les casses vides
    
    strcat(envoi,"]\n });\n");
    return envoi;
}
