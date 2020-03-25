#include<iostream>
#include"head.h"
using namespace std;

extern short now[][9];
extern short available[][9];
extern short record[][9][9];
extern int turns;

int count()
{
	int i=0,j=0,cb=0,cw=0,rtrn=0;
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==1)
				cb++;
			if(now[i][j]==2)
				cw++;
		}
	}
	rtrn=cb*100+cw;
	return rtrn;
}