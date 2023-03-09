#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "topologie.h"
#include <string.h>


//Déclaration des variables globales

char* JJ = "rouge";
char* JR = "jaune";
char Joueur[5];
char nom[NBCASES];
int Alternance = 1;
T_Position p;
T_ListeCoups l;
T_Score score;
T_Coup coups;
octet valide;
int positionRouge[24] = {0,2,4,7,9,11,12,14,16,18,20,22,25,27,29,31,33,35,36,38,40,43,45,47};
int positionJaune[24] = {1,3,5,6,8,10,13,15,17,19,21,23,24,26,28,30,32,34,37,39,41,42,44,46};


//Prototypes des fonctions

void placementBonus();
void enJeu();
void haveJson(char* nom ,T_Position p, T_Score score);
void gagnant(T_Score score);


//Fonction principale

int main( int argc, char *argv[] ){

    //Determinations du nom du fichier
	if (argc>2){
		printf("trops d'arguments entrés\n");
		return 0;
	}

	//nom de fichier par défaut
	else if (argc==1) strcpy(nom,"fic.js");

	//nom de fichier en argument
	else strcpy(nom,argv[1]);

	printf("On utilise le fichier : %s\n\n",nom); 

    //Placement des bonus
    placementBonus();

    //On détermine la position initiale
    p = getPositionInitiale();

    //On joue le jeu
    enJeu();

    //On affiche le gagnant
    gagnant(score);

    //Fin du jeu
    printf("fin du jeu");
    return 0;
    }


//Fonctions :


//Fonction qui permet de placer les bonus

void placementBonus(){
    int i = 0;


    //Placement du bonus jaune
    do{
        printf("\nOù voulez-vous placer le bonus jaune :");
        scanf("%hhd",&p.evolution.bonusJ); 
        getchar();
    }while(p.evolution.bonusJ != positionJaune[0] && p.evolution.bonusJ != positionJaune[1] && p.evolution.bonusJ != positionJaune[2] && p.evolution.bonusJ != positionJaune[3] && p.evolution.bonusJ != positionJaune[4] && p.evolution.bonusJ != positionJaune[5] && p.evolution.bonusJ != positionJaune[6] && p.evolution.bonusJ != positionJaune[7] && p.evolution.bonusJ != positionJaune[8] && p.evolution.bonusJ != positionJaune[9] && p.evolution.bonusJ != positionJaune[10] && p.evolution.bonusJ != positionJaune[11] && p.evolution.bonusJ != positionJaune[12] && p.evolution.bonusJ != positionJaune[13] && p.evolution.bonusJ != positionJaune[14] && p.evolution.bonusJ != positionJaune[15] && p.evolution.bonusJ != positionJaune[16] && p.evolution.bonusJ != positionJaune[17] && p.evolution.bonusJ != positionJaune[18] && p.evolution.bonusJ != positionJaune[19] && p.evolution.bonusJ != positionJaune[20] && p.evolution.bonusJ != positionJaune[21] && p.evolution.bonusJ != positionJaune[22] && p.evolution.bonusJ != positionJaune[23]); 
    printf("Placement du bonus jaune en %hhd réussi !!!\n\n",p.evolution.bonusJ);
    haveJson(nom,p,score);

    //Placement du bonus rouge
    do{
    printf("\nOù voulez-vous placer le bonus rouge : ");
    scanf("%hhd",&p.evolution.bonusR);
    getchar();
    }while(p.evolution.bonusR != positionRouge[0] && p.evolution.bonusR != positionRouge[1] && p.evolution.bonusR != positionRouge[2] && p.evolution.bonusR != positionRouge[3] && p.evolution.bonusR != positionRouge[4] && p.evolution.bonusR != positionRouge[5] && p.evolution.bonusR != positionRouge[6] && p.evolution.bonusR != positionRouge[7] && p.evolution.bonusR != positionRouge[8] && p.evolution.bonusR != positionRouge[9] && p.evolution.bonusR != positionRouge[10] && p.evolution.bonusR != positionRouge[11] && p.evolution.bonusR != positionRouge[12] && p.evolution.bonusR != positionRouge[13] && p.evolution.bonusR != positionRouge[14] && p.evolution.bonusR != positionRouge[15] && p.evolution.bonusR != positionRouge[16] && p.evolution.bonusR != positionRouge[17] && p.evolution.bonusR != positionRouge[18] && p.evolution.bonusR != positionRouge[19] && p.evolution.bonusR != positionRouge[20] && p.evolution.bonusR != positionRouge[21] && p.evolution.bonusR != positionRouge[22] && p.evolution.bonusR != positionRouge[23]);
    
    printf("Placement du bonus rouge en %hhd réussi !!!\n\n",p.evolution.bonusR);
    haveJson(nom,p,score);

    //Placement du malus jaune
    do{
    printf("\nOù voulez-vous placer le malus jaune : ");
    scanf("%hhd",&p.evolution.malusJ);
    getchar();
    }while(p.evolution.malusJ != positionJaune[0] && p.evolution.malusJ != positionJaune[1] && p.evolution.malusJ != positionJaune[2] && p.evolution.malusJ != positionJaune[3] && p.evolution.malusJ != positionJaune[4] && p.evolution.malusJ != positionJaune[5] && p.evolution.malusJ != positionJaune[6] && p.evolution.malusJ != positionJaune[7] && p.evolution.malusJ != positionJaune[8] && p.evolution.malusJ != positionJaune[9] && p.evolution.malusJ != positionJaune[10] && p.evolution.malusJ != positionJaune[11] && p.evolution.malusJ != positionJaune[12] && p.evolution.malusJ != positionJaune[13] && p.evolution.malusJ != positionJaune[14] && p.evolution.malusJ != positionJaune[15] && p.evolution.malusJ != positionJaune[16] && p.evolution.malusJ != positionJaune[17] && p.evolution.malusJ != positionJaune[18] && p.evolution.malusJ != positionJaune[19] && p.evolution.malusJ != positionJaune[20] && p.evolution.malusJ != positionJaune[21] && p.evolution.malusJ != positionJaune[22] && p.evolution.malusJ != positionJaune[23]);
    
    printf("Placement du malus jaune en %hhd réussi !!!\n\n" ,p.evolution.malusJ);
    haveJson(nom,p,score);
    
    //Placement du malus rouge
    do{
    printf("\nOù voulez-vous placer le malus rouge : ");
    scanf("%hhd",&p.evolution.malusR);
    getchar();
    }while(p.evolution.malusR != positionRouge[0] && p.evolution.malusR != positionRouge[1] && p.evolution.malusR != positionRouge[2] && p.evolution.malusR != positionRouge[3] && p.evolution.malusR != positionRouge[4] && p.evolution.malusR != positionRouge[5] && p.evolution.malusR != positionRouge[6] && p.evolution.malusR != positionRouge[7] && p.evolution.malusR != positionRouge[8] && p.evolution.malusR != positionRouge[9] && p.evolution.malusR != positionRouge[10] && p.evolution.malusR != positionRouge[11] && p.evolution.malusR != positionRouge[12] && p.evolution.malusR != positionRouge[13] && p.evolution.malusR != positionRouge[14] && p.evolution.malusR != positionRouge[15] && p.evolution.malusR != positionRouge[16] && p.evolution.malusR != positionRouge[17] && p.evolution.malusR != positionRouge[18] && p.evolution.malusR != positionRouge[19] && p.evolution.malusR != positionRouge[20] && p.evolution.malusR != positionRouge[21] && p.evolution.malusR != positionRouge[22] && p.evolution.malusR != positionRouge[23]);
    
    printf("Placement du malus rouge en %hhd réussi !!!\n\n",p.evolution.malusR);
    haveJson(nom,p,score);

    //Vérification que les bonus et malus ne sont pas sur la même case
    if (p.evolution.bonusJ == p.evolution.malusJ || p.evolution.bonusR == p.evolution.malusR){
        printf("\nVous avez placé un bonus et un malus sur la même case, recommencez !\n\n");
        placementBonus();
    }
    else{
        printf("\nPlacement des bonus et malus réussi !!!\n\n");
    }

}


//fonction qui permet de jouer un coup

void enJeu(){
    do{
        
        if ((Alternance % 2) == 0) {strcpy(Joueur,JR);}       // fait alterner le nom du joueur
        else {strcpy(Joueur,JJ);}

        do{
        printf("Au %s de jouer : ", Joueur);                //annonce le tour du joueur en alternant

        
        //demande de saisie des coordonnées du pion à déplacer
        printf("Donnez la position du pion a déplacer :");  
        scanf("%hhd",&coups.origine);


        //demande de saisie des coordonnées de la case d'arrivée
        printf("Donnez la position de la case d'arrivée :");
        scanf("%hhd",&coups.destination);
        
        }while(estValide(p , coups.origine, coups.destination) != VRAI);        //vérifie que le coup est valide
        
        p = jouerCoup(p, coups.origine, coups.destination);
        l = getCoupsLegaux(p);

        //mis à jour du score
        score = evaluerScore(p);
        afficherScore(score);

        //mise à jour du fichier json
        haveJson(nom,p,score);

        Alternance++;                                       //variable qui permet d'alterner
    }while(l.nb != 0);
}


//fonction qui permet d'écrire dans le fichier js

void haveJson(char* nom, T_Position pos, T_Score score){

    //déclaration des variables
	FILE *file = NULL;
	int i;

	//ouverture du fichier en mode écriture
	file = fopen(nom,"w"); 

	//écriture des scores
	fprintf(file,"traiterJson({\n%s:%d, \n%s:%d, \n%s:%d, \n%s:%d,\n%s:%d, \n",STR_TURN,pos.trait,STR_SCORE_J,score.nbJ,STR_SCORE_J5,score.nbJ5,STR_SCORE_R,score.nbR,STR_SCORE_R5,score.nbR5);
		
	//écriture des malus et des bonus
	fprintf(file,"%s:%d, \n%s:%d, \n%s:%d, \n%s:%d,\n%s:[",STR_BONUS_J,pos.evolution.bonusJ,STR_MALUS_J,pos.evolution.malusJ,STR_BONUS_R,pos.evolution.bonusR,STR_MALUS_R,pos.evolution.malusR,STR_COLS);
    
	
    //écriture des positions des pions
	for(i=0;i<NBCASES-1;i++){
		fprintf(file,"\n\t{%s:%d, %s:%d},",STR_NB,pos.cols[i].nb,STR_COULEUR,pos.cols[i].couleur);
	}
	fprintf(file,"\n\t{%s:%d, %s:%d}\n]\n});",STR_NB,pos.cols[NBCASES-1].nb,STR_COULEUR,pos.cols[NBCASES-1].couleur);	

    //fermeture du fichier
	fclose(file);
    
}


//fonction qui permet de déterminer le gagnant

void gagnant(T_Score score){

    //les rouges gagnent si le score rouge est plus élevé
    if (score.nbR > score.nbJ) printf("Les rouges ont gagné\n"); 
	else
	{
		
		//les jaunes gagnent si le score jaune est plus élevé
		if(score.nbJ > score.nbR) printf("Les jaunes ont gagné\n");

		else 
		{
			//Si égalité : les jaunes gagnent si les jaunes ont plus de tours de 5
			if (score.nbJ5 > score.nbR5)	printf("Les jaunes ont gagné: ils ont le plus de tours de 5\n");

			//Si égalité : les rouges gagnent si les rouges ont plus de tours de 5
			else printf("Les rouges ont gagné: ils ont le plus de tours de 5\n");
		}
	}
}