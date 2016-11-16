#include<stdio.h>
#include<stdlib.h>
#include "final.h"


/*!
* Fonction retournant 1 si l’indice est valide par rapport au plateau
*
* \param p : plateau
* \param indice : entier compris entre [0,n-1]
*/
int indiceValide (plateau * p, int indice)
{
	int indice_val=0;
	if ( indice >= 0 && indice < p->n )
		indice_val=1;
	return indice_val;

}

/*!
* Fonction retournant 1 si la case (indiceLigne,indiceColonne) existe sur le plateau
*
* \param p : plateau
* \param indiceLigne : entier correspondant à un indice de ligne
* \param indiceColonne : entier correspondant à un indice de colonne
*/
int caseValide(plateau * p, int indiceLigne, int indiceColonne)
{	
	if(indiceValide(p,indiceLigne) && indiceValide(p,indiceColonne)) 
			return 1;
	return 0;		
}

/*!
* Fonction retournant 1 si la case (i,j) du plateau p est vide
*
* \param p : plateau
* \param i : entier correspondant à un indice de ligne
* \param j : entier correspondant à un indice de colonne
*/

int caseVide(plateau * p, int i, int j)
{
	if (caseValide(p,i,j) && getCase(p,i,j)==0)
			return 1;
	return 0;

}

//donne la position du premier vide de la ligne s'il y en a renvoie zero s'il n'y a pas de vide 
int ligneCaseVide(plateau * p,int ligne,int colonne,int di,int dj)
{
	int i;

	if (di==1)
		for (i=1 ; i <= p->n ; i++)
			if (caseVide(p,ligne+i-1,colonne))
			{
				return i;
			}
	if (di==-1 )
		for (i=1 ; i <= p->n ; i++)
		{
			if (caseVide(p,ligne-i+1,colonne))
			{
				return i;
			}
		}

	if (dj==-1)
	{
		
		for (i=1 ; i <= p->n ; i++)
		{
			if (caseVide(p,ligne,colonne-i+1))
			{
				return i;
			}	
		}
		
	}

	if	(dj==1)
		for (i=1 ; i <= p->n ; i++)
		{
			if (caseVide(p,ligne,colonne+i-1))
			{
				return i;
			}		
		}


	return 0;
}



/*
	fonction retournant 1 si l'ont peut inserer un pion dans la direction donnéer par di et dj
	/param di direction sur les lignes
	/param dj direction sur les colonnes
*/
int directPossible(plateau * p,int ligne,int colonne,int di,int dj)
{
	int possible =-1;
	
	if ( colonne < p->n && colonne >= 0 && ligne == 0 && di == 1 )
		possible =1;
	else if ( colonne < p->n && colonne >= 0 && ligne == ((p->n)-1) && di == -1 )
		possible=1;
	else if ( ligne < p->n && ligne >= 0 && colonne == 0 && dj == 1 )
		possible = 1;
	else if ( ligne < p->n && ligne >= 0 && colonne == ((p->n)-1) && dj == -1 )
		possible = 1;
	else 
		possible = 0;	
		
	return possible;
}

//cherche la valeur oposé a la case donné + une direction
int valeurCase(plateau *p,int ligne ,int colonne ,int di ,int dj)
{
	int valCase;
	
	if ( colonne < p->n && colonne >= 0 && ligne == 0 && di == 1 )
		valCase = *(p->tableau+colonne+((p->n*p->n)-p->n));
	else if ( colonne < p->n && colonne >= 0 && ligne == ((p->n)-1) && di == -1 )
		valCase = *(p->tableau+colonne);
	else if ( ligne < p->n && ligne >= 0 && colonne == 0 && dj == 1 )
		valCase = *(p->tableau + (p->n-1) +(ligne*p->n)); 
	else if ( ligne < p->n && ligne >= 0 && colonne == ((p->n)-1) && dj == -1 )
		valCase = *(p->tableau + (ligne*p->n));
	else 
		valCase = 0;


	return valCase;
}

/*!
* Fonction retournant 1 si le pion peut être ajouté à partir de la case (ligne,col)
* dans la direction donnée par di,dj
*
* \param p : plateau
* \param ligne : ligne de la case où l’on insère le pion
* \param col : colonne de la case où l’on insère le pion
* \param di : direction sur les lignes
*
	// -1 si l’on insère vers le haut,
*
	// 0 si l’on reste sur la même ligne,
*
	// 1 si l’on insère vers le bas
* \param dj : direction sur les colonnes
*
	// -1 si l’on insère vers la gauche,
*
	// 0 si l’on reste sur la même colonne,
*
	// 1 si l’on insère vers la droite
* \param pion : 1 ou -1 suivant le joueur
*/
int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion) 
{
	int insert_poss=0;
	if (caseValide(p,ligne,col))
	{
		if(directPossible(p,ligne,col,di,dj))
		{
			if(ligneCaseVide(p,ligne,col,di,dj)!=0)
				insert_poss=1;
			else if( pion == valeurCase(p,ligne,col,di,dj) || valeurCase(p,ligne,col,di,dj) == 0 )
				insert_poss=1;
		}
	}



	return insert_poss;
}

//fonction qui bouge les ligne en fonction de la ou ce trouve le pion inséré prend en compte les vide
void bougeLigne(plateau *p , int ligne,int colonne, int di, int dj)
{
	int i;
	
	int a = ligneCaseVide(p,ligne,colonne,di,dj);

	if (a==0)
		a=p->n;
	if (ligne == 0 && colonne >= 0 && colonne < p->n && di == 1) //direction haut vers bas
		for (i=a-1; i > 0 ;i-- )
		{		
				setCase(p,i,colonne,getCase(p,i-1,colonne));
				//*(p->tableau+(i*p->n)+colonne)=*(p->tableau+((i-1)*p->n)+colonne);
		}
	else if ( colonne == (p->n)-1 && ligne >=0 && ligne < p->n && dj == -1 )//direction droite vers gauche
		for (i=p->n-a; i<p->n ; i++)
		{
				//setCase(p,ligne,colonne,getCase(p,ligne,i+1));
				*(p->tableau+(ligne*p->n)+i)=*(p->tableau+ligne*p->n+i+1);
		}
	else if (colonne == 0 && ligne >= 0 && ligne < p->n && dj == 1 )//direction gauche vers droite
		for (i=a-1;i>0;i--)
		{
				//setCase(p,ligne,colonne,getCase(p,ligne,i-1));
				*(p->tableau+(ligne*p->n)+i)=*(p->tableau+(ligne*p->n)+i-1);
		}
	else if (ligne == p->n-1 && colonne >= 0 && colonne < p->n && di == -1)//direction du bas vers le haut
		for(i=p->n-a; i<p->n	; i++)	
		{
				*(p->tableau+(i*p->n)+colonne)=*(p->tableau+((i+1)*p->n)+colonne);
		}
			
}

/*!
* Fonction insérant le pion à partir de la case (ligne,col)
* dans la direction donnée par di,dj
*
* \param p : plateau
* \param ligne : ligne de la case où l’on insère le pion
* \param col : colonne de la case où l’on insère le pion
* \param di : direction sur les lignes
*
// -1 si l’on insère vers le haut,
*
// 0 si l’on reste sur la même ligne,
*
// 1 si l’on insère vers le haut
* \param dj : direction sur les colonnes
*
// -1 si l’on insère vers la gauche,
*
// 0 si l’on reste sur la même colonne,
*
// 1 si l’on insère vers la droite
* \param pion : 1 ou -1 suivant le joueur
*/
void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion)
{
	if (insertionPionPossible(p,ligne,col,di,dj,pion) )
	{
		bougeLigne(p,ligne,col,di,dj);
		*(p->tableau+(ligne*p->n)+col)=pion;
	}
	else
		printf("le pion ne peut pas être insere ici\n");

}





/*
/ fonction qui retourne 1 ou -1 si l'un des deux joueurs a gagné , 2 si match nul et 0 si la partie n'est 
/pas fini
*/
int gagne(plateau * p)
{
	int i=0;
	int j=0;
	int blanc=0;
	int noir=0;
	int blanc2=0;
	int noir2=0;


	for(i=0;i<p->n;i++)
		for(j=0;j<p->n-1;j++)
			{
				if (getCase(p,i,j) == getCase(p,i,j+1) && getCase(p,i,j )== 1 )
				{
					blanc ++;
					if (blanc==p->n-1)
					{	
						blanc = 0;
						blanc2++;
					}
				}
				if (getCase(p,i,j) == getCase(p,i,j+1) && getCase(p,i,j )== -1 )
				{
					noir ++;
					if (noir == p->n-1)
					{
						noir = 0;
						noir2++;
					}
				}
				
			}
	

	invers(p,2);
	for(i=0;i<p->n;i++)
		for(j=0;j<p->n-1;j++)
			{
				if (getCase(p,i,j) == getCase(p,i,j+1) && getCase(p,i,j )== 1 )
				{
					blanc ++;
					if (blanc==p->n-1)
					{	
						blanc = 0;
						blanc2++;
					}
				}
				if (getCase(p,i,j) == getCase(p,i,j+1) && getCase(p,i,j )== -1 )
				{
					noir ++;
					if (noir == p->n-1)
					{
						noir = 0;
						noir2++;
					}
				}
				
			}
	invers(p,2);


		

		if(blanc2 > noir2)
			return 1;	
		if(blanc2 < noir2)
			return -1;
		if(blanc2 == noir2 && blanc2 !=0 )
			return 2;	

	return 0;
	
}

/*fonction qui inverse le tableau avec 3 paramètre
	//n = 0 inverse le plateau par rapport a un axe horizontal
	//n = 1 inverse le plateau par rapport a un axe vertical
	//n = 2 inverse le plateau par rapport a la première diagonal

	
*/
void invers(plateau * p, int n)
{
	int i;
	int j;
	int a;
	//inverse par rapport a un axe horizontale
	if (n==0)
	{
		for (i=0;i<(p->n)/2 ; i++)
			for(j=0;j< (p->n) ; j++)
			{
				a=getCase(p,i,j);
				setCase(p,i,j,getCase(p,p->n-1-i,j ));
				setCase(p,p->n-i-1,j,a);
			}
	}


	//inverse par rapport a un axe verticale
	if (n == 1 )
	{
		for (i=0;i<p->n ; i++)
			for(j=0;j< (p->n)/2 ; j++)
			{
				a=getCase(p,i,j);
				setCase(p,i,j,getCase(p,i,p->n-j-1));
				setCase(p,i,p->n-j-1,a);
			}
	}
	//inverse par rapport a l'axe diagonale

	if(n==2)
	{
		for (i=1;i<p->n; i++)
			for(j=0;j< (p->n)-(p->n-i) ; j++)
			{
				a=getCase(p,i,j);
				setCase(p,i,j,getCase(p,j,i));
				setCase(p,j,i,a);	
			}
	}

}

