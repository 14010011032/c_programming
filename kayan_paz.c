#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

int sayilar[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char harita[4][4];
void tablo_ciz();
void harita_al();
void kaydir();
int oyun_bitti();
int getch(void);
int getche(void);


int main()
{
	srand(time(NULL));
	harita_al();
	tablo_ciz();
	printf("\n");
	printf("\tYukaridakini kaydirmak icin < 8 > e basiniz\n");
	printf("\tAsagidakini  kaydirmak icin < 5 > e basiniz\n");
	printf("\tSoldakini    kaydirmak icin < 4 > e basiniz\n");
	printf("\tSagdakini    kaydirmak icin < 6 > e basiniz\n");
	kaydir();
	return 0;
}
void harita_al()
{
	harita[3][3]=0;
	int cekilen,i,j;
 	for (i = 0; i < 4;i++)
 	{ 	
		for (j = 0; j < 4;j++)
	 		{
	 			cekilen=rand()%15;
	 			if(sayilar[cekilen]!=0 || (j==3 && i==3) )
	 			{
	 				
	 					harita[i][j]=sayilar[cekilen];
	 					sayilar[cekilen]=0;
	 			}
	 			else
	 			{
	 				j--;
	 			}
	 		}
  	}
}
void tablo_ciz()
{

	int i,j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if(harita[i][j]==0)
			{
				printf("\t");
				printf("    ");
			}
			else
			{
				printf("\t");
				printf("  %d  ",harita[i][j]);
			}
		}
		printf("\n\n");
	}
}
void kaydir()
{
	int x=3,sayac=0,y=3,temp;
	while(1)
	{
		int say;
		say=oyun_bitti();
		tablo_ciz();
		if(say==16)
		{
			printf("\toyun bitti kardesim tebrikler \n");
			printf("\t %d hamlede bitirdiniz \n",sayac);
			break;
		}
		puts("\n\tHangi yon:");
		int ascii;
    	ascii = getch();
   		char ch = (char)ascii;
    	int yon = ch - '0';
		if(yon==8 || yon==4 || yon==6 || yon==5)
		{
			if( (x==3 && yon==5) || (y==3 && yon==6) || (x==0 && yon==8) || (y==0 && yon==4))
				{
					printf("\t Fazla gitme  \n");
				}
				else
				{
					//system("clear");
					sayac++;
					switch(yon)
					{
						case 8:
						
							temp=harita[x-1][y];
							harita[x-1][y]=harita[x][y];
							harita[x][y]=temp;
							x=x-1;
							break;
						case 5:
						
							temp=harita[x+1][y];
							harita[x+1][y]=harita[x][y];
							harita[x][y]=temp;
							x=x+1;
							break;
						case 4:
							temp=harita[x][y-1];
							harita[x][y-1]=harita[x][y];
							harita[x][y]=temp;
							y=y-1;
							break;
						case 6:
							temp=harita[x][y+1];
							harita[x][y+1]=harita[x][y];
							harita[x][y]=temp;
							y=y+1;
							break;
					}
				}
		}
		else
		{
			printf("\tYanlis yon girdiniz.tekrar giriniz\n");
		}
	}
}
int oyun_bitti()
{
	int i,j,kontrol=1;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (harita[i][j]==kontrol)
			{
				kontrol++;
			}
			else
			{
				i=4;
				j=4;
			}
		}
	}
	return kontrol;
}
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}