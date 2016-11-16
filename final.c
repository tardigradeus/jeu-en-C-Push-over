#include<stdio.h>
#include<stdlib.h>
#include<assert.h> //inclue la bibliotèque qui permet l'utilisation de assert()
#include "final.h"
#include<time.h>
#include <unistd.h> 

void delay(int n)
{
	int i=0;
	int a=1;
	for(i=0;i<n*100000000;i++)
	{
	a=1+i;	
	}
}

int main ()
{
printf("Bienvenue... \n");
sleep(1);
printf("Sur... \n");
sleep(1);
printf(" _______  __   __           __   __     _______  __   __           _____   \n"); 
delay(1);
printf("|   _   ||  | |  | _______ |  | |  |   |       ||  | |  | _______ |   _ |  \n");
delay(1);
printf("|  |_|  ||  | |  ||  _____||  |_|  |   |   _   ||  |_|  ||    ___||  | ||  \n");
delay(1);
printf("|       ||  |_|  || |_____ |       |   |  | |  ||       ||   |___ |  |_||_ \n");
delay(1);
printf("|    ___||       ||_____  ||   _   |   |  |_|  ||       ||    ___||   __  |\n");
delay(1);
printf("|   |    |_______| _____| ||  | |  |   |       | |     | |   |___ |  |  | |\n");
delay(1);
printf("|___|             |_______||__| |__|   |_______|  |___|  |_______||__|  |_|\n\n ");
delay(1);
 
	printf("entrer la taille du plateau de jeu (entre 2 et 8 ) : ");
	srand(time(NULL));
	int n=0;
	
	scanf("%d",&n);
	plateau *pl;
	pl=creerPlateau(n);//on recois un type tableau initialisé
	//initialisation de quelque valeur pour des tests
	/*
	int aleat;
	int nbr=0;
	for (nbr=0;nbr<pl->n*pl->n;nbr++)
	{
		aleat=rand()%2;
		if (aleat==1)
			*(pl->tableau+nbr)=1;
		else
			*(pl->tableau+nbr)=-1;
	}*/
	
	/*
	*(pl->tableau)=1;
	*(pl->tableau+10)=-1;
	*(pl->tableau+17)=-1;
	*(pl->tableau+3)=1;
	*(pl->tableau+4)=1;
	*(pl->tableau+9)=1;
	*(pl->tableau+14)=1;
	*(pl->tableau+19)=1;
	*(pl->tableau+24)=1;
	*(pl->tableau+20)=-1;
	*(pl->tableau+4)=1;
	*/
	
	int i ,j;
	printf("entrer x = : ");
	scanf("%d",&i);
	printf("\n");
	printf("entrer y = : ");
	scanf("%d",&j);
	printf("\n");
	printf("la valeur de la case (%d,%d) est : %d \n",i,j,getCase(pl,i,j) );

	printf("coordonner de la case a changer \n");
	printf("i = : ");
	scanf("%d",&i);
	printf("\nj = : ");
	scanf("%d",&j);
	printf("\nvaleur de la case a changer : ");
	int val;
	scanf("%d",&val);
	setCase(pl,i,j,val);



	affichage(pl);

	/*
	parcour le tableau pour voir toute les coordonées
	int a,b;
	for (a=0;a<=i;a++)
	{
		for(b=0;b<=j;b++)
		{
		printf("la valeur de la case (%d,%d) est : %d \n",a,b,getCase(&pl,a,b) );
		}
	}
	*/
	printf("debut des test de la deuxième partie\n");
		
	printf("l'indice de valeur 5 retourne : %d\n",indiceValide(pl,5));
	printf("l'indice de valeur 9 retourne : %d\n",indiceValide(pl,9));
	printf("l'indice de valeur 2 retourne : %d\n",indiceValide(pl,2));
	printf("l'indice de valeur 6 retourne : %d\n",indiceValide(pl,6));
	printf("l'indice de valeur 0 retourne : %d\n",indiceValide(pl,0));
	printf("----------------------------------\n");
	printf("la case 1,2 retourne : %d\n",caseValide(pl,1,2));
	printf("la case 4,1 retourne : %d\n",caseValide(pl,4,1));
	printf("la case 5,0 retourne : %d\n",caseValide(pl,5,0));
	printf("la case 6,3 retourne : %d\n",caseValide(pl,6,3));
	printf("la case 0,0 retourne : %d\n",caseValide(pl,0,0));
	printf("---------------------------------\n");
	printf("la case 0,0 retourne : %d\n",caseVide(pl,0,0));
	printf("la case 0,4 retourne : %d\n",caseVide(pl,0,4));
	printf("la case 3,2 retourne : %d\n",caseVide(pl,3,2));
	printf("la case 4,4 retourne : %d\n",caseVide(pl,4,4));
	printf("la case 6,3 retourne : %d\n",caseVide(pl,6,3));
	printf("---------------------------------\n");
	printf("la case 0.4 retourne avec di = 1 et dj = 0 : %d\n",directPossible(pl,0,4,1,0));
	printf("la case 0.4 retourne avec di = -1 et dj = 0 : %d\n",directPossible(pl,0,4,-1,0));
	printf("la case 0.4 retourne avec di = 0 et dj = 1 : %d\n",directPossible(pl,0,4,0,1));
	printf("la case 0.4 retourne avec di = 0 et dj = -1 : %d\n\n",directPossible(pl,0,4,0,-1));
	printf("la case 3.0 retourne avec di = 1 et dj = 0 : %d\n",directPossible(pl,3,0,1,0));
	printf("la case 3.0 retourne avec di = -1 et dj = 0 : %d\n",directPossible(pl,3,0,-1,0));
	printf("la case 3.0 retourne avec di = 0 et dj = 1 : %d\n",directPossible(pl,3,0,0,1));
	printf("la case 3.0 retourne avec di = 0 et dj = -1 : %d\n\n",directPossible(pl,3,0,0,-1));
	printf("la case 4.0 retourne avec di = 1 et dj = 0 : %d\n",directPossible(pl,4,0,1,0));
	printf("la case 4.0 retourne avec di = -1 et dj = 0 : %d\n",directPossible(pl,4,0,-1,0));
	printf("la case 4.0 retourne avec di = 0 et dj = 1 : %d\n",directPossible(pl,4,0,0,1));
	printf("la case 4.0 retourne avec di = 0 et dj = -1 : %d\n",directPossible(pl,4,0,0,-1));
	printf("la case 0.0 retourne avec di = 0 et dj = -1 : %d\n",directPossible(pl,0,0,0,-1));
	printf("la case 4.4 retourne avec di = 0 et dj = 1 : %d\n",directPossible(pl,4,4,0,1));
	printf("---------------------------------\n");
	printf("la valeur de la case 0.0 est : %d\n",valeurCase(pl,0,0,0,1)); 
	printf("la valeur de la case 1.0 est : %d\n",valeurCase(pl,1,0,0,1));
	printf("la valeur de la case 2.0 est : %d\n",valeurCase(pl,2,0,0,1));
	printf("la valeur de la case 3.0 est : %d\n",valeurCase(pl,3,0,0,1));
	printf("la valeur de la case 4.0 est : %d\n\n",valeurCase(pl,4,0,0,1));
	printf("la valeur de la case 0.0 est : %d\n",valeurCase(pl,0,0,1,0));
	printf("la valeur de la case 0.1 est : %d\n",valeurCase(pl,0,1,1,0));
	printf("la valeur de la case 0.2 est : %d\n",valeurCase(pl,0,2,1,0));
	printf("la valeur de la case 0.3 est : %d\n",valeurCase(pl,0,3,1,0));
	printf("la valeur de la case 0.4 est : %d\n\n",valeurCase(pl,0,4,1,0));
	printf("la valeur de la case 4.0 est : %d\n",valeurCase(pl,4,0,-1,0));
	printf("la valeur de la case 4.1 est : %d\n",valeurCase(pl,4,1,-1,0));
	printf("la valeur de la case 4.2 est : %d\n",valeurCase(pl,4,2,-1,0));
	printf("la valeur de la case 4.3 est : %d\n",valeurCase(pl,4,3,-1,0));
	printf("la valeur de la case 4.4 est : %d\n\n",valeurCase(pl,4,4,-1,0));
	printf("la valeur de la case 0.4 est : %d\n",valeurCase(pl,0,4,0,-1));
	printf("la valeur de la case 1.4 est : %d\n",valeurCase(pl,1,4,0,-1));
	printf("la valeur de la case 2.4 est : %d\n",valeurCase(pl,2,4,0,-1));
	printf("la valeur de la case 3.4 est : %d\n",valeurCase(pl,3,4,0,-1));
	printf("la valeur de la case 4.4 est : %d\n",valeurCase(pl,4,4,0,-1));
	printf("---------------------------------\n");
	int choix=1,x,y,di,dj,pion ;
	
	while (choix == 1)
	{
		printf("coordonées d'une insertion :\n");
		printf("x= ");
		scanf("%d",&x);
		printf("y= ");
		scanf("%d",&y);
		printf("direction de l'insertion :\n");
		printf("di= ");
		scanf("%d",&di);
		printf("dj= ");
		scanf("%d",&dj);
		printf("couleur de votre pion : ");
		scanf("%d",&pion);
		insertionPion(pl,x,y,di,dj,pion);
		affichage(pl);
		printf("refaire une insertion ? :");
		scanf("%d",&choix); 

	}

	
	
	detruirePlateau(pl);

	return 0;
}

