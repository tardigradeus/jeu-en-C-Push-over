#include <stdio.h>
#include <stdlib.h>
#include "final.h"


//fonction qui ne m'appartient pas 
void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
} 

partie * creerPartie ()
{	
	int taille;
	partie *p1 = malloc(sizeof(partie));
	if(p1==NULL)
	{
		printf("erreur d'allocation , plus de place");
		exit(1);
	}
	printf("Nom du Premier Joueur ? ");
	scanf ("%126s", p1->nomJoueur1);
	viderBuffer();	
	printf("Nom du Second Joueur ? ");
	scanf ("%126s", p1->nomJoueur2);
	viderBuffer();
	do
	{	

		printf("qu'elle est la dimension du champ de bataille (2/8) ");
		scanf("%d", &(taille));

	}while(taille < 1 || taille > 8);
	
	p1->p = creerPlateau(taille);
	return p1;
}

void detruirePartie(partie * pa)
{
	detruirePlateau (pa->p);
	free(pa);
	pa = NULL;
}

void changePionCouleurCourant (partie * pa)
{
	if (pa->pionJoueurCourant == -1)
	{
		pa->pionJoueurCourant = 1;
	}
	else if (pa->pionJoueurCourant == 1)
	{
		pa->pionJoueurCourant = -1;
	}
}
	
int saisieJoueur(partie * pa, int * li, int * co, int * di, int * dj)
{
	char choix = 'a';
	int x = 0;
	int caseP;
		do
		{
			printf("Sur quel bord du plateau voulez-vous jouer ? (H/B/G/D) retourner au menu (m)\n");
			scanf("%s",&choix);

			if (choix == 'M' || choix == 'm')
			{
				return 0;
			}

			printf("Sur quelle case voulez vous vous placer ? (de 1 à %d)\n",pa->p->n);
			scanf("%d",&caseP); 
			caseP--;
			
			if ((choix == 'H' || choix == 'h') && caseValide(pa->p,0,caseP))
			{
				x = insertionPionPossible(pa->p,0,caseP,1,0,pa->pionJoueurCourant);
				*li = 0;
				*co=caseP;
				*di=1;
				*dj=0;
			}

			else if ((choix == 'B' || choix == 'b') && caseValide(pa->p,pa->p->n-1,caseP))
			{
				x = insertionPionPossible(pa->p,pa->p->n-1,caseP,-1,0,pa->pionJoueurCourant);
				*li = pa->p->n-1;
				*co = caseP;
				*di = -1;
				*dj = 0;
			}

			else if ((choix == 'G' || choix == 'g') && caseValide(pa->p,caseP,0))
			{
				x = insertionPionPossible(pa->p,caseP,0,0,1,pa->pionJoueurCourant);
				*li = caseP;
				*co = 0;
				*di = 0;
				*dj = 1;
			}

			else if ((choix == 'D' || choix == 'd' ) && caseValide(pa->p,caseP,pa->p->n-1))
			{
				x = insertionPionPossible(pa->p,caseP,pa->p->n-1,0,-1,pa->pionJoueurCourant);
				*li = caseP;
				*co = pa->p->n-1;
				*di = 0;
				*dj = -1;
			}
			else
			{
				x = 0;
			}
			
		} while ( x == 0);

	viderBuffer();
	return x;
}

void afficheNom(partie * pa)
{
	if (pa->pionJoueurCourant == 1)
	{
		printf("Le Joueur est %s\n",pa->nomJoueur1);
	}
	else if (pa->pionJoueurCourant == -1)
	{
		printf("Le Joueur est %s\n",pa->nomJoueur2);
	}
}

int tourJoueur (partie * pa)
{
	int x;
	int li=0,co=0,di=0,dj=0;
	affichage(pa->p);
	afficheNom(pa);
	x = saisieJoueur(pa,&li,&co,&di,&dj);
	if (x == 0)
	{
		return 0;
	}
	insertionPion(pa->p, li, co, di, dj, pa->pionJoueurCourant);
	return 1;
	
}


void afficheGagne(int x)
{
	if (x==1)
	{
		printf("       .__                                ____          .__        \n");     
		printf("______ |  | _____  ___.__. ___________   /_   | __  _  _|__| ____               \n");
		printf("\\____ \\|  | \\__  \\<   |  |/ __ \\_  __ \\   |   | \\ \\/ \\/ /  |/    \\    \n");
		printf("|  |_> >  |__/ __ \\\\___  \\  ___/|  | \\/   |   |  \\     /|  |   |  \\       \n");
		printf("|   __/|____(____  / ____|\\___  >__|      |___|   \\/\\_/ |__|___|  /	        \n");
		printf("|__|             \\/\\/         \\/                                \\/          \n");
	}
	else if (x==-1)
	{
		printf("       .__                              ________           .__               \n");         
		printf("______ |  | _____  ___.__. ___________  \\_____  \\  __  _  _|__| ____   ____     \n");
		printf("\\____ \\|  | \\__  \\<   |  |/ __ \\_  __ \\  /  ____/  \\ \\/ \\/ /  |/    \\ /    \\    \n");
		printf("|  |_> >  |__/ __ \\___  \\  ___/|  | \\/ /       \\   \\     /|  |   |  \\   |  \\	\n");
		printf("|   __/|____(____  / ____|\\___  >__|    \\_______ \\   \\/\\_/ |__|___|  /___|  /	\n");
		printf("|__|             \\/\\/         \\/                \\/                 \\/     \\/	\n");
	}
	else if(x==2)
	{
		printf("                 _       _                   _ _ \n");
		printf(" _ __ ___   __ _| |_ ___| |__    _ __  _   _| | |	   \n");
		printf("| '_ ` _ \\ / _` | __/ __| '_ \\  | '_ \\| | | | | |	   \n");
		printf("| | | | | | (_| | || (__| | | | | | | | |_| | | |	   \n");
		printf("|_| |_| |_|\\__,_|\\__\\___|_| |_| |_| |_|\\__,_|_|_|  \n");
	}
}



int jouer (partie * pa)
{
	int x=0;
	while ( x == 0)
	{
		x = tourJoueur(pa);
		if (x == 0)
		{
			return 0;
		}
		changePionCouleurCourant(pa);
		x = gagne(pa->p);	
		printf("x = %d",x);
		clear_terminal();
	}
	clear_terminal();

	if ( x == 2 )
	{
		afficheGagne(x);	
	}
	else if (x == 1)
	{
		afficheGagne(x);
	}
	else if (x == -1)
	{
		afficheGagne(x);
	}
		
	affichage(pa->p);
	return 1;
}

/*int main()
{
	
	partie * p1;
	p1 = creerPartie();
	p1->pionJoueurCourant = 1;	
	jouer(p1);
	sauvegardePartie(p1);
	detruirePartie(p1);
	return 0;
}
*/
