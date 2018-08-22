#include <lib.h>
#include "Variable.h"

void printCard(int x, int y, int number, int color);
void eraseCard(int x, int y);
void CG_DEFCHAR();
void AdvancedPrint(int,int,char*);
void APlot(int,int,char,int);

#define TREFLE 1
#define CARREAU 2
#define COEUR 3
#define PIQUE 4
#define VALET 11
#define DAME 12
#define ROI 13
#define AS 1
#define VIDE 0
#define FLIP 5
#define NOCARD 0

unsigned int i,j,k, crd, curs, kee, inibet;

unsigned int rd1, rd2, nb1, nb2, crd1, crd2;
unsigned int cards[52], table[5];

unsigned char nbPlayers, turn, selec, allPlay, cont;

Player p [4] = {{"P1", 0, 0, 600, 0, 1},
		 {"P2", 0, 0, 600, 0, 1},
		 {"P3", 0, 0, 600, 0, 1},
		 {"P4", 0, 0, 600, 0, 1}
};

char *strJoue   = "JOUE       ";
char *strNoJoue = "NE JOUE PAS";


void prepare()
{
	for(i=0;i<52;i++)
		cards[i] = i;
}


void shuffle()
{
	for(j=0;j<32;j++)
	{
		APlot(4+j,24,22,1);
		APlot(5+j,24,23,1);
	}
	for(j=0;j<32;j++)
	{
		for(i=0;i<4;i++)
		{
			rd1 = random(); rd2 = random();
			nb1 = rd1%52;   nb2 = rd2%52;
			crd1 = cards[nb1];
			cards[nb1] = cards[nb2];
			cards[nb2] = crd1;
		}
		APlot(4+j,24,20,1);
	}
	APlot(4,24,' ',32);
}

void pause(int ps){
	for(i=0;i<ps;i++)
		for(j=0;j<256;j++)
			;
}

void main()
{
	CG_DEFCHAR();
	cls();
	printf("\n\nCombien de joueurs? (2 a 4) ");
	nbPlayers = 0;
	while(nbPlayers<2 || nbPlayers>4)
	{	
		scanf("%d",&nbPlayers);
		if(nbPlayers<2 || nbPlayers>4)
			printf("2 a 4 joueurs!");
	}
	
	printf("Entrez les noms (jusqu'a 8 caracteres)\n");
	for(i=0;i<nbPlayers;i++){
		printf("\nJoueur %d \n",i+1);
		scanf("%s",p[i].name);
	}
	
	cont = 1;
	while(cont)
	{
		cls();
		poke(0x26a,6);
		
		poke(0xBB80+1*40+1,9);
		for(i=2*40;i<8*40;i+=40){
			poke(0xBB80+i+1,8);
			poke(0xBB80+i+2,4);
			poke(0xBB80+i+39,23);
		}
		for(i=8*40;i<23*40;i+=40){
			poke(0xBB80+i+1,9);
		}
		for(i=23*40;i<28*40;i+=40){
			poke(0xBB80+i+1,8);
			poke(0xBB80+i+2,4);
		}
		for(i=0;i<nbPlayers;i++){
			AdvancedPrint(3,2+i,p[i].name);
			AdvancedPrint(13,2+i,itoa(p[i].money));
		}
		
		AdvancedPrint(9,23,"APPUYEZ SUR UNE TOUCHE");
		getchar();
		srandom(deek(0x304));
		AdvancedPrint(9,23," MELANGE DES CARTES...");
		prepare(); shuffle();
		AdvancedPrint(7,23,"TOUT LE MONDE JOUE CE TOUR?");
		AdvancedPrint(10,25,"OUI");
		AdvancedPrint(27,25,"NON");
		AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
		curs = 1; selec = 1;
		while(selec)
		{
			if(curs==1)
			{
				APlot(9,25,22,1);
				APlot(14,25,23,1);
				APlot(26,25,23,1);
			}
			else
			{
				APlot(26,25,22,1);
				APlot(31,25,23,1);
				APlot(9,25,23,1);
			}
			kee = get();
			if(kee == 8 || kee == 9)	//Flèche gauche / droite
				if(curs == 1)
					curs = 0;
				else
					curs = 1;
			if(kee == 13)				// ENTER
				selec = 0;
		}
		allPlay = curs;
		APlot(9,25,' ',5);
		APlot(26,25,' ',5);
		APlot(9,27,' ',32);
		if(allPlay == 1)
			for(i=0;i<nbPlayers;i++) p[i].play = allPlay;
		else {
			curs = 1; 
			selec = 1;
			while(selec)
			{
				AdvancedPrint(7,23,"SELECTIONNEZ LES JOUEURS");
				AdvancedPrint(9,27,"  [1]  [2]  [3]  [4]  ");
				for(i=0;i<nbPlayers;i++){
					if(p[i].play==1){
						APlot(2,2+i,4,1);
						APlot(1,2+i,22,1);
						AdvancedPrint(20,2+i,strJoue);
					} else {
						APlot(2,2+i,1,1);
						APlot(1,2+i,19,1);
						AdvancedPrint(20,2+i,strNoJoue);
					}
				}
				for(i=nbPlayers;i<4;i++){
					p[i].play = 0;
					APlot(2,2+i,0,1);
					APlot(1,2+i,23,1);
					APlot(20,2+i,' ',11);
				}

				kee = get();
				if(kee>=49 && kee <=52) {
					i=kee-49;
					p[i].play= 1 - p[i].play;
				}
				if(kee==13)
					selec = 0;
			}
		}
		APlot(9,27,' ',22);
		
		AdvancedPrint(7,23,"    DISTRIBUTION...        ");
		crd = 0;
		for(i=0;i<nbPlayers;i++){
			if(p[i].play) {
				p[i].hand1 = cards[crd];  crd++;
				p[i].hand2 = cards[crd];  crd++;
				p[i].bet = 1;
			}
		}
		for(i=0;i<5;i++)
		{
			table[i] = cards[crd];
			crd++;
		}
		pause(4);
			
		APlot(8,23,' ',23);
		for(k=0;k<5;k++)
			printCard( 2+k*6, 9, NOCARD, VIDE);
		
		pause(16);
		
		for(k=0;k<3;k++)
		{
			printCard(2+k*6,9, NOCARD, FLIP);
			pause(4);
			printCard(2+k*6,9, table[k]%13+1, table[k]/13+1);
			pause(4);
		}
		
		for(i=0;i<nbPlayers;i++)
			AdvancedPrint(21,2+i,itoa(p[i].bet));
		
				
		//Pi Play
		for(i=0;i<nbPlayers;i++){
			for(j=16;j<22;j++) {
				APlot(2,j,5,1);
				APlot(3,j,109,34);
			}
			if(p[i].play) {
				AdvancedPrint(8,23,"  TOUR DE ");
				AdvancedPrint(18,23,p[i].name);
				AdvancedPrint(8,25,"APPUYEZ SUR UNE TOUCHE");
				APlot(1,2,18,1);
			
				get();
				for(j=16;j<22;j++)
					APlot(2,j,23,35);
				APlot(8,23,' ',18);
				APlot(8,25,' ',22);		
				APlot(1,2,22,1);
				printCard( 2+6, 16, NOCARD, VIDE);
				printCard( 2+2*6, 16, NOCARD, VIDE);
			
				printCard(2,16, NOCARD, FLIP);
			
				pause(4);
				printCard(2,16, p[i].hand1 %13+1, p[i].hand1 /13+1);
				pause(4);
				printCard(8,16, NOCARD, FLIP);
				pause(4);
				printCard(8,16, p[i].hand2 %13+1, p[i].hand2 /13+1);
				pause(4);
				selec = 1; curs = 1; inibet = p[i].bet;
				while(selec)
				{
					AdvancedPrint(5,23,"+ 1"); AdvancedPrint(10,23,"+ 5"); AdvancedPrint(15,23,"+10"); AdvancedPrint(20,23,"+50");
					AdvancedPrint(5,24,"- 1"); AdvancedPrint(10,24,"- 5"); AdvancedPrint(15,24,"-10"); AdvancedPrint(20,24,"-50");
					AdvancedPrint(10,25,"VALIDER"); AdvancedPrint(30,24,"      "); AdvancedPrint(30,24,itoa(p[0].bet));
					AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
					if(curs == 1){APlot( 4,23,22,1);APlot( 8,23,23,1);}else APlot( 4,23,23,1);
					if(curs == 2){APlot( 9,23,22,1);APlot(13,23,23,1);}else APlot( 9,23,23,1);
					if(curs == 3){APlot(14,23,22,1);APlot(18,23,23,1);}else APlot(14,23,23,1);
					if(curs == 4){APlot(19,23,22,1);APlot(23,23,23,1);}else APlot(19,23,23,1);
					if(curs == 5){APlot( 4,24,22,1);APlot( 8,24,23,1);}else APlot( 4,24,23,1);
					if(curs == 6){APlot( 9,24,22,1);APlot(13,24,23,1);}else APlot( 9,24,23,1);
					if(curs == 7){APlot(14,24,22,1);APlot(18,24,23,1);}else APlot(14,24,23,1);
					if(curs == 8){APlot(19,24,22,1);APlot(23,24,23,1);}else APlot(19,24,23,1);
					if(curs == 9){APlot( 9,25,22,1);APlot(17,25,23,1);}else APlot( 9,25,23,1);
				
					kee = get();
					if(kee==8)				// G
					{
						if(curs==1)
							curs=4;
						else if(curs==5)
							curs=8;
						else if(curs==9)
							;
						else
							curs--;
					}
					if(kee==9)				// D
					{
						if(curs==4)
							curs=1;
						else if(curs==8)
							curs=5;
						else if(curs==9)
							;
						else
							curs++;
					}
					if(kee==11)				// H
					{
						if((curs-1)/4==0)
							curs=9;
						else if((curs-1)/4==1)
							curs-=4;
						else if(curs==9)
							curs=5;
					}
					if(kee==10)				// B
					{
						if((curs-1)/4==0)
							curs+=4;
						else if((curs-1)/4==1)
							curs=9;
						else if(curs==9)
							curs=1;
					}
					if(kee==13)				// ENTER
					{
						if(curs == 1){if(p[i].bet<p[i].money   )p[i].bet++;}
						if(curs == 2){if(p[i].bet<p[i].money-5 )p[i].bet+=5;}
						if(curs == 3){if(p[i].bet<p[i].money-10)p[i].bet+=10;}
						if(curs == 4){if(p[i].bet<p[i].money-50)p[i].bet+=50;}
						if(curs == 5){if(p[i].bet>inibet )      p[i].bet--;}
						if(curs == 6){if(p[i].bet>(inibet+4))   p[i].bet-=5;}
						if(curs == 7){if(p[i].bet>(inibet+9))   p[i].bet-=10;}
						if(curs == 8){if(p[i].bet>(inibet+49))  p[i].bet-=50;}
						if(curs == 9){selec = 0;}
					}
				}
			
				for(k=23;k<28;k++)
					APlot(3,k,' ',36);
			}
			
			for(i=0;i<nbPlayers;i++)
				AdvancedPrint(21,2+i,itoa(p[i].bet));
		}	
			
		for(k=23;k<28;k++)
			APlot(3,k,' ',36);
		
		
		get();
	}
}
