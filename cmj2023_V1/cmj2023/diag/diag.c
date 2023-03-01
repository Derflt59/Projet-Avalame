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

char analyse(char* chaine, int mJ,int mR,int bJ,int bR, char envoi[8000]);
void MalusBonnusModifica(char* chaine,int* mJ,int* mR,int* bJ,int* bR, int* color);

int main(int argc, char **argv){
    //Vérification du nombre d'argument !
    fprintf(stdout, "Num diag : %s \n", argv[1]);
    fprintf(stdout, "Chaine FEN : %s\n", argv[2]);

    if (argc != 3) {                                                                                                                                            //vérifie si il n'y a pas plus de 3 arguments
        fprintf(stderr, "Erreur dans l'exécution de : %s ; il y a plus de 3 argument, n'oublier pas les guillements pour la chaine FEN\n", argv[0]);
        return 1;
    }

    //Déclaration de variable : 
    int mJ=-1, mR=-1, bJ=-1,bR=-1,color=0,i;    
    int num=(*argv[1]-'0');
    char *FEN, choix;
    FEN = (argv[2]);
    char FEN_copy[strlen(FEN)];
    char nom[80], note[400], envoi[8000];

    for(i=0 ; i<strlen(FEN);i++){       //recopy la chaine FEN dans une autre pour l'affichage
        FEN_copy[i]=FEN[i];
    }

    //Pour le nom du fichier 
    printf("Voulez vous changer le nom du fichier ?  (Y/N) \a");                             
    scanf("%c",&choix);
    getchar();
    if(choix =='Y' || choix =='y'){
        printf("Quelle est le nom ? \n");
        fgets(nom,80,stdin);
        nom[strcspn(nom, "\n")] = 0;                                                                                                                            //suppression du caractère de retour à la ligne
        strcat(nom,".js");
    }
    if(choix =='N' || choix == 'n'){
        printf("Très bien ! \a");
        strcpy(nom,"diag.js");
    }
    
   
    fprintf(stdout, "nom du fichier : %s \n", nom);

    //Pour l'ajout de note ou non
    printf("Voulez vous ajouté une note ? (Y/N) \a");
    scanf("%c",&choix);
    if(choix =='Y' || choix =='y'){
        printf("Que voulez vous écrire ? \n");
        fgets(note,200,stdin);
        getchar();
        note[strcspn(note, "\n")] = 0;                                                                                                                              //suppression du caractère de retour à la ligne
    }
    if(choix =='N' || choix == 'n'){
        printf("Très bien ! \a");
        strcpy(note,"Pas de note spécifier");
    }
    
    fprintf(stdout," Note interne : %s \n",note);
    fprintf(stdout, " %s \n", "After choise");

    //Création du document
    FILE *Creation = fopen(nom, "w+");
    fclose(Creation);

    fprintf(stdout, " %s \n", "After make");    
    fprintf(stdout, " \n FEN_copy : %s \n", FEN_copy);
    fprintf(stdout, " \n FEN : %s \n", FEN);

    //Utilisation de modification B/M pour les écrits
    MalusBonnusModifica(FEN, &mJ, &mR, &bJ, &bR, &color);

    fprintf(stdout, " \n FEN : %s \n", FEN);

    fprintf(stdout, "Malus : J : %d, R :%d ; Bonnus : J : %d, R : %d ; Color : %d \n", mJ, mR, bJ, bR, color);
   

    //traite la première partie (celle qui ne fait pas le détaille avec les collonnes)
    FILE *PremierEcrit = fopen(nom, "a+");
    fprintf(PremierEcrit, "traiterJson({\n\"trait\":%d,\n\"numDiag\":%d,\n\"notes\": \"%s\",\n\"fen\": \"%s\",\n\"bonusJ\":%d,\n\"malusJ\":%d,\n\"bonusR\":%d,\n\"malusR\":%d,\n\"cols\":[ \n",color, num, note, FEN_copy,mJ, mR, bJ,bR);
    fclose(PremierEcrit);

    fprintf(stdout, " %s \n", "After 1er");

    //traite la 2e partie, celle qui traite uniquement des colones 
    FILE *DesiemeEcrit = fopen(nom, "a+");
    analyse(FEN,mJ, mR, bJ,bR, envoi);
    fprintf(DesiemeEcrit, "%s", envoi);
    fclose(DesiemeEcrit);

    fprintf(stdout, " %s \n", "After 2nd");
    
    return 0;
    
}


/* 
Nom de fonction : MalusBonnusModifica
Principe de fonctionnement : Passe en revue toute les postitions jusqu'a trouvé les bonus / maluse de chaque couleur
Returne : la chaine FEN modiffier : sans les indications bonus / maluse ; ainsi que les positions de chacun d'entre eu 
*/

void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR, int* color){
    int i=0, j, IndBR=0, IndMR=0,IndBJ=0, IndMJ=0; 
    while (FEN[i]!='\0'){
        fprintf(stdout,"%d ;",i);
        if(i==0 && (FEN[i] == 'B' || FEN[i] == 'M' || FEN[i] == 'b' || FEN[i] == 'm' ||(FEN[j+1] >= '1' && FEN[j+1] <= '9' ))){
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        }
        else{
        
        if(FEN[i] == 'B' && ( FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
            if(IndBR==0) {*bR = i-1; IndBR=1;} //prend uniquement le premier emplacement du bonnus rouge
            fprintf(stdout,"%s ","Bonnus rouge\n -->");
            fprintf(stdout,"%d ",*bR);
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'M' && ( FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
            if(IndMR==0) {*mR = i-1; IndMR=1;} //prend uniquement le premier emplacement du malus rouge
            fprintf(stdout,"%s","Malus rouge\n");
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'b' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
            if(IndBJ==0) {*bJ = i-1; IndBJ=1;} //prend uniquement le premier emplacement du bonus jaune
            fprintf(stdout,"%s","Bonnus jaune \n");
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 

        if(FEN[i] == 'm' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
            if(IndMJ==0) {*mJ = i-1; IndMJ=1;} //prend uniquement le premier emplacement du malus rouge
            fprintf(stdout,"%s","Malus jaune \n");
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        } 
    }
    
    if (FEN[i] == 'r') *color = 2;
    if (FEN[i] == 'j') *color = 1;

    i++;
    }
    
}


/* 
Nom de fonction : analyse
Principe de fonctionnement : Prend la chaine FEN en entré pour pouvoir modiffier la valeur du pointeur d'envoie 
Returne : rien
*/
char analyse(char* FEM, int mJ,int mR,int bJ,int bR, char envoi[8000]){
    int i=0, j, nb=0;
    int couleur=0, valeur=0;
    //char implementation[28] = "\t{\"nb\":0, \"couleur\":0},\n";
    
    for(j=0;j<strlen(FEM);j++){
        
        if(FEM[j] == 'u') {
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;

            strcat(envoi,"\t{\"nb\":");
            if (valeur == -1)  strcat(envoi,"-1");
            if (valeur == 0)  strcat(envoi,"0");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            
        }
        if(FEM[j] == 'd') {
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 0)  strcat(envoi,"0");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 't') {
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 'q') {
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            if (valeur == 6)  strcat(envoi,"6");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 'c') { 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            if (valeur == 6)  strcat(envoi,"6");
            if (valeur == 7)  strcat(envoi,"7");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
        }

        if(FEM[j] == 'U') {
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;

            strcat(envoi,"\t{\"nb\":");
            if (valeur == -1)  strcat(envoi,"-1");
            if (valeur == 0)  strcat(envoi,"0");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            
        }
        if(FEM[j] == 'D') {
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 0)  strcat(envoi,"0");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 'T') {
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 1)  strcat(envoi,"1");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 'Q') {
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 2)  strcat(envoi,"2");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            if (valeur == 6)  strcat(envoi,"6");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
        }
        if(FEM[j] == 'C') { 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 3)  strcat(envoi,"3");
            if (valeur == 4)  strcat(envoi,"4");
            if (valeur == 5)  strcat(envoi,"5");
            if (valeur == 6)  strcat(envoi,"6");
            if (valeur == 7)  strcat(envoi,"7");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
        }

        //Pour vérifier le nombre de case vide 
        if((FEM[j] >= '1' && FEM[j] <= '9' )){
            nb = nb*10 + (FEM[j]-'0');
        }
        
    }

    for(i;i<nb;i++) strcat(envoi,"\t{\"nb\":0, \"couleur\":0},\n");    //permet d'affichier toute les casses vides
    
    envoi[strlen(envoi)-2] = '\0';

    strcat(envoi,"\n]\n});\n");                                          //Finalise le document

                                                               
}
