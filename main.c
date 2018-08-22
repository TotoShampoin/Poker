#include <lib.h>
#include "Variable.h"

void printCard(int x, int y, int number, int color);
void eraseCard(int x, int y);
void CG_DEFCHAR();
void AdvancedPrint();

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

Player P1 = {"P1", 0, 0, 600, 0}, P2 = {"P2", 0, 0, 600, 0}, P3 = {"P3", 0, 0, 600, 0}, P4 = {"P4", 0, 0, 600, 0};
unsigned char p1Play, p2Play, p3Play, p4Play;

void prepare()
{
	for(i=0;i<52;i++)
		cards[i] = i;
}


void shuffle()
{
	for(j=0;j<32;j++)
	{
		APlot(4+j,24,22);
		APlot(5+j,24,23);
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
		APlot(4+j,24,20);
	}
	AdvancedPrint(4,24,"                                ");
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
	
		printf("Entrez les noms (jusqu'a 8 caracteres)\n\nJoueur 1 \n");
		scanf("%s",P1.name);
		
		printf("\nJoueur 2 \n");
		scanf("%s",P2.name);
		
		if(nbPlayers>2)
		{
			printf("\nJoueur 3 \n");
			scanf("%s",P3.name);
		}
		if(nbPlayers > 3)
		{
			printf("\nJoueur 4 \n");
			scanf("%s",P4.name);
		}
	
	cont = 1;
	while(cont)
	{
		cls();
		poke(0x26a,6);
		
		poke(0xBB80+1*40+1,9);
		for(i=2;i<8;i++){
			poke(0xBB80+i*40+1,8);
			poke(0xBB80+i*40+2,4);
			poke(0xBB80+i*40+39,23);
		}
		for(i=8;i<23;i++){
			poke(0xBB80+i*40+1,9);
		}
		for(i=23;i<28;i++){
			poke(0xBB80+i*40+1,8);
			poke(0xBB80+i*40+2,4);
		}
		
		AdvancedPrint(3,2,P1.name);
		AdvancedPrint(13,2,itoa(P1.money));
		AdvancedPrint(3,3,P2.name);
		AdvancedPrint(13,3,itoa(P2.money));
		if(nbPlayers>2)
		{
			AdvancedPrint(3,4,P3.name);
			AdvancedPrint(13,4,itoa(P3.money));
		}
		if(nbPlayers>3)
		{
			AdvancedPrint(3,5,P4.name);
			AdvancedPrint(13,5,itoa(P4.money));
		}
		
		AdvancedPrint(9,23,"APPUYEZ SUR UNE TOUCHE");
		getchar();
		srandom(deek(0x304));
		AdvancedPrint(9,23," MELANGE DES CARTES...");
		prepare(); shuffle();
		AdvancedPrint(7,23,"TOUT LE MONDE JOUE CE TOUR?");
		AdvancedPrint(10,25,"OUI"); AdvancedPrint(27,25,"NON");
		AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
		curs = 1; selec = 1;
		while(selec)
		{
			if(curs==1)
			{
				APlot(9,25,22); APlot(14,25,23);
				APlot(26,25,23);
			}
			else
			{
				APlot(26,25,22); APlot(31,25,23);
				APlot(9,25,23);
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
		AdvancedPrint(9,25,"     "); AdvancedPrint(26,25,"     ");
		AdvancedPrint(9,27,"                      ");
		
		p1Play = 0; p2Play = 0; p3Play = 0; p4Play = 0;
		if(allPlay == 1)
		{
			// p1Play = 1;
			p2Play = 1;
			if(nbPlayers>2)p3Play = 1;
			if(nbPlayers>3)p4Play = 1;
		}
		else
		{
			curs = 1; selec = 1;
			while(selec)
			{
				AdvancedPrint(7,23,"SELECTIONNEZ LES JOUEURS");
				AdvancedPrint(9,27,"  [1]  [2]  [3]  [4]  ");
				if(p1Play==1)		
				{
					APlot(2,2,4);
					APlot(1,2,22);
					AdvancedPrint(20,2,"JOUE       ");
				}
				else
				{
					APlot(2,2,1);
					APlot(1,2,19);
					AdvancedPrint(20,2,"NE JOUE PAS");
				}
				if(p2Play==1)
				{
					APlot(2,3,4);
					APlot(1,3,22);
					AdvancedPrint(20,3,"JOUE       ");
				}
				else
				{
					APlot(2,3,1);
					APlot(1,3,19);
					AdvancedPrint(20,3,"NE JOUE PAS");
				}
				if(p3Play==1)
				{
					APlot(2,4,4);
					APlot(1,4,22);
					AdvancedPrint(20,4,"JOUE       ");
				}
				else
				{
					APlot(2,4,1);
					APlot(1,4,19);
					AdvancedPrint(20,4,"NE JOUE PAS");
				}
				if(nbPlayers<3)
				{
					p3Play = 0;
					APlot(2,4,0);
					APlot(1,4,23);
					AdvancedPrint(20,4,"           ");
				}
				if(p4Play==1)
				{
					APlot(2,5,4);
					APlot(1,5,22);
					AdvancedPrint(20,5,"JOUE       ");
				}
				else
				{
					APlot(2,5,1);
					APlot(1,5,19);
					AdvancedPrint(20,5,"NE JOUE PAS");
				}
				if(nbPlayers<4)
				{
					p4Play = 0;
					APlot(2,5,0);
					APlot(1,5,23);
					AdvancedPrint(20,5,"           ");
				}
				kee = get();
				if(kee==49)				// 1
					if(p1Play==1)
						p1Play = 0;
					else
						p1Play = 1;
				if(kee==50)				// 2
					if(p2Play==1)
						p2Play = 0;
					else
						p2Play = 1;
				if(kee==51)				// 3
					if(p3Play==1)
						p3Play = 0;
					else
						p3Play = 1;
				if(kee==52)				// 4
					if(p4Play==1)
						p4Play = 0;
					else
						p4Play = 1;
				if(kee==13)				// ENTER
					selec = 0;
			}
		}
		AdvancedPrint(9,27,"                      ");
		
		AdvancedPrint(7,23,"    DISTRIBUTION...        ");
		crd = 0;
		if(p1Play)
		{
			P1.hand1 = cards[crd];  crd++;
			P1.hand2 = cards[crd];  crd++;
			P1.bet = 1;
		}
		if(p2Play)
		{
			P2.hand1 = cards[crd];  crd++;
			P2.hand2 = cards[crd];  crd++;
			P2.bet = 1;
		}
		if(p3Play)
		{
			P3.hand1 = cards[crd];  crd++;
			P3.hand2 = cards[crd];  crd++;
			P3.bet = 1;
		}
		if(p4Play)
		{
			P4.hand1 = cards[crd];  crd++;
			P4.hand2 = cards[crd];  crd++;
			P4.bet = 1;
		}
		for(i=0;i<5;i++)
		{
			table[i] = cards[crd];
			crd++;
		}
		
		for(i=0;i<4;i++)
			for(j=0;j<256;j++)
				;
			
		AdvancedPrint(8,23,"                       ");
		for(k=0;k<5;k++)
			printCard( 2+k*6, 9, NOCARD, VIDE);
		for(i=0;i<16;i++)
			for(j=0;j<256;j++)
				;
		for(k=0;k<3;k++)
		{
			printCard(2+k*6,9, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(2+k*6,9, table[k]%13+1, table[k]/13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
		}
		
		AdvancedPrint(21,2,itoa(P1.bet));
		AdvancedPrint(21,3,itoa(P2.bet));
		AdvancedPrint(21,4,itoa(P3.bet));
		AdvancedPrint(21,5,itoa(P4.bet));
		
		for(j=16;j<22;j++)
		{
			APlot(2,j,5);
			for(i=3;i<37;i++)
				APlot(i,j,109);
		}
		//P1 Play
		if(p1Play)
		{
			AdvancedPrint(8,23,"  TOUR DE ");
			AdvancedPrint(18,23,P1.name);
			AdvancedPrint(8,25,"APPUYEZ SUR UNE TOUCHE");
			APlot(1,2,18);
			
			get();
			for(j=16;j<22;j++)
			{
				for(i=2;i<37;i++)
					APlot(i,j,23);
			}
			AdvancedPrint(8,23,"                  ");
			AdvancedPrint(8,25,"                      ");
			
			APlot(1,2,22);
			for(k=0;k<2;k++)
				printCard( 2+k*6, 16, NOCARD, VIDE);
			
			printCard(2,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(2,16, P1.hand1 %13+1, P1.hand1 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, P1.hand2 %13+1, P1.hand2 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			selec = 1; curs = 1; inibet = P1.bet;
			while(selec)
			{
				AdvancedPrint(5,23,"+ 1"); AdvancedPrint(10,23,"+ 5"); AdvancedPrint(15,23,"+10"); AdvancedPrint(20,23,"+50");
				AdvancedPrint(5,24,"- 1"); AdvancedPrint(10,24,"- 5"); AdvancedPrint(15,24,"-10"); AdvancedPrint(20,24,"-50");
				AdvancedPrint(10,25,"VALIDER"); AdvancedPrint(30,24,"      "); AdvancedPrint(30,24,itoa(P1.bet));
				AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
				if(curs == 1){APlot( 4,23,22);APlot( 8,23,23);}else APlot( 4,23,23);
				if(curs == 2){APlot( 9,23,22);APlot(13,23,23);}else APlot( 9,23,23);
				if(curs == 3){APlot(14,23,22);APlot(18,23,23);}else APlot(14,23,23);
				if(curs == 4){APlot(19,23,22);APlot(23,23,23);}else APlot(19,23,23);
				if(curs == 5){APlot( 4,24,22);APlot( 8,24,23);}else APlot( 4,24,23);
				if(curs == 6){APlot( 9,24,22);APlot(13,24,23);}else APlot( 9,24,23);
				if(curs == 7){APlot(14,24,22);APlot(18,24,23);}else APlot(14,24,23);
				if(curs == 8){APlot(19,24,22);APlot(23,24,23);}else APlot(19,24,23);
				if(curs == 9){APlot( 9,25,22);APlot(17,25,23);}else APlot( 9,25,23);
				
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
					if(curs == 1){if(P1.bet<P1.money)P1.bet++;}
					if(curs == 2){if(P1.bet<P1.money-5)P1.bet+=5;}
					if(curs == 3){if(P1.bet<P1.money-10)P1.bet+=10;}
					if(curs == 4){if(P1.bet<P1.money-50)P1.bet+=50;}
					if(curs == 5){if(P1.bet>inibet)P1.bet--;}
					if(curs == 6){if(P1.bet>(inibet+4))P1.bet-=5;}
					if(curs == 7){if(P1.bet>(inibet+9))P1.bet-=10;}
					if(curs == 8){if(P1.bet>(inibet+49))P1.bet-=50;}
					if(curs == 9){selec = 0;}
				}
			}
			
			for(k=23;k<28;k++)
				AdvancedPrint(3,k,"                                    ");
		}
		
		AdvancedPrint(21,2,itoa(P1.bet));
		AdvancedPrint(21,3,itoa(P2.bet));
		AdvancedPrint(21,4,itoa(P3.bet));
		AdvancedPrint(21,5,itoa(P4.bet));
		
		for(j=16;j<22;j++)
		{
			APlot(2,j,5);
			for(i=3;i<37;i++)
				APlot(i,j,109);
		}
		
		//P2 Play
		if(p2Play)
		{
			AdvancedPrint(8,23,"  TOUR DE ");
			AdvancedPrint(18,23,P2.name);
			AdvancedPrint(8,25,"APPUYEZ SUR UNE TOUCHE");
			APlot(1,2,23);
			APlot(1,3,18);
			
			get();
			for(j=16;j<22;j++)
			{
				for(i=2;i<37;i++)
					APlot(i,j,23);
			}
			AdvancedPrint(8,23,"                  ");
			AdvancedPrint(8,25,"                      ");
			
			APlot(1,3,22);
			for(k=0;k<2;k++)
				printCard( 2+k*6, 16, NOCARD, VIDE);
			
			printCard(2,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(2,16, P2.hand1 %13+1, P2.hand1 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, P2.hand2 %13+1, P2.hand2 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			selec = 1; curs = 1; inibet = P2.bet;
			while(selec)
			{
				AdvancedPrint(5,23,"+ 1"); AdvancedPrint(10,23,"+ 5"); AdvancedPrint(15,23,"+10"); AdvancedPrint(20,23,"+50");
				AdvancedPrint(5,24,"- 1"); AdvancedPrint(10,24,"- 5"); AdvancedPrint(15,24,"-10"); AdvancedPrint(20,24,"-50");
				AdvancedPrint(10,25,"VALIDER"); AdvancedPrint(30,24,"      "); AdvancedPrint(30,24,itoa(P2.bet));
				AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
				if(curs == 1){APlot( 4,23,22);APlot( 8,23,23);}else APlot( 4,23,23);
				if(curs == 2){APlot( 9,23,22);APlot(13,23,23);}else APlot( 9,23,23);
				if(curs == 3){APlot(14,23,22);APlot(18,23,23);}else APlot(14,23,23);
				if(curs == 4){APlot(19,23,22);APlot(23,23,23);}else APlot(19,23,23);
				if(curs == 5){APlot( 4,24,22);APlot( 8,24,23);}else APlot( 4,24,23);
				if(curs == 6){APlot( 9,24,22);APlot(13,24,23);}else APlot( 9,24,23);
				if(curs == 7){APlot(14,24,22);APlot(18,24,23);}else APlot(14,24,23);
				if(curs == 8){APlot(19,24,22);APlot(23,24,23);}else APlot(19,24,23);
				if(curs == 9){APlot( 9,25,22);APlot(17,25,23);}else APlot( 9,25,23);
				
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
					if(curs == 1){if(P2.bet<P2.money)P2.bet++;}
					if(curs == 2){if(P2.bet<P2.money-5)P2.bet+=5;}
					if(curs == 3){if(P2.bet<P2.money-10)P2.bet+=10;}
					if(curs == 4){if(P2.bet<P2.money-50)P2.bet+=50;}
					if(curs == 5){if(P2.bet>inibet)P2.bet--;}
					if(curs == 6){if(P2.bet>(inibet+4))P2.bet-=5;}
					if(curs == 7){if(P2.bet>(inibet+9))P2.bet-=10;}
					if(curs == 8){if(P2.bet>(inibet+49))P2.bet-=50;}
					if(curs == 9){selec = 0;}
				}
			}
			
			for(k=23;k<28;k++)
				AdvancedPrint(3,k,"                                    ");
		}
		
		AdvancedPrint(21,2,itoa(P1.bet));
		AdvancedPrint(21,3,itoa(P2.bet));
		AdvancedPrint(21,4,itoa(P3.bet));
		AdvancedPrint(21,5,itoa(P4.bet));
		
		for(j=16;j<22;j++)
		{
			APlot(2,j,5);
			for(i=3;i<37;i++)
				APlot(i,j,109);
		}
		
		//P3 Play
		if(p3Play)
		{
			AdvancedPrint(8,23,"  TOUR DE ");
			AdvancedPrint(18,23,P3.name);
			AdvancedPrint(8,25,"APPUYEZ SUR UNE TOUCHE");
			APlot(1,3,23);
			APlot(1,4,18);
			
			get();
			for(j=16;j<22;j++)
			{
				for(i=2;i<37;i++)
					APlot(i,j,23);
			}
			AdvancedPrint(8,23,"                  ");
			AdvancedPrint(8,25,"                      ");
		
			APlot(1,4,22);
			for(k=0;k<2;k++)
				printCard( 2+k*6, 16, NOCARD, VIDE);
			
			printCard(2,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(2,16, P3.hand1 %13+1, P3.hand1 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, P3.hand2 %13+1, P3.hand2 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			selec = 1; curs = 1; inibet = P3.bet;
			while(selec)
			{
				AdvancedPrint(5,23,"+ 1"); AdvancedPrint(10,23,"+ 5"); AdvancedPrint(15,23,"+10"); AdvancedPrint(20,23,"+50");
				AdvancedPrint(5,24,"- 1"); AdvancedPrint(10,24,"- 5"); AdvancedPrint(15,24,"-10"); AdvancedPrint(20,24,"-50");
				AdvancedPrint(10,25,"VALIDER"); AdvancedPrint(30,24,"      "); AdvancedPrint(30,24,itoa(P3.bet));
				AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
				if(curs == 1){APlot( 4,23,22);APlot( 8,23,23);}else APlot( 4,23,23);
				if(curs == 2){APlot( 9,23,22);APlot(13,23,23);}else APlot( 9,23,23);
				if(curs == 3){APlot(14,23,22);APlot(18,23,23);}else APlot(14,23,23);
				if(curs == 4){APlot(19,23,22);APlot(23,23,23);}else APlot(19,23,23);
				if(curs == 5){APlot( 4,24,22);APlot( 8,24,23);}else APlot( 4,24,23);
				if(curs == 6){APlot( 9,24,22);APlot(13,24,23);}else APlot( 9,24,23);
				if(curs == 7){APlot(14,24,22);APlot(18,24,23);}else APlot(14,24,23);
				if(curs == 8){APlot(19,24,22);APlot(23,24,23);}else APlot(19,24,23);
				if(curs == 9){APlot( 9,25,22);APlot(17,25,23);}else APlot( 9,25,23);
				
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
					if(curs == 1){if(P3.bet<P3.money)P3.bet++;}
					if(curs == 2){if(P3.bet<P3.money-5)P3.bet+=5;}
					if(curs == 3){if(P3.bet<P3.money-10)P3.bet+=10;}
					if(curs == 4){if(P3.bet<P3.money-50)P3.bet+=50;}
					if(curs == 5){if(P3.bet>inibet)P3.bet--;}
					if(curs == 6){if(P3.bet>(inibet+4))P3.bet-=5;}
					if(curs == 7){if(P3.bet>(inibet+9))P3.bet-=10;}
					if(curs == 8){if(P3.bet>(inibet+49))P3.bet-=50;}
					if(curs == 9){selec = 0;}
				}
			}
			
			for(k=23;k<28;k++)
				AdvancedPrint(3,k,"                                    ");
		}
		
		
		AdvancedPrint(21,2,itoa(P1.bet));
		AdvancedPrint(21,3,itoa(P2.bet));
		AdvancedPrint(21,4,itoa(P3.bet));
		AdvancedPrint(21,5,itoa(P4.bet));
		
		for(j=16;j<22;j++)
		{
			APlot(2,j,5);
			for(i=3;i<37;i++)
				APlot(i,j,109);
		}
		
		//P4 Play
		if(p4Play)
		{
			AdvancedPrint(8,23,"  TOUR DE ");
			AdvancedPrint(18,23,P4.name);
			AdvancedPrint(8,25,"APPUYEZ SUR UNE TOUCHE");
			APlot(1,4,23);
			APlot(1,5,18);
			
			get();
			for(j=16;j<22;j++)
			{
				for(i=2;i<37;i++)
					APlot(i,j,23);
			}
			AdvancedPrint(8,23,"                  ");
			AdvancedPrint(8,25,"                      ");
			
			APlot(1,5,22);
			for(k=0;k<2;k++)
				printCard( 2+k*6, 16, NOCARD, VIDE);
			
			printCard(2,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(2,16, P4.hand1 %13+1, P4.hand1 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, NOCARD, FLIP);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			printCard(8,16, P4.hand2 %13+1, P4.hand2 /13+1);
			for(i=0;i<4;i++)
				for(j=0;j<256;j++)
					;
			selec = 1; curs = 1; inibet = P4.bet;
			while(selec)
			{
				AdvancedPrint(5,23,"+ 1"); AdvancedPrint(10,23,"+ 5"); AdvancedPrint(15,23,"+10"); AdvancedPrint(20,23,"+50");
				AdvancedPrint(5,24,"- 1"); AdvancedPrint(10,24,"- 5"); AdvancedPrint(15,24,"-10"); AdvancedPrint(20,24,"-50");
				AdvancedPrint(10,25,"VALIDER"); AdvancedPrint(30,24,"      "); AdvancedPrint(30,24,itoa(P4.bet));
				AdvancedPrint(9,27,"  [FLECHES]  [ENTER]  ");
				if(curs == 1){APlot( 4,23,22);APlot( 8,23,23);}else APlot( 4,23,23);
				if(curs == 2){APlot( 9,23,22);APlot(13,23,23);}else APlot( 9,23,23);
				if(curs == 3){APlot(14,23,22);APlot(18,23,23);}else APlot(14,23,23);
				if(curs == 4){APlot(19,23,22);APlot(23,23,23);}else APlot(19,23,23);
				if(curs == 5){APlot( 4,24,22);APlot( 8,24,23);}else APlot( 4,24,23);
				if(curs == 6){APlot( 9,24,22);APlot(13,24,23);}else APlot( 9,24,23);
				if(curs == 7){APlot(14,24,22);APlot(18,24,23);}else APlot(14,24,23);
				if(curs == 8){APlot(19,24,22);APlot(23,24,23);}else APlot(19,24,23);
				if(curs == 9){APlot( 9,25,22);APlot(17,25,23);}else APlot( 9,25,23);
				
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
					if(curs == 1){if(P4.bet<P4.money)P4.bet++;}
					if(curs == 2){if(P4.bet<P4.money-5)P4.bet+=5;}
					if(curs == 3){if(P4.bet<P4.money-10)P4.bet+=10;}
					if(curs == 4){if(P4.bet<P4.money-50)P4.bet+=50;}
					if(curs == 5){if(P4.bet>inibet)P4.bet--;}
					if(curs == 6){if(P4.bet>(inibet+4))P4.bet-=5;}
					if(curs == 7){if(P4.bet>(inibet+9))P4.bet-=10;}
					if(curs == 8){if(P4.bet>(inibet+49))P4.bet-=50;}
					if(curs == 9){selec = 0;}
				}
			}
			
			for(k=23;k<28;k++)
				AdvancedPrint(3,k,"                                    ");
		}
		
		
		get();
	}
}
