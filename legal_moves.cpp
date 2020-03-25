#include<iostream>
#include"head.h"
using namespace std;

extern short now[][9];
extern short available[][9];
extern short record[][9][9];
extern int turns;
extern short whose_turn;

void legal_moves()
{
	int i=0,j=0,m=0,n=0;
	short save[9][9]={0};
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			available[i][j]=now[i][j];
			save[i][j]=now[i][j];
		}
	}
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(available[i][j]==0)
			{
				if(((i+1)<9)&&(available[i+1][j]==3-whose_turn))
					available[i][j]=3;
				else if(((i-1)>0)&&(available[i-1][j]==3-whose_turn))
					available[i][j]=3;
				else if(((j-1)>0)&&(available[i][j-1]==3-whose_turn))
					available[i][j]=3;
				else if(((j+1)<9)&&(available[i][j+1]==3-whose_turn))
					available[i][j]=3;
				else if(((i+1)<9)&&((j+1)<9)&&(available[i+1][j+1]==3-whose_turn))
					available[i][j]=3;
				else if(((i-1)>0)&&((j+1)<9)&&(available[i-1][j+1]==3-whose_turn))
					available[i][j]=3;
				else if(((i+1)<9)&&((j-1)>0)&&(available[i+1][j-1]==3-whose_turn))
					available[i][j]=3;
				else if(((i-1)>0)&&((j-1)>0)&&(available[i-1][j-1]==3-whose_turn))
					available[i][j]=3;
				else
					available[i][j]=4;
				if(available[i][j]==3)
				{
					now[i][j]=whose_turn;
					if(my_reverse(i,j)==0)
						available[i][j]=4;
					for(m=0;m<9;m++)
					{
						for(n=0;n<9;n++)		
							now[m][n]=save[m][n];//²»ÊÇi,j!
					}
				}
			}
		}
	}
	int k=31;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(available[i][j]!=3)
				available[i][j]=0;
			else
			{
				available[i][j]=k;
				k++;
			}
		}
	}
}	