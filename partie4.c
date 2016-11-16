#include <stdio.h>
#include <stdlib.h>
#include "final.h"

/*
*	fonction qui sauvegarde une partie en cours 
*	dans le fichier sauvegarde.txt
*	prend en compte un pointeur sur une partie
*/
int sauvegardePartie(partie * pa)
{

	int i=0,j=0;
	FILE * fi=fopen("sauvegarde.txt","wt");
	if (fi==NULL)
	{
		printf("erreur lors de l'opération de sauvegarde");
		return 0;
	}
	fprintf(fi,"joueur1 : %s\n",pa->nomJoueur1);
	fprintf(fi,"joueur2 : %s\n",pa->nomJoueur2);
	fprintf(fi,"tour : %d\n",pa->pionJoueurCourant);
	fprintf(fi,"taille : %d\n",pa->p->n);
	for(i=0;i < pa->p->n;i++)
	{
		for(j=0;j < pa->p->n;j++)
			fprintf(fi,"%d ",getCase(pa->p,i,j));
		printf("\n");	
	}
	fclose(fi);
	return 1;
}


/*
*	fonction qui charge les données du dossier sauvegarde.txt
*   
*/
partie * chargementPartie()
{
	int i=0,j=0,x;
	
	FILE * fo=fopen("sauvegarde.txt","rt");//ouverture dossier de sauvegarde
		if (fo==NULL)
	{
		printf("erreur lors de l'opération de chargement");
		return 0;
	}	

	partie *pa = malloc(sizeof(partie));//creation d'une partie
	if(pa == NULL)
	{
		printf("erreur de chargement , plus de place");
		return 0;
	}
	pa->p = malloc(sizeof(plateau));//creation d'un plateau
	if(pa->p == NULL)
	{
		printf("erreur d'allocation , plus de place");
		free(pa);
		pa=NULL;
		return 0;
	}
	
	fscanf(fo,"joueur1 : %s\n",pa->nomJoueur1);
	fscanf(fo,"joueur2 : %s\n",pa->nomJoueur2);
	fscanf(fo,"tour : %d\n",&pa->pionJoueurCourant);
	fscanf(fo,"taille : %d\n",&pa->p->n);

	pa->p->tableau= malloc((pa->p->n)*(pa->p->n)*sizeof(int)); // on alloue un tableau de taille n*n
	if(pa->p->tableau==NULL)
	{
		printf("erreur d'allocation , plus de place");
		free(pa->p);
		free(pa);
		pa->p=NULL;
		pa=NULL;
		return 0;
	}	



	for(i=0;i < pa->p->n;i++)
	{	
		for(j=0;j < pa->p->n;j++)
		{	
			fscanf(fo,"%d ",&x);
			setCase(pa->p,i,j,x);
		}
		printf("\n");
	}
	fclose(fo);
	return pa;
}


int menu(partie * pa)
{
	int choix=0;
	

	do
	{
		color_printf(RED,BLACK," __________________________________________ \n");
		delay(1);
		color_printf(RED,BLACK,"|");color_printf(BLUE,BLACK," 1 quitter le jeu                         ");color_printf(RED,BLACK,"|\n");
		delay(1);
		color_printf(RED,BLACK,"|");color_printf(BLUE,BLACK," 2 commencer une nouvelle partie          ");color_printf(RED,BLACK,"|\n");
		delay(1);
		color_printf(RED,BLACK,"|");color_printf(BLUE,BLACK," 3 charger la dernière partie sauvegardée ");color_printf(RED,BLACK,"|\n");
		delay(1);
		if (pa!=NULL)
		{
			color_printf(RED,BLACK,"|");color_printf(BLUE,BLACK," 4 sauvegarder votre partie               ");color_printf(RED,BLACK,"|\n");
			delay(1);
			color_printf(RED,BLACK,"|");color_printf(BLUE,BLACK," 5 reprendre votre partie                 ");color_printf(RED,BLACK,"|\n");
			delay(1);
		}
		color_printf(RED,BLACK,"|__________________________________________|\n");
			delay(2);
		scanf("%1d",&choix);
		choix--;
		 printf (" choix : %d \n ",choix);
	}while ( (choix > 5 || choix < 0 )  || (pa==NULL && choix >2) ); 
	return choix;
}


