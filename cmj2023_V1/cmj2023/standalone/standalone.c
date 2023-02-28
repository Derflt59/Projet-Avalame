#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "topologie.h"
#include <string.h>


char* JJ = "rouge";
char* JR = "jaune";
char Joueur[5];
int Alternance = 1;
int positionRouge[24] = {0,2,4,7,9,11,12,14,16,18,20,22,25,27,29,31,33,35,36,38,40,43,45,47};
int positionJaune[24] = {1,3,5,6,8,10,13,15,17,19,21,23,24,26,28,30,32,34,37,39,41,42,44,46};

void placementBonus();
void enJeu();
void refresh();
void traiterJson(char *json);
void getJson();


int main(){
    refresh();
    placementBonus();
    enJeu();
    return 0;
    }


void placementBonus(){
    T_Position p = getPositionInitiale();
    do{
    printf("\nOù voulez-vous placer le bonus jaune :");
    scanf("%hhd",&p.evolution.bonusJ); 
    getchar();
    }while(p.evolution.bonusJ != positionJaune[0] && p.evolution.bonusJ != positionJaune[1] && p.evolution.bonusJ != positionJaune[2] && p.evolution.bonusJ != positionJaune[3] && p.evolution.bonusJ != positionJaune[4] && p.evolution.bonusJ != positionJaune[5] && p.evolution.bonusJ != positionJaune[6] && p.evolution.bonusJ != positionJaune[7] && p.evolution.bonusJ != positionJaune[8] && p.evolution.bonusJ != positionJaune[9] && p.evolution.bonusJ != positionJaune[10] && p.evolution.bonusJ != positionJaune[11] && p.evolution.bonusJ != positionJaune[12] && p.evolution.bonusJ != positionJaune[13] && p.evolution.bonusJ != positionJaune[14] && p.evolution.bonusJ != positionJaune[15] && p.evolution.bonusJ != positionJaune[16] && p.evolution.bonusJ != positionJaune[17] && p.evolution.bonusJ != positionJaune[18] && p.evolution.bonusJ != positionJaune[19] && p.evolution.bonusJ != positionJaune[20] && p.evolution.bonusJ != positionJaune[21] && p.evolution.bonusJ != positionJaune[22] && p.evolution.bonusJ != positionJaune[23]);
    printf("Placement du bonus jaune en %hhd réussi !!!\n\n",p.evolution.bonusJ);

    do{
    printf("\nOù voulez-vous placer le bonus rouge : ");
    scanf("%hhd",&p.evolution.bonusR);
    getchar();
    }while(p.evolution.bonusR != positionRouge[0] && p.evolution.bonusR != positionRouge[1] && p.evolution.bonusR != positionRouge[2] && p.evolution.bonusR != positionRouge[3] && p.evolution.bonusR != positionRouge[4] && p.evolution.bonusR != positionRouge[5] && p.evolution.bonusR != positionRouge[6] && p.evolution.bonusR != positionRouge[7] && p.evolution.bonusR != positionRouge[8] && p.evolution.bonusR != positionRouge[9] && p.evolution.bonusR != positionRouge[10] && p.evolution.bonusR != positionRouge[11] && p.evolution.bonusR != positionRouge[12] && p.evolution.bonusR != positionRouge[13] && p.evolution.bonusR != positionRouge[14] && p.evolution.bonusR != positionRouge[15] && p.evolution.bonusR != positionRouge[16] && p.evolution.bonusR != positionRouge[17] && p.evolution.bonusR != positionRouge[18] && p.evolution.bonusR != positionRouge[19] && p.evolution.bonusR != positionRouge[20] && p.evolution.bonusR != positionRouge[21] && p.evolution.bonusR != positionRouge[22] && p.evolution.bonusR != positionRouge[23]);
    printf("Placement du bonus rouge en %hhd réussi !!!\n\n",p.evolution.bonusR);

    do{
    printf("\nOù voulez-vous placer le malus jaune : ");
    scanf("%hhd",&p.evolution.malusJ);
    getchar();
    }while(p.evolution.malusJ != positionJaune[0] && p.evolution.malusJ != positionJaune[1] && p.evolution.malusJ != positionJaune[2] && p.evolution.malusJ != positionJaune[3] && p.evolution.malusJ != positionJaune[4] && p.evolution.malusJ != positionJaune[5] && p.evolution.malusJ != positionJaune[6] && p.evolution.malusJ != positionJaune[7] && p.evolution.malusJ != positionJaune[8] && p.evolution.malusJ != positionJaune[9] && p.evolution.malusJ != positionJaune[10] && p.evolution.malusJ != positionJaune[11] && p.evolution.malusJ != positionJaune[12] && p.evolution.malusJ != positionJaune[13] && p.evolution.malusJ != positionJaune[14] && p.evolution.malusJ != positionJaune[15] && p.evolution.malusJ != positionJaune[16] && p.evolution.malusJ != positionJaune[17] && p.evolution.malusJ != positionJaune[18] && p.evolution.malusJ != positionJaune[19] && p.evolution.malusJ != positionJaune[20] && p.evolution.malusJ != positionJaune[21] && p.evolution.malusJ != positionJaune[22] && p.evolution.malusJ != positionJaune[23]);
    printf("Placement du malus jaune en %hhd réussi !!!\n\n" ,p.evolution.malusJ);
    
    do{
    printf("\nOù voulez-vous placer le malus rouge : ");
    scanf("%hhd",&p.evolution.malusR);
    getchar();
    }while(p.evolution.malusR != positionRouge[0] && p.evolution.malusR != positionRouge[1] && p.evolution.malusR != positionRouge[2] && p.evolution.malusR != positionRouge[3] && p.evolution.malusR != positionRouge[4] && p.evolution.malusR != positionRouge[5] && p.evolution.malusR != positionRouge[6] && p.evolution.malusR != positionRouge[7] && p.evolution.malusR != positionRouge[8] && p.evolution.malusR != positionRouge[9] && p.evolution.malusR != positionRouge[10] && p.evolution.malusR != positionRouge[11] && p.evolution.malusR != positionRouge[12] && p.evolution.malusR != positionRouge[13] && p.evolution.malusR != positionRouge[14] && p.evolution.malusR != positionRouge[15] && p.evolution.malusR != positionRouge[16] && p.evolution.malusR != positionRouge[17] && p.evolution.malusR != positionRouge[18] && p.evolution.malusR != positionRouge[19] && p.evolution.malusR != positionRouge[20] && p.evolution.malusR != positionRouge[21] && p.evolution.malusR != positionRouge[22] && p.evolution.malusR != positionRouge[23]);
    printf("Placement du malus rouge en %hhd réussi !!!\n\n",p.evolution.malusR);

    if (p.evolution.bonusJ == p.evolution.malusJ || p.evolution.bonusR == p.evolution.malusR){
        printf("\nVous avez placé un bonus et un malus sur la même case, recommencez !\n\n");
        placementBonus();
    }
    else{
        printf("\nPlacement des bonus et malus réussi !!!\n\n");
    }
}

void enJeu(){
    T_Position p = getPositionInitiale();
    int depart, arrivee;
    T_ListeCoups w; 
    w = getCoupsLegaux(p) ; 
    while(w.nb!= 0){
        
        if ((Alternance % 2) == 0) {strcpy(Joueur,JR);}       // fait alterner le nom du joueur
        else {strcpy(Joueur,JJ);}

        do{
        printf("Au %s de jouer : ", Joueur);                //annonce le tour du joueur en altenant

        printf("Donnez la position du pion a déplacer :");  
        scanf("%d",&depart);


        printf("Donnez la position de la case d'arrivée :");
        scanf("%d",&arrivee);
        
        }while(depart < 0 || depart > 63 || arrivee < 0 || arrivee > 63 || estValide(p , depart, arrivee) != VRAI);
        
        jouerCoup(p,depart,arrivee);
        refresh();
        afficherPosition(p);

        Alternance++;                                       //variable qui permet d'altener
    }
}
    

void refresh(){
    T_Position p = getPositionInitiale();
    int pion = 0;
    FILE *fic = fopen("refresh.js", "w+");
    if(fic==NULL) exit(1);
    fprintf(fic, "var pion = %d;", pion);
    fclose(fic);
    afficherScore(evaluerScore(p)); 
}
void traiterJson(char *json){
    T_Position p = getPositionInitiale();
    int depart, arrivee;
    T_ListeCoups w; 
    w = getCoupsLegaux(p) ; 
    depart = json[0];
    arrivee = json[1];
    if(depart < 0 || depart > 63 || arrivee < 0 || arrivee > 63 || estValide(p , depart, arrivee) != VRAI){
        printf("Coup non valide");
    }
    else{
        jouerCoup(p,depart,arrivee);
        refresh();
        afficherPosition(p);
    }
}



void getJson(){
    FILE *fic = fopen("refresh.js", "r");
    if(fic==NULL) exit(1);
    char json[2];
    fscanf(fic, "var pion = %s;", &json[0]);
    fclose(fic);
    traiterJson(json);
}
