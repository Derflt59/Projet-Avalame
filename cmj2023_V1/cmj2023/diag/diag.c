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

//char analyse(char* chaine, int mJ,int mR,int bJ,int bR, char envoi[8000]);
//void MalusBonnusModifica(char* chaine,int* mJ,int* mR,int* bJ,int* bR, int* color);

int main(int argc, char *argv[]){
    //Vérification du nombre d'argument !
    printf("fff");
    
    /* if (argc != 2) {
        fprintf(stderr, "Usage: %s FEN\n", argv[0]);
        return 1;
    }
    //Déclaration de variable : 
    int mJ=0, mR=0, bJ=0,bR=0,color=0;
    int num=(*argv[0]-'0');
    char* FEN = argv[1], choix;
    char nom[80], note[400], envoi[8000];
    char* FEN_copy ;                            // copie de la chaîne FEN pour la modification est l'analyse
    strcpy(FEN_copy,FEN);
    
    //Pour le nom du fichier 
    printf("Voulez vous changer le nom du fichier ? : Y/N \n");                             
    scanf("%c",&choix);
    getchar();
    if(choix =='Y' || choix =='y'){
        printf("Quelle est le nom ? (Si espace ne pas oublier les guillements) \n");
        scanf("%s",nom);
        getchar();
        strcat(nom,".js");
    }
    if(choix =='N' || choix == 'n'){
        printf("Très bien ! \n");
        strcpy(nom,"diag.js");
    }
    */
   /*
    FILE *Creation = fopen(nom, "w+");
    fclose(Creation);

    //Pour l'ajout de note ou non
    printf("Voulez vous ajouté une note : Y/N \n");
    scanf("%c",&choix);
    if(choix =='Y' || choix =='y'){
        printf("Que voulez vous écrire \n");
        fgets(note,400,stdin);
    }

    if(choix =='N' || choix == 'n'){
        printf("Très bien ! \n");
        strcpy(note,"Pas de note spécifier");
    }
    */
    //Utilisation de modification B/M pour les écrits
    //MalusBonnusModifica(FEN_copy, &mJ, &mR, &bJ, &bR, &color);

    /*

    //traite la première partie (celle qui ne fait pas le détaille avec les collonnes)
    FILE *PremierEcrit = fopen(nom, "a+");
    fprintf(PremierEcrit, "traiterJson({\n\"trait\":%d,\n\"numDiag\":%d,\n\"notes\": \"%s\",\n\"fen\": \"%s\",\n\"bonusJ\":%d,\n\"malusJ\":%d,\n\"bonusR\":%d,\n\"malusR\":%d,\n",color, num, note, FEN,mJ, mR, bJ,bR);
    fclose(PremierEcrit);

    */
    //traite la 2e partie, celle qui traite uniquement des colones 
    /*
    FILE *DesiemeEcrit = fopen(nom, "a+");
    analyse(FEN_copy,mJ, mR, bJ,bR, envoi);
    fprintf(DesiemeEcrit, "%s", envoi);
    fclose(DesiemeEcrit);
    */
    

    
    return 0;
    
}


/* 
Nom de fonction : MalusBonnusModifica
Principe de fonctionnement : Passe en revue toute les postitions jusqu'a trouvé les bonus / maluse de chaque couleur
Returne : la chaine FEN modiffier : sans les indications bonus / maluse ; ainsi que les positions de chacun d'entre eu 


void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR, int* color){
    int i=0, j, IndBR=0, IndMR=0,IndBJ=0, IndMJ=0; 
    while (FEN[i]!='\0'){
        if(i==0 && (FEN[i] == 'B' || FEN[i] == 'M' || FEN[i] == 'b' || FEN[i] == 'm' ||(FEN[j] >= '1' && FEN[j] <= '9' ))){
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        }
        else{
        if(FEN[i] == 'B' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            if(IndBR==0) {*bR = i-1; IndBR=1;} //prend uniquement le premier emplacement du bonnus rouge
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'M' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            if(IndMR==0) {*mR = i-1; IndMR=1;} //prend uniquement le premier emplacement du malus rouge
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'b' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            if(IndBJ==0) {*bJ = i-1; IndBJ=1;} //prend uniquement le premier emplacement du bonus jaune
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'm' || FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C'){
            if(IndMJ==0) {*mJ = i-1; IndMJ=1;} //prend uniquement le premier emplacement du malus rouge
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 
    }
    
    if (FEN[i] == 'r') *color = 2;
    if (FEN[i] == 'j') *color = 1;
    
    }
    i++;
}
*/

/* 
Nom de fonction : analyse
Principe de fonctionnement : Prend la chaine FEN en entré pour pouvoir modiffier la valeur du pointeur d'envoie 
Returne : rien

char analyse(char* FEM, int mJ,int mR,int bJ,int bR, char envoi[8000]){
    int i=0, j, nb=0;
    int couleur=0, valeur=0;
    char implementation[28] = "\a{\"nb\":0, \"couleur\":0},\n";
    
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
    
    strcat(envoi,"]\n });\n");                                          //Finalise le document

                                                               
}
*/