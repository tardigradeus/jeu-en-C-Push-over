#include<stdio.h>
#include<stdlib.h>
#include<assert.h> //inclue la bibliotèque qui permet l'utilisation de assert()
#include "final.h"

void clear_terminal()
{
  printf("\033[2J");
  printf("\033[0;0H");
}

//fonction qui fait attendre un certain temps
void delay(int n)
{
	int i,x;
	for(i=0 ; i<50000000*n ;i++)
		x++;
}


int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...)
{
  int res;
  va_list args;
  printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
  va_start(args, format);
  res = vprintf(format, args);
  va_end(args);
  printf("\x1B[00m");
  return res;
}


plateau *creerPlateau(int taille){
	int i;
	plateau *pl = malloc(sizeof(plateau));
	if (pl == NULL)
	{
		printf("erreur d'allocation , plus de place");
		exit(1);
	}
	
	assert(taille <= 8 && taille >= 2); //envoie un message d'erreur si n n'est pas compri entre 3 et 8 inclus

	(pl->n)=taille;
	(*pl).tableau= malloc((pl->n)*(pl->n)*sizeof(int)); // on alloue un tableau de taille n*n
	if(pl==NULL)
	{
		printf("erreur d'allocation , plus de place");
		exit(1);
	}
	if ((*pl).tableau == NULL)//on verifie que le tableau a bien été aloué
	{
		printf("le pointeur n'a rien reçu désolé");
		exit(1);
	}
	for (i=0 ; i < pl->n*pl->n ; i++ )//on met toute les valeurs du tableau a zero
	{
		*(pl->tableau+i)=0;
	}	
	return pl;//on renvois pl
}

//fonction qui detruit le plateau prend en paramètre un pointeur de type plateau
void detruirePlateau(plateau * p)
{
	assert(p->tableau!=NULL);//verifie que le le plateau contient bien un pointeur sur un tableau
	free(p->tableau);//libere le tableau allouer par malloc plus haut
	free(p);
	p->tableau=NULL;//met le pointeur du tableau a zero
	p->n=0;//et met la taille a zero
}

void afficheLigneIntermediaire(plateau *pl,int l)
{
	int i ;
	if(l%2==0)//regarde si la ligne est pair ou impair (ici pair)
		{
	for(i=0 ; i < pl->n ; i++)//remplie de couleur les creux
			{
				if (i%2==0)
					color_printf(GREEN,MAGENTA,"       ");//regarde si la case est pair ou impair (pair)
				else
					color_printf(GREEN,CYAN,"       ");//impair
			}
		}
		else//ici ligne impair
		{
			for(i=0 ; i < pl->n ; i++)//remplie de couleur le vide superieur
			{
				if (i%2==0)
					color_printf(GREEN,CYAN,"       ");//regarde si la case est pair ou impair (pair)
				else
					color_printf(GREEN,MAGENTA,"       ");//impair
			}
		}
}	

void afficheValeur(plateau *pl,int l,int k,int j)
{
	
	if(l%2==0)//regarde si la ligne est impair ou pair
	{
		if(k%2==0)//regarde si la case est impair ou pair
		{
			//affiche des couleur differente en fonction de la valeur
			if (*(pl->tableau+j)==1)
				color_printf(WHITE,MAGENTA,"   O   ");
			else if (*(pl->tableau+j)==-1)
				color_printf(BLACK,MAGENTA,"   O   ");
			else
				color_printf(GREEN,MAGENTA,"       ");
		}
		else//case impair
		{
			if (*(pl->tableau+j)==1)
				color_printf(WHITE,CYAN,"   O   ");
			else if (*(pl->tableau+j)==-1)
				color_printf(BLACK,CYAN,"   O   ");
			else
				color_printf(GREEN,CYAN,"       ");
		}
	}
	else//ligne impair
	{
		if(k%2==0)//case pair
		{
			//affiche des couleur differente en fonction de la valeur
			if (*(pl->tableau+j)==1)
				color_printf(WHITE,CYAN,"   O   ");
			else if (*(pl->tableau+j)==-1)
				color_printf(BLACK,CYAN,"   O   ");
			else
				color_printf(GREEN,CYAN,"       ");
		}
		else//case impair
		{
			if (*(pl->tableau+j)==1)
				color_printf(WHITE,MAGENTA,"   O   ");
			else if (*(pl->tableau+j)==-1)
				color_printf(BLACK,MAGENTA,"   O   ");
			else
				color_printf(GREEN,MAGENTA,"       ");
		}
	}

}



void affichage(plateau *pl)
{
	int i,j=0,k,l;

	//affiche les numéro de case du dessus
	for(i=0; i<pl->n ; i++)
		printf("     %d ",i+1);

	printf("\n");
	for(l=0 ; l<pl->n ; l++)	//passe les ligne de case
	{
		printf("  ");//espace le tableau

		afficheLigneIntermediaire(pl,l);
		printf("\n");

		printf("%d ",l+1);//affche les numéro de ligne a gauche
		//affiche la valeur
		for(k=0 ; k<pl->n ; k++)
		{
			afficheValeur(pl,l,k,j);
			j++	;//ajoute +1 a la valeur qui permet de prendre la valeur du tableau (*p).tableau
		}
		printf("\n");

		printf("  ");
		afficheLigneIntermediaire(pl,l);
		
		printf("\n");//passe a la prochaine ligne


	}//fin de la partie affichage

	printf("\n");


}

int getCase(plateau * p,int i,int j)//fonction qui donne la valeur de la case de coordonées x et y
{
	assert( (i>=0 && i<(p->n) ) && "erreur de coordonnées");//verifie que i est bien entre (0,((*pl).n)-1)
	assert( (j>=0 && j<(p->n) ) && "erreur de coordonnées");//pareil pour j
	/*renvoie la valeur de la case
	  avance de n*i adresse ((*p).n) dans le tableau puis ajoute j au precedent resultat
	*/
	return *(p->tableau+((i*(p->n))+j)); 

}

//fonction qui met une valeur 0 1 ou -1 au coordonnées données
void setCase(plateau *p,int i,int j,int  val)
{
		assert( (i>=0 && i<=(p->n)-1 ) && ("erreur de coordonnées"));//verifie que i est bien entre (0,((*pl).n)-1)
		assert( (j>=0 && j<=(p->n)-1 ) && ("erreur de coordonnées"));//pareil pour j
		assert( (val>=-1 && val<=1 ) && ("erreur de valleur val n'est pas compris entre -1 et 1"));//verifie que val  se situe entre 1 et 0
		*(p->tableau+((i*p->n)+j)) = val ;
}
