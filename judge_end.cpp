#include<iostream>
#include"head.h"
using namespace std;

extern short now[][9];
extern short record[][9][9];
extern int turns;

bool judge_end(short whose_turn)
{
	int i=0,j=0,k=0,m=0,l=0,p=0,n=0,judge=0;
	short sav[9][9]={0};
	for(i=1;i<9;i++)
	{
		for(k=1;k<9;k++)
			sav[i][k]=now[i][k];
	}
	for(i=1;i<9;i++)
	{
		for(k=1;k<9;k++)
		{		
			if(now[i][k]==0)
			{
				now[i][k]=whose_turn;
				if(my_reverse(i,k)==1)
				{
					judge=1;
					for(m=1;m<9;m++)
					{
						for(n=1;n<9;n++)
							now[m][n]=sav[m][n];
					}
					break;
				}
				for(m=1;m<9;m++)
				{
					for(n=1;n<9;n++)
						now[m][n]=sav[m][n];
				}
			}
		}
		if(judge==1)
			break;
	}
	return judge;
}