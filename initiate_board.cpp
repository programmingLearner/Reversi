#include<iostream>
using namespace std;

extern short now[][9];
extern short record_start[9][9];
extern int turns;

void initiate_board()//初始化棋盘
{
	int i=0,j=0;
	turns=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			now[i][j]=0;//0表示未着子点
	}
	now[4][4]=2;//2表示白子
	now[5][5]=2;
	now[4][5]=1;//1表示黑子
	now[5][4]=1;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			record_start[i][j]=now[i][j];
	}
}