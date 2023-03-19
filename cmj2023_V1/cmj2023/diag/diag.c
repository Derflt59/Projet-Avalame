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

#define MAX_LENGTH 400

void analyse(char* chaine, int mJ,int mR,int bJ,int bR, char envoi[8000]);                      //analyse la chaine FEN et renvoie la chaine à injecté dans le fichier javascript
void MalusBonnusModifica(char* chaine,int* mJ,int* mR,int* bJ,int* bR, int* color);             //récupère l'emplacement des bonnus et malus et la couleur du joueur ainsi que la couleur
void SuppressionIndesirable(char* chaine);                                                      //supprime les caractères indésirable de la chaine FEN    

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
    if (*argv[1] < '0' || *argv[1] > '9')  {
        fprintf(stderr,"Erreur dans l'exécution de %s : le numero de diagramme doit etre un chiffre \n",argv[0]);
        fprintf(stderr,"Rappel : %s <num_diag> <chaine_FEN>\n", argv[0]);
        return 1;
    }

    //Déclaration de variable : 
    int mJ=-1, mR=-1, bJ=-1,bR=-1,color=0,i=0,c;    
    int num=(*argv[1]-'0');
    char *FEN, choix;
    FEN = (argv[2]);
    char FEN_copy[strlen(FEN)];
    char nom[80], note[MAX_LENGTH],envoi[8000];

    
    #ifdef __DEBUG__
    fprintf(stdout,"valeur de i : %d \n",i);
    fprintf(stdout, "Chaine FEN_Copy : %s\n", FEN_copy);
    fprintf(stdout, "Emplacement i : %c \n", FEN[i-1]);
    #endif

    //vérification de la conformité de la chaine FEN avant le début des traitements : (utilisation du code ACSII)
    i = strlen(FEN);                    //i est la longueur de la chaine FEN
    if (FEN[i-1] != 'r' && FEN[i-1] != 'j' && FEN[i-1] != 'R' && FEN[i-1] != 'J')  {
        fprintf(stderr,"Erreur dans l'exécution de %s : la trace doit être un r ou un j\n",argv[0]);
        fprintf(stderr,"Rappel : %s <num_diag> <chaine_FEN> \n", argv[0]);
        return 1;
    }

    fprintf(stdout, "Entrée un nom et appuyer sur enter pour valider :");

    //Pour le nom du fichier 
    fgets(nom, sizeof(nom), stdin);                                                                                     // Récupère les entrées clavier jusqu'on appuis sur la bar entrer pour récupéré le nom      
    if(*nom=='\n') strcpy(nom,"diag");                                                                                  // Si le nom est vide on prend juste le nom de base qui est diag.js
    nom[strcspn(nom, "\n")] = 0;                                                                                        // Supprime le \n si présent en dernier 
    if (nom[strlen(nom)-3] != '.' && nom[strlen(nom)-2] != 'j' && nom[strlen(nom)-1] != 's')   strcat(nom,".js");       // Si le nom n'a pas l'extention .js on rajoute l'extention
  
                               
    
    fprintf(stdout, "\n Nom du fichier : %s \n", nom);
    

    //Pour l'ajout d'une note ou non
    i=0;                //remise à 0 pour utilisation dans la boucle
    printf("Descriptions, taille maximale 400 charactère, appuiller sur Ctrl+D pour quitter le mode intéractif: \n");
    while ((c = getchar()) != EOF && i < MAX_LENGTH && c != '\0') {// Récupère les entrées clavier jusqu'on appuis sur Ctrl+D pour la note
        
        #ifdef __DEBUG__
        fprintf(stdout, "c : %c \n", c);            //affiche la valeur de c en char 
        #endif

        //vérifie si la touche entrer est appuyé et donc elle est transformé en balise <br> pour le fichier javascript
        if (c == 10) {           //code ascii de la touche entrer
            note[i++] = 60;      //code ascii de <
            note[i++] = 98;      //code ascii de b
            note[i++] = 114;     //code ascii de r
            note[i++] = 62;      //code ascii de >
        }
        else {note[i++] = c;}
       
        
        
    }
    note[i-4] = '\0';                                  
    
   
    #ifdef __DEBUG__
    fprintf(stdout, "note du fichier : %s \n", note);           //montre les notes 
    #endif

    //Création du document
    FILE *Creation = fopen(nom, "w+");                          // Création du fichier avec le nom donné en argument
    fclose(Creation);

    #ifdef __DEBUG__
    fprintf(stdout, " %s \n", "After make");    
    fprintf(stdout, " \n FEN_copy : %s \n", FEN_copy);
    fprintf(stdout, " \n FEN : %s \n", FEN);
    #endif

    //Suppression des caractères indésirable
    SuppressionIndesirable(FEN);
    
    //#ifdef __DEBUG__
    fprintf(stdout, " \n%s\n", "Après suppression des caractères indésirable");
    fprintf(stdout, " FEN : %s \n", FEN);
    //#endif
    
    for(i=0 ; i<strlen(FEN)+1 ;i++){       //recopy la chaine FEN dans une autre pour l'affichage
        FEN_copy[i]=FEN[i];
    }

    #ifdef __DEBUG__
    fprintf(stdout, " FEN_copy : %s \n", FEN_copy);             /*Affiche la chaine FEN qui à été copier dans FEN_copy et qui est corriger */
    #endif  

    //Utilisation de modification B/M pour les écrits
    MalusBonnusModifica(FEN, &mJ, &mR, &bJ, &bR, &color);

    //#ifdef __DEBUG__
    fprintf(stdout, " \n%s\n", "Après modification pour les B/M");
    fprintf(stdout, " FEN : %s \n", FEN);
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


//Fonction pour supprimer les caractères indésirable
//Principe de fonctionnement : Parcours la chaine FEN pour retirer les caractères indésirable en vérifiant si le caractère est un chiffre ou un espace puis si c'est une lettre autorisé
//Return : la chaine FEN sans les caractères indésirable
void SuppressionIndesirable(char* FEN){
    int i=strlen(FEN)-1, j=0;
    while (i >= 0) {
        #ifdef __DEBUG__
        fprintf(stdout, "FEN : %s ", FEN);
        fprintf(stdout, "\a c : %c \n", FEN[i]);
        #endif
        if (FEN[i] >= '0' && FEN[i] <= '9') {                               //Si le caractère est un chiffre
                                                                            // On ne fait rien
        }

        else if(FEN[i] == ' '){                                                                     //Si le caractère est un espace
            if(FEN[i+1]!='j' && FEN[i+1]!='r' && FEN[i+1]!='J' && FEN[i+1]!='R'){                   //Si le caractère suivant n'est pas une lettre de trait on supprime le caractère
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            }
        }

        else if(FEN[i] == 'j' || FEN[i] == 'r' || FEN[i] == 'J' || FEN[i] == 'R'){                  //Si le caractère est une lettre de trait
            if(FEN[i-1]!=' '){                                                                      //Si le caractère précédent n'est pas un espace on supprime le caractère
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            }
        }

        else if (FEN[i] != 'u' && FEN[i] != 'd' && FEN[i] != 't' && FEN[i] != 'q' && FEN[i] != 'c' && FEN[i] != 'j' && FEN[i] != 'r' && FEN[i] != 'J' && FEN[i] != 'R' && FEN[i] != ' ' && FEN[i] != 'M' && FEN[i] != 'B' && FEN[i] != 'm' && FEN[i] != 'B'){               //Si le caractère n'est pas une lettre autorisée
            for(j=i;j<(strlen(FEN));j++){                                                           //On supprime le caractère 
                FEN[j]=FEN[j+1];
            }
        
        }
        
        i--;
    }
}


/* 
Nom de fonction : MalusBonnusModifica
Principe de fonctionnement : Passe en revue toute les postitions jusqu'a trouvé les bonus / maluse de chaque couleur
Returne : la chaine FEN modiffier : sans les indications bonus / maluse ; ainsi que les positions de chacun d'entre eu 
*/

void MalusBonnusModifica(char* FEN,int* mJ,int* mR,int* bJ,int* bR, int* color){
    int i=0, j, IndBR=0, IndMR=0,IndBJ=0, IndMJ=0,len; 
    int nbBM; //nombre de bonus/malus pour chaque lettre

    #ifdef __DEBUG__
    fprintf(stdout, " %s \n", "During make");
    fprintf(stdout, "FEN : %s \n", FEN);
    #endif

    while((FEN[i]!='r') && (FEN[i]!='j') && (FEN[i]!='R') && (FEN[i]!='J') && (FEN[i]!= '\0') && (i <= strlen(FEN)+1)){
        #ifdef __DEBUG__
        fprintf(stdout,"%d ;",i);
        #endif

        if(i==0 && (FEN[i] == 'B' || FEN[i] == 'M' || FEN[i] == 'b' || FEN[i] == 'm')){     //si le premier caractère est un bonus ou malus et donc le supprime car ne set à rien
            
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
                if(IndBR==0) {
                    nbBM = 0; 
                    if(FEN[i-1] != 'u') { //si le bonnus n'est pas un bonnus la bonne couleur
                        
                        if(FEN[i-1] == 'U' && IndMR==0){*bR = i-1;IndBR=1;}

                        else if(FEN[i-1] == 'D' || FEN[i-1] == 'd'){
                            if(mR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*bR = i-1; IndBR=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre
                        }
                        else if(FEN[i-1] == 'T' || FEN[i-1] == 't'){
                            if(mR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 2) {*bR = i-1; IndBR=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'C' || FEN[i-1] == 'c'){
                            if(mR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*bR = i-1; IndBR=1;}      //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'Q' || FEN[i-1] == 'q'){
                            if(mR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*bR = i-1; IndBR=1;}     //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        
                        
                    } //prend uniquement le premier emplacement du bonnus rouge
               
                }               
               
                #ifdef __DEBUG__
                fprintf(stdout,"%s ","Bonnus rouge -->");
                fprintf(stdout,"%d \n",*bR);
                #endif

                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 

            else if(FEN[i] == 'M' && ( FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                
                if(IndMR==0) {
                    nbBM = 0; 
                    if(FEN[i-1] != 'u') { //si le bonnus n'est pas un bonnus la bonne couleur
                        
                        if(FEN[i-1] == 'U' && IndBR==0){*mR = i-1;IndMR=1;}

                        else if(FEN[i-1] == 'D' || FEN[i-1] == 'd'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*mR = i-1;IndMR=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre
                        }
                        else if(FEN[i-1] == 'T' || FEN[i-1] == 't'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 2) {*mR = i-1;IndMR=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'C' || FEN[i-1] == 'c'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*mR = i-1;IndMR=1;}      //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'Q' || FEN[i-1] == 'q'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*mR = i-1;IndMR=1;}     //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        
                        
                    } //prend uniquement le premier emplacement du bonnus rouge
               
                }
                
                #ifdef __DEBUG__
                fprintf(stdout,"%s","Malus rouge -->");
                fprintf(stdout,"%d \n",*mR);
                #endif
                for(j=i;j<(strlen(FEN));j++){       //supprime le malus rouge de la chaine FEN
                    FEN[j]=FEN[j+1];
                }
            } 

            else if(FEN[i] == 'b' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                
                if(IndBJ==0) {
                    nbBM = 0; 
                    if(FEN[i-1] != 'U') { //si le bonnus n'est pas un bonnus la bonne couleur
                        
                        if(FEN[i-1] == 'u' && IndMJ==0){*bJ = i-1;IndBJ=1;}

                        else if(FEN[i-1] == 'D' || FEN[i-1] == 'd'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*bJ = i-1;IndBJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre
                        }
                        else if(FEN[i-1] == 'T' || FEN[i-1] == 't'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 2) {*bJ = i-1;IndBJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'C' || FEN[i-1] == 'c'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*bJ = i-1;IndBJ=1;}      //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'Q' || FEN[i-1] == 'q'){
                            if(bR == (i-1)) {nbBM++;}
                            if(mJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 3) {*bJ = i-1;IndBJ=1;}     //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        
                        
                    } //prend uniquement le premier emplacement du bonnus rouge
               
                }

                #ifdef __DEBUG__
                fprintf(stdout,"%s","Bonnus jaune -->");
                fprintf(stdout,"%d \n",*bJ);
                #endif
                for(j=i;j<(strlen(FEN));j++){
                    FEN[j]=FEN[j+1];
                }
            } 

            else if(FEN[i] == 'm' && (FEN[i-1] == 'u'|| FEN[i-1] == 'd'|| FEN[i-1] == 't'|| FEN[i-1] == 'q'|| FEN[i-1] == 'c'|| FEN[i-1] == 'U'|| FEN[i-1] == 'D'|| FEN[i-1] == 'T'|| FEN[i-1] == 'Q'|| FEN[i-1] == 'C')){
                
                if(IndMJ==0) {
                    nbBM = 0; 
                    if(FEN[i-1] != 'U') { //si le bonnus n'est pas un bonnus la bonne couleur
                        
                        if(FEN[i-1] == 'u' && IndBJ==0){*mJ = i-1;IndMJ=1;}

                        else if(FEN[i-1] == 'D' || FEN[i-1] == 'd'){
                            if(bR == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*mJ = i-1;IndMJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre
                        }
                        else if(FEN[i-1] == 'T' || FEN[i-1] == 't'){
                            if(bR == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*mJ = i-1;IndMJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'C' || FEN[i-1] == 'c'){
                            if(bR == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*mJ = i-1;IndMJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        else if(FEN[i-1] == 'Q' || FEN[i-1] == 'q'){
                            if(bR == (i-1)) {nbBM++;}
                            if(bJ == (i-1)) {nbBM++;}
                            if(mR == (i-1)) {nbBM++;}

                            if(nbBM <= 1) {*mJ = i-1;IndMJ=1;}       //vérifie si le nombre de bonus/malus est inférieur à la valeur de la lettre

                        }
                        
                        
                    } //prend uniquement le premier emplacement du bonnus rouge
               
                }

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
    #ifdef __DEBUG__
    fprintf(stdout, " \n FEN : %s \n", FEN);
    #endif
    if (FEN[i] == 'r' || FEN[i]=='R') *color = 2;                               //Si le dernier caractère est r alors la couleur est rouge
    if (FEN[i] == 'j' || FEN[i]=='J') *color = 1;                               //Si le dernier caractère est j alors la couleur est jaune
    
     
    
    
}
    

/* 
Nom de fonction : analyse
Principe de fonctionnement : Prend la chaine FEN en entré pour pouvoir modiffier la valeur du pointeur d'envoie 
Returne : rien
*/
void analyse(char* FEM, int mJ,int mR,int bJ,int bR, char envoi[8000]){
    int i=0, j=0, nb=0;
    int couleur=0, valeur=0, count=0;

    while(j<strlen(FEM) && count<=48){
        
        #ifdef __DEBUG__
        fprintf(stdout, " \n count : %d \n", count);
        #endif

        //Pour la couleur rouge 
        if(FEM[j] == 'u') {
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;

            strcat(envoi,"\t{\"nb\":");
            if (valeur == -1)  strcat(envoi,"-1");
            else if (valeur == 0)  strcat(envoi,"0");
            else if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'd') {
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 0)  strcat(envoi,"0");
            else if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 't') {
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'q') {
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            else if (valeur == 6)  strcat(envoi,"6");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'c') { 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            else if (valeur == 6)  strcat(envoi,"6");
            else if (valeur == 7)  strcat(envoi,"7");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"2");
            strcat(envoi,"},\n");
            count++;
        }

        //Pour la couleur jaoune
        else if(FEM[j] == 'U') {
            valeur = 1;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;

            strcat(envoi,"\t{\"nb\":");
            if (valeur == -1)  strcat(envoi,"-1");
            else if (valeur == 0)  strcat(envoi,"0");
            else if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'D') {
            valeur = 2;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 0)  strcat(envoi,"0");
            else if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'T') {
            valeur = 3;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 1)  strcat(envoi,"1");
            else if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'Q') {
            valeur = 4;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 2)  strcat(envoi,"2");
            else if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            else if (valeur == 6)  strcat(envoi,"6");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            count++;
        }
        else if(FEM[j] == 'C') { 
            valeur = 5;
            if (mJ == j) valeur = valeur - 1;
            if (mR == j) valeur = valeur - 1;
            if (bJ == j) valeur = valeur + 1;
            if (bR == j) valeur = valeur + 1;
            strcat(envoi,"\t{\"nb\":");
            if (valeur == 3)  strcat(envoi,"3");
            else if (valeur == 4)  strcat(envoi,"4");
            else if (valeur == 5)  strcat(envoi,"5");
            else if (valeur == 6)  strcat(envoi,"6");
            else if (valeur == 7)  strcat(envoi,"7");
            
            strcat(envoi,", \"couleur\":");
            strcat(envoi,"1");
            strcat(envoi,"},\n");
            count++;
        }

        //Pour vérifier le nombre de case vide 
        else if(FEM[j] >= '1' && FEM[j] <= '9' ){
            
            if (FEM[j+1] >= '1' && FEM[j+1] <= '9'){
                #ifdef __DEBUG__
                fprintf(stdout, " \n %s \n", "test 2 nombre");
                #endif
                nb = (FEM[j] - '0')*10 + (FEM[j+1] - '0');
                j++; count = count + nb;                                //augmentation du compteur de case (count) et du passeur au suivant (j)
                for(i=0;i<nb;i++) {
                    #ifdef __DEBUG__
                    fprintf(stdout, " \n %s \n", "Ligne envoyer !");
                    #endif
                    strcat(envoi,"\t{\"nb\":0, \"couleur\":0},\n");

                }
            }
            else {
                #ifdef __DEBUG__
                fprintf(stdout, " \n %s \n", "test 1 nombre");
                #endif

                nb = FEM[j] - '0';
                count = count + nb;

                for(i=0;i<nb;i++) {
                    #ifdef __DEBUG__
                    fprintf(stdout, " \n %s \n", "Ligne envoyer !");
                    #endif
                    strcat(envoi,"\t{\"nb\":0, \"couleur\":0},\n");
                }
            }
            
        }
        
        j++;
    }

    //#ifdef __DEBUG__
    fprintf(stdout, " \ncount : %d \n", count);
    fprintf(stdout, " \nnb : %d \n", nb);
    //#endif

    //Permet d'avoir toujours 48 cases d'afficher 
    if (count == 48) nb = 0;                //si le nombre de case déjà afficher est égale à 48, on affiche 0 case vide
    else if (count == 0) nb = 48;                //si le nombre de case déjà afficher est égale à 0, on affiche 48 case vide
    
    if (nb > 48) nb = 48 - count;           //si le nombre demandé de case vide est supérieur à 48, on affiche 48 cases vides moin le nombre de case déjà afficher
    else if (nb > (48 - count)) nb = 48 - count; //si le nombre demandé de case vide est supérieur à au nombre de case vide restant à afficher, on affiche 48 cases vides moins le nombre de case déjà afficher
    
    if ((nb + count) < 48) {nb = 48 - count;} //si le nombre de case déjà afficher plus le nombre de case vide demandé est inférieur à 48, on affiche 48 cases vides moin le nombre de case déjà afficher

    #ifdef __DEBUG__
    fprintf(stdout, " \n NB : %d \n", nb);
    strcat(envoi,"\t-----------------------------\n");          ///crée une séparation dans le fichier pour vérifier si le nombre de case est correct
    #endif

    for(i=0;i<nb;i++) strcat(envoi,"\t{\"nb\":0, \"couleur\":0},\n");         //permet d'affichier toute les casses vides
    
    envoi[strlen(envoi)-2] = '\0';                                          //Supprime la dernière virgule        
    strcat(envoi,"\n]\n});\n");                                             //Finalise le document                                                          
}
