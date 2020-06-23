#include<stdio.h>
#include<stdlib.h>
#include"final.h"


int main()
{
	int x = 1;
	int y;

	color_printf(WHITE,BLACK,"BIENVENUE... \n");
	delay(5);
	color_printf(WHITE,BLACK,"SUR LE JEU ... \n");
	delay(5);

	color_printf(YELLOW,BLACK,"                    .__                                \n"); 
	delay(1);
	color_printf(YELLOW,BLACK,"______  __ __  _____|  |__     _______  __ ___________ \n");
	delay(1);
	color_printf(YELLOW,BLACK,"\\____ \\|  |  \\/  ___/  |  \\   /  _ \\  \\/ // __ \\_  __ \\\n");
	delay(1);
	color_printf(YELLOW,BLACK,"|  |_> >  |  /\\___ \\|   Y  \\ (  <_> )   /\\  ___/|  | \\/\n");
	delay(1);
	color_printf(YELLOW,BLACK,"|   __/|____//____  >___|  /  \\____/ \\_/  \\___  >__|   \n");
	delay(1);
	color_printf(YELLOW,BLACK,"|__|              \\/     \\/                   \\/       \n");
	delay(4);
	

	partie * pa;
		pa=NULL;
	while(x != 0)
	{
		x=menu(pa);
		clear_terminal();
		if(x==1)//deuxieme choix
		{
				pa=creerPartie();
				pa->pionJoueurCourant = 1;
				y=jouer(pa);
				if (y==1)
				{	
					detruirePartie(pa);
					return 0;
				}
		}	
		else if(x==2)//troisieme choix
		{
				
				pa=chargementPartie();
				y=jouer(pa);
				if (y==1)
				{ 
					detruirePartie(pa);
					return 0;
				}
		
		}
		else if(x==3)//4ieme choix
		{
			
				y=sauvegardePartie(pa);
				if(y==1)
				{
					printf("sauvegarde reussi la jeu va maintenant s'arreter \n");
					delay(1);
					detruirePartie(pa);
					return 0;
				}
		}	
		else if (x==4)//5ieme choix
		{
			y=jouer(pa);
				if (y==1)
				{ 
					detruirePartie(pa);
					return 0;
				}
		}
		
	}
	color_printf(RED,BLACK,"   _                               _      \n");
	delay(1);
	color_printf(RED,BLACK,"  /_\\  _   _   _ __ _____   _____ (_)_ __ \n");
	delay(1);
	color_printf(RED,BLACK," //_\\\\| | | | | '__/ _ \\ \\ / / _ \\| | '__|\n");
	delay(1);
	color_printf(RED,BLACK,"/  _  \\ |_| | | | |  __/\\ V / (_) | | |   \n");
	delay(1);
	color_printf(RED,BLACK,"\\_/ \\_/\\__,_| |_|  \\___| \\_/ \\___/|_|_|   \n");
	delay(1);
	color_printf(RED,BLACK,"                                          \n");
	delay(1);
	return 0;
}
