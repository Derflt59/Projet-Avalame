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

    //vérification du nombre d'argument :
    if (argc != 3) {                                                                                                                                            //vérifie si il n'y a pas plus de 3 arguments
        fprintf(stderr, "Erreur dans l'exécution de %s : il faut 3 arguments, n'oublier pas les guillements pour la chaine FEN\n", argv[0]);
        fprintf(stderr,"Rapple : %s <num_diag> <chaine_FEN>\n", argv[0]);
        return 1;
    }

    //vérification si le numérau de diagramme est bien un nombre :
    if (*argv[1] < 48 || *argv[1] > 57)  {
        fprintf(stderr,"Erreur dans l'exécution de %s : le numero de diagramme doit etre un chiffre \n",argv[0]);
        fprintf(stderr,"Rappel : %s <num_diag> <chaine_FEN>\n", argv[0]);
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

    #ifdef __DEBUG__
    fprintf(stdout,"valeur de i : %d \n",i);
    fprintf(stdout, "Chaine FEN_Copy : %s\n", FEN_copy);
    fprintf(stdout, "Emplacement i : %c \n", FEN[i-1]);
    #endif

    //vérification de la conformité de la chaine FEN avant le début des traitements : (utilisation du code ACSII)
    if (FEN[i-1] != 'r' && FEN[i-1] != 'j' && FEN[i-1] != 'R' && FEN[i-1] != 'J')  {
        fprintf(stderr,"Erreur dans l'exécution de %s : la trace doit être un r ou un j\n",argv[0]);
        fprintf(stderr,"Rappel : %s <num_diag> <chaine_FEN> \n", argv[0]);
        return 1;
    }

    //Pour le nom du fichier 
    fgets(nom, sizeof(nom), stdin);                         // Récupère les entrées clavier jusqu'on appuis sur la bar entrer pour récupéré le nom      
    if(*nom=='\n') strcpy(nom,"diag");                     // Si le nom est vide on prend juste le nom de base qui est diag.js
    nom[strcspn(nom, "\n")] = 0;                          // Supprime le \n si présent en dernier 
    strcat(nom,".js");                                   // Rajoute l'extention .js au nom donné 

    #ifdef __DEBUG__
    fprintf(stdout, "nom du fichier : %s \n", nom);
    #endif

    //Pour l'ajout d'une note ou non
    printf("Entré une descriptions, taille maximale 400 charactère, appuiller sur Ctrl+D pour quitter le mode intéractif: \n");
    while (fgets(note,400,stdin) != NULL) ;                      // Récupère les entrées clavier jusqu'on appuis sur Ctrl+D pour la note
    
    fprintf(stdout, "note du fichier : %s \n", note);           // montre si les notes sont vides ou pas 
    
    if(*note=='\0') strcpy(note,"Pas de note spécifier");       //rajoute une note disant qu'il n'y a pas de note 

    fprintf(stdout, "note du fichier : %s \n", note);           //montre les notes 

    //Création du document
    FILE *Creation = fopen(nom, "w+");
    fclose(Creation);

    #ifdef __DEBUG__
    fprintf(stdout, " %s \n", "After make");    
    fprintf(stdout, " \n FEN_copy : %s \n", FEN_copy);
    fprintf(stdout, " \n FEN : %s \n", FEN);
    #endif

    //Utilisation de modification B/M pour les écrits
    MalusBonnusModifica(FEN, &mJ, &mR, &bJ, &bR, &color);

    //#ifdef __DEBUG__
    fprintf(stdout, " \n FEN : %s \n", FEN);
    fprintf(stdout, "Malus : J : %d, R :%d ; Bonnus : J : %d, R : %d ; Color : %d \n", mJ, mR, bJ, bR, color);
    //#endif

    //traite la première partie (celle qui ne fait pas le détaille avec les collonnes)
    FILE *PremierEcrit = fopen(nom, "a+");
    fprintf(PremierEcrit, "traiterJson({\n\"trait\":%d,\n\"numDiag\":%d,\n\"notes\": \"%s\",\n\"fen\": \"%s\",\n\"bonusJ\":%d,\n\"malusJ\":%d,\n\"bonusR\":%d,\n\"malusR\":%d,\n\"cols\":[ \n",color, num, note, FEN_copy,mJ, mR, bJ,bR);
    fclose(PremierEcrit);

    #ifdef __DEBUG__
    fprintf(stdout, " %s \n", "After 1er");
    #endif

    //traite la 2e partie, celle qui traite uniquement des colones 
    FILE *DesiemeEcrit = fopen(nom, "a+");
    analyse(FEN,mJ, mR, bJ,bR, envoi);
    fprintf(DesiemeEcrit, "%s", envoi);
    fclose(DesiemeEcrit);

    #ifdef __DEBUG__
    fprintf(stdout, " %s \n", "After 2nd");
    #endif

    return 0;
    
}


/* 
Nom de fonction : MalusBonnusModifica
Principe de fonctionnement : Passe en revue toute les postitions jusqu'a trouvé les bonus / maluse de chaque couleur
Returne : la chaine FEN modiffier : sans les indications bonus / maluse ; ainsi que les positions de chacun d'entre eu 
*/

void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR, int* color){
    int i=0, j,k, IndBR=0, IndMR=0,IndBJ=0, IndMJ=0,len; 

    //#ifdef __DEBUG__
    fprintf(stdout, " %s \n", "During make");
    fprintf(stdout, "FEN : %s \n", FEN);
    //#endif

    while((FEN[i]!='r') && (FEN[i]!='j') && (FEN[i]!='R') && (FEN[i]!='J') && (FEN[i]!= '\0') && (i <= strlen(FEN)+1)){
        #ifdef __DEBUG__
        fprintf(stdout,"%d ;",i);
        #endif

        if(i==0 && (FEN[i] == 'B' || FEN[i] == 'M' || FEN[i] == 'b' || FEN[i] == 'm')){
            
            fprintf(stdout, " %s \n", "1er verify");
            if(FEN[i] == 'B') {IndBR=1;}
            if(FEN[i] == 'M') {IndMR=1;}
            if(FEN[i] == 'b') {IndBJ=1;}
            if(FEN[i] == 'm') {IndMJ=1;}

            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        }
        else{
            #ifdef __DEBUG__
            fprintf(stdout, " %d : ", i);                   //affiche la position de la lettre
            fprintf(stdout, " %c \t", FEN[i]);              //affiche la lettre
            #endif
            
            if(FEN[i] == 'B' && ( FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                if(IndBR==0) {*bR = i-1; IndBR=1;} //prend uniquement le premier emplacement du bonnus rouge
                #ifdef __DEBUG__
                fprintf(stdout,"%s ","Bonnus rouge -->");
                fprintf(stdout,"%d \n",*bR);
                #endif
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 

            if(FEN[i] == 'M' && ( FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                if(IndMR==0) {*mR = i-1; IndMR=1;} //prend uniquement le premier emplacement du malus rouge
                #ifdef __DEBUG__
                fprintf(stdout,"%s","Malus rouge -->");
                fprintf(stdout,"%d \n",*mR);
                #endif
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 

            if(FEN[i] == 'b' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                if(IndBJ==0) {*bJ = i-1; IndBJ=1;} //prend uniquement le premier emplacement du bonus jaune
                #ifdef __DEBUG__
                fprintf(stdout,"%s","Bonnus jaune -->");
                fprintf(stdout,"%d \n",*bJ);
                #endif
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 

            if(FEN[i] == 'm' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                if(IndMJ==0) {*mJ = i-1; IndMJ=1;} //prend uniquement le premier emplacement du malus rouge
                #ifdef __DEBUG__
                fprintf(stdout,"%s","Malus jaune -->");
                fprintf(stdout,"%d \n",*mJ);
                #endif
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 
        }
    
        #ifdef __DEBUG__
        fprintf(stdout, "Chaine FEN : %s\n", FEN);          //Pour afficher la chaine FEN et voir les changements ou non
        #endif

        i++;
    }
    fprintf(stdout, " \n FEN : %s \n", FEN);
    if (FEN[i] == 'r' || FEN[i]=='R') *color = 2;                               //Si le dernier caractère est r alors la couleur est rouge
    if (FEN[i] == 'j' || FEN[i]=='J') *color = 1;                               //Si le dernier caractère est j alors la couleur est jaune
    
     
    while (i >= 0) {
        fprintf(stdout, "FEN : %s \n", FEN);
        if (FEN[i] >= '0' && FEN[i] <= '9') {
            if((FEN[i+1] >= '0' && FEN[i+1] <= '9') || (FEN[i+1]==' ')){}
            else{
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];   
                }
            }
        }

        else if(FEN[i] == ' '){
            if(FEN[i+1]!='j' && FEN[i+1]!='r' && FEN[i+1]!='J' && FEN[i+1]!='R'){
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            }
        }

        else if (FEN[i] != 'j' && FEN[i] != 'r' && FEN[i] != 'u' && FEN[i] != 'd' && FEN[i] != 't' && FEN[i] != 'q' && FEN[i] != 'c' && FEN[i] != 'J' && FEN[i] != 'R' && FEN[i] != 'U' && FEN[i] != 'D' && FEN[i] != 'T' && FEN[i] != 'Q' && FEN[i] != 'C') {
            for(j=i;j<(strlen(FEN));j++){
                FEN[j]=FEN[j+1];
            }
        
        }
        i--;
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

    for(j=0;j<strlen(FEM);j++){
        //Pour la couleur jaune 
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

        //Pour la couleur rouge
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

    for(i;i<nb;i++) strcat(envoi,"\t{\"nb\":0, \"couleur\":0},\n");         //permet d'affichier toute les casses vides
    
    envoi[strlen(envoi)-2] = '\0';                                          //Supprime la dernière virgule        

    strcat(envoi,"\n]\n});\n");                                             //Finalise le document

                                                               
}
