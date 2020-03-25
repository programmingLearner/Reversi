#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include"head.h"
using namespace std;

extern short now[][9];
extern short record_whose_turn[100];
extern short record_i[100];
extern short record_j[100];
extern short available[][9];
extern short record_start[][9];
extern int turns;

void undo()
{
	int temp=turns,i=0,j=0;
	turns=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			now[i][j]=record_start[i][j];
	}
	while(turns<temp-3)
	{
		turns++;
		if(record_i[turns]!=-1)
		{
			now[record_i[turns]][record_j[turns]]=record_whose_turn[turns];
			my_reverse(record_i[turns],record_j[turns]);
		}
	}
	turns++;
	return;
}

bool players_turn(short whose_turn)//玩家回合
{
	bool save_to_file();
	int i=0,k=0,m=0,n=0,l=0,p=0,go=0;
	bool judge=0,saved=0,quit=0;
	short sav[9][9]={0};
	char j='a';
	string inpu;
	cin>>inpu;
	if((inpu.length()==1)&&(inpu[0]>='A')&&(inpu[0]<='Z'))
	{
		for(m=1;m<9;m++)
		{
			for(n=1;n<9;n++)
			{
				if(available[m][n]==inpu[0]-'A'+31)
				{
					i=m;
					k=n;
					break;
				}
			}
		}
		m=0,n=0;
	}
	else if((inpu.length()==2)&&(inpu[0]>='0')&&(inpu[0]<='9')&&(inpu[1]<='h')&&(inpu[1]>='a'))
	{
		i=inpu[0]-'0';
		j=inpu[1];
		k=j-'a'+1;
	}
	else if((inpu.length()==4)&&(inpu[0]=='u')&&(inpu[1]=='n')&&(inpu[2]=='d')&&(inpu[3]=='o'))
	{
		undo();
		system("cls");
		print_board(1);
		return players_turn(whose_turn);
	}
	else if((inpu.length()==4)&&(inpu[0]=='s')&&(inpu[1]=='a')&&(inpu[2]=='v')&&(inpu[3]=='e'))
	{
		record_whose_turn[turns]=-1;
		while(saved==0)
			saved=save_to_file();
		return 0;
	}
	else if((inpu.length()==4)&&(inpu[0]=='q')&&(inpu[1]=='u')&&(inpu[2]=='i')&&(inpu[3]=='t'))
	{
		return 0;
	}
	else
	{
		cout<<"非法走子！请重新走棋"<<endl;
		judge=players_turn(whose_turn);
		return judge;
	}
	if(now[i][k]==0)
		now[i][k]=whose_turn;
	else
	{
		cout<<"非法走子！请重新走棋"<<endl;
		judge=players_turn(whose_turn);
		return judge;
	}
	if(my_reverse(i,k)==0)
	{
		now[i][k]=0;
		cout<<"非法走子！请重新走棋"<<endl;
		judge=players_turn(whose_turn);
		return judge;
	}
	record_i[turns]=i;
	record_j[turns]=k;
	return 1;
}