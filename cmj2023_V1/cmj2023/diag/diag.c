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




void main{
    char FEN = chaineFEN();
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

void EcritBasique(char chaine){
    FILE *fic = fopen("teste.js", "w+");
    fprintf("teste.js", "traiterJson({\n
        \"trait\":2,\n
        \"numDiag\":2,\n
        \"notes\": \"Une position à nombre de pièces réduit. Ici, pour gagner, les rouges jouent 4->0. Pour ne pas faire apparaître de pions évolution, il suffit de les affecter par paires bonus/malus aux mêmes colonnes\",\n
        \"fen\": \"%s\",\n
        \"bonusJ\":0,\n
        \"malusJ\":2,\n
        \"bonusR\":1,\n
        \"malusR\":1,\n
        ", chaine);
    fclose("teste.js");
}

void EcritModification(char FENin){
    char writing[1653] = analyse(FENin);
    FILE *fic = fopen("teste.js", "a+");
    fprintf("teste.js", "%s", writing);
    fclose("teste.js");
}
void analyse(char chaine){
    int i=0, j;
    int couleur=0, valeur=0;
    char implementation[28] = "\a{\"nb\":0, \"couleur\":0},\n"
    for(j=0;j<strlen(chaine);j++){
        if(chaine[j] = 'u') {
            couleur = 2; 
            valeur = 1;
            if(chaine[j+1] = 'B' || chaine[j+1] = 'b'){
                valeur++;

                if(chaine[j+2] = 'B' || chaine[j+1] = 'b'){
                    valeur++;
                    if(chaine[j+3] = 'B' || chaine[j+1] = 'b'){
                        valeur++;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    
                    if(chaine[j+3] = 'M' || chaine[j+1] = 'm'){
                        valeur--;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    }

                if(chaine[j+2] = 'M' || chaine[j+1] = 'm'){valeur--
                    if(chaine[j+3] = 'B' || chaine[j+1] = 'b'){
                        valeur++;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    
                    if(chaine[j+3] = 'M' || chaine[j+1] = 'm'){
                        valeur--;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                };
            }
            if(chaine[j+1] = 'M' || chaine[j+1] = 'm'){valeur--;
                if(chaine[j+2] = 'B' || chaine[j+1] = 'b'){
                    valeur++;
                    if(chaine[j+3] = 'B' || chaine[j+1] = 'b'){
                        valeur++;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    
                    if(chaine[j+3] = 'M' || chaine[j+1] = 'm'){
                        valeur--;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    }

                if(chaine[j+2] = 'M' || chaine[j+1] = 'm'){valeur--
                    if(chaine[j+3] = 'B' || chaine[j+1] = 'b'){
                        valeur++;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                    
                    if(chaine[j+3] = 'M' || chaine[j+1] = 'm'){
                        valeur--;
                        if(chaine[j+4] = 'B' || chaine[j+1] = 'b')valeur++;
                        if(chaine[j+4] = 'M' || chaine[j+1] = 'm')valeur--;
                        }
                };
            }
 
            // Trouvé comment modifier une chaine de char et simplifier au niveau des if max 2. 
            strcat(chaine,implementation);
        }
        /* A modifier comme si dessus !
        if(chaine[j] = 'd') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 't') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'q') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'c') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");

        if(chaine[j] = 'U') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'D') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'T') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'Q') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        if(chaine[j] = 'C') strcat(chaine,"\a{\"nb\":1, \"couleur\":2},\n");
        */
        
    }

    for(i;i<nb;i++) strcat(chaine,"\a{\"nb\":0, \"couleur\":0},\n");    //permet d'affichier toute les casses vides
    
    strcat(chaine,"]\n });\n")
}