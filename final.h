#ifndef FINAL_H
#define FINAL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>




typedef struct
{
	int * tableau;
	int n;
}plateau;

typedef struct
{
	char nomJoueur1[127] ;
	char nomJoueur2[127];
	int pionJoueurCourant;
	plateau * p;

}partie;

// couleurs du terminal
  typedef enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  } COULEUR_TERMINAL;

/*
 * Fonction effaçant le terminal
 */
void clear_terminal();

/*
 * Printf en couleur. Les deux premiers paramètres sont les couleurs d'écriture et de fond (mettre une des valeurs parmi : 
 * BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN et WHITE).
 * Les parmètres suivants sont comme le printf "normal" : chaîne de format puis toutes les valeurs à afficher
 */
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format,...);


//partie1
void delay(int n);
plateau* creerPlateau(int taille);
void detruirePlateau(plateau * p);
void affichage(plateau *pl);
int getCase(plateau * p,int i,int j);
void setCase(plateau *p,int i,int j,int  val);

//partie2
int indiceValide (plateau * p, int indice);
int caseValide(plateau * p, int indiceLigne, int indiceColonne);
int caseVide(plateau * p, int i, int j);
int ligneCaseVide(plateau * p,int ligne,int colonne,int di,int dj);
int directPossible(plateau * p,int ligne,int colonne,int di,int dj);
int valeurCase(plateau *p,int ligne ,int colonne ,int di ,int dj);
int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion);
void bougeLigne(plateau *p , int ligne,int colonne,int di,int dj);
void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion);
int gagne(plateau * p);
void invers(plateau * p, int n);


//partie3
partie * creerPartie ();
void detruirePartie(partie * pa);
void changePionCouleurCourant (partie * pa);
int saisieJoueur(partie * pa, int * li, int * co, int * di, int * dj);
void afficheNom(partie * pa);
int tourJoueur (partie * pa);
int jouer (partie * pa);

//partie4
int sauvegardePartie(partie * pa);
int menu(partie * pa);
partie * chargementPartie();

#endif
